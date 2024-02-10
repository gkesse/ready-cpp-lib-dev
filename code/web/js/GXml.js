//===============================================
class GXml {
    //===============================================
    constructor() {
        this.m_doc = null;
        this.m_node = null;
        this.m_doc2 = null;
        this.m_node2 = null;
    }
    //===============================================
    createDoc() {
        var lXml = sprintf("<?xml version='1.0' encoding='UTF-8'?><rdv></rdv>");
        if(!this.loadXml(lXml)) return false;
        return true;
    }
    //===============================================
    loadXml(_data) {
        _data = _data.trim();
        if(_data == "") return false;
        if(window.DOMParser) {
            var lParser = new DOMParser();
            this.m_doc = lParser.parseFromString(_data, "text/xml");            
            if(!this.m_doc) return false;
            this.m_node = this.m_doc.documentElement;
            if(!this.m_node) return false;
            this.m_doc2 = this.m_doc;
            this.m_node2 = this.m_node;
        }
        else {
            this.m_doc = new ActiveXObject("Microsoft.XMLDOM");
            if(!this.m_doc) return false;
            this.m_doc.async = false;
            if(!this.m_doc.loadXML(_data)) return false;
            this.m_node = this.m_doc.documentElement;
            if(!this.m_node) return false;
            this.m_doc2 = this.m_doc;
            this.m_node2 = this.m_node;
        }
        return true;
    }
    //===============================================
    loadNode(_data) {
        _data = _data.trim();
        if(_data == "") return false;
        if(!this.m_node) return false;
        var lDom = this.m_doc2.createElement("template");
        lDom.innerHTML = _data;
        var lNodes = lDom.childNodes;
        while(lNodes[0]) {
            this.m_node.appendChild(lNodes[0]);
        }
        return true;
    }
    //===============================================
    createNode(_path, _value = "", _isCData = false) {
        if(_path == "") return new GXml();
        if(!this.m_node) return new GXml();
        var lPaths = _path.split("/");
        var lPath = "";
        if(_path[0] == "/") lPath = "/";
        var lNode = this.m_node;
        var isPath = false;
        var lDom = this;
        
        for(var i = 0; i < lPaths.length; i++) {
            var lPathI = lPaths[i];
            if(lPathI == "") continue;
            if(isPath) lPath += "/";
            lPath += lPathI;
            isPath = true;
            
            if(!this.existeNode(lPath)) {
                lDom = lDom.addObj(lPathI);
            }
            else {
                lDom = lDom.getNode(lPath);
            }
        }
        lDom.setValue(_value, _isCData);
        return lDom;
    }    
    //===============================================
    addObj(_name) {
        var lDom = new GXml();
        lDom.m_doc2 = this.m_doc2;
        lDom.m_node2 = this.m_node2;
        if(!this.m_node) return lDom;
        lDom.m_node = this.m_doc2.createElement(_name);
        this.m_node.appendChild(lDom.m_node);
        return lDom;
    }    
    //===============================================
    addData(_name, _value, _isCData = false) {
        var lDom = new GXml();
        lDom.m_doc2 = this.m_doc2;
        lDom.m_node2 = this.m_node2;
        if(!this.m_node) return new lDom;
        lDom.m_node = this.m_doc2.createElement(_name);
        this.m_node.appendChild(lDom.m_node);
        lDom.setValue(_value, _isCData);
        return lDom;
    }    
    //===============================================
    existeNode(_path) {
        return (this.countNode(_path) != 0);
    }
    //===============================================
    countNode(_path) {
        if(_path == "") return 0;
        if(!this.m_node) return 0;
        var lCount = 0;
        
        if(this.m_doc2.evaluate) {
            var lNode = this.m_node;
            if(_path[0] == "/") lNode = this.m_node2;
            var lNodes = this.m_doc2.evaluate(_path, lNode, null, XPathResult.ANY_TYPE, null);
            while(1) {
                var lNodeI = lNodes.iterateNext();
                if(!lNodeI) break;
                lCount++;
            }
        } 
        else if(window.ActiveXObject || xhttp.responseType == "msxml-document") {
            _root.m_doc.setProperty("SelectionLanguage", "XPath");
            var lNodes = this.m_doc2.selectNodes(_path);
            lCount = lNodes.length;
        }
        return lCount;
    }
    //===============================================
    getNode(_path) {
        var lDom = new GXml();
        lDom.m_doc2 = this.m_doc2;
        lDom.m_node2 = this.m_node2;
        
        if(_path == "") return lDom;
        if(!this.m_node) return lDom;
                
        if(this.m_doc2.evaluate) {
            var lNode = this.m_node;
            if(_path[0] == "/") lNode = this.m_node2;
            var lNodes = this.m_doc2.evaluate(_path, lNode, null, XPathResult.ANY_TYPE, null);
            lDom.m_node = lNodes.iterateNext();
        } 
        else if(window.ActiveXObject || xhttp.responseType == "msxml-document") {
            this.m_doc2.setProperty("SelectionLanguage", "XPath");
            var lNodes = this.m_doc2.selectNodes(_path);
            if(lNodes.length) {
                lDom.m_node = lNodes[0];
            }
        }
        return lDom;
    }
    //===============================================
    getValue(_isCData = false) {
        if(!this.m_node) return "";
        var lData = "";
        if(!_isCData) {
            lData = this.m_node.innerHTML;
        }
        else {
            lData = this.m_node.firstElementChild.nodeValue;
        }
        return lData;
    }
    //===============================================
    setValue(_value, _isCData = false) {
        if(_value == "") return;
        if(!this.m_node) return;
        
        if(!_isCData) {
            this.m_node.innerHTML = _value;
        }
        else {
            var lCData = this.m_doc2.createCDATASection(_value);
            this.m_node.appendChild(lCData);
        }
    }
    //===============================================
    toString() {
        if(!this.m_doc) return "";
        var lData = this.m_doc.documentElement.outerHTML;
        lData = sprintf("<?xml version='1.0' encoding='UTF-8'?>\n%s", lData);
        return lData.toXml();
    }
    //===============================================
    toNode() {
        if(!this.m_node) return "";
        var lData = this.m_node.outerHTML;
        return lData.toXml();
    }
    //===============================================
}
//===============================================