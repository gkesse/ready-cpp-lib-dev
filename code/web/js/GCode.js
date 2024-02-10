//===============================================
class GCode extends GXml {
    //===============================================
    constructor() {
        super();
    }   
    //===============================================
    createDatas() {
        var lDom = this.getNode(sprintf("/rdv/datas"));
        if(!lDom.m_node) {
            lDom = this.createNode("/rdv/datas");
        }
        return lDom;
    }
    //===============================================
    createCode(_code) {
        var lDom = new GXml();
        lDom = this.getNode(sprintf("/rdv/datas/data[code='%s']", _code));
        if(!lDom.m_node) {
            lDom = this.createDatas();
            lDom = lDom.addObj("data");
            lDom.addData("code", _code);
        }
        return lDom;
    }
    //===============================================
    addData(_code, _name, _value, _isCData) {
        if(_value == 0) return;
        if(_value == "") return;
        var lDom = new GXml();
        lDom = this.getNode(sprintf("/rdv/datas/data[code='%s']/%s", _code, _name));
        if(!lDom.m_node) {
            lDom = this.createCode(_code);
            lDom.addData(_name, _value, _isCData);
        }
        else {
            lDom.setValue(_value, _isCData);
        }
    }
    //===============================================
    addMap(_code, _map) {
        if(_map.length == 0) return;
        
        var lDom = new GXml();
        lDom = this.getNode(sprintf("/rdv/datas/data[code='%s']/map", _code));
        
        if(!lDom.m_node) {
            lDom = this.createCode(_code);
            lDom = lDom.addObj("map");
        }
        
        for(var i = 0; i < _map.length; i++) {
            var lObj = _map[i];
            var lData = lObj.serialize(_code);
            lData = this.toDatas(lData);
            lDom.loadNode(lData);
        }
    }
    //===============================================
    getData(_code, _name, _isCData) {
        var lDom = new GXml();
        lDom = this.getNode(sprintf("/rdv/datas/data[code='%s']/%s", _code, _name));
        if(!lDom.m_node) return "";
        var lData = lDom.getValue();
        return lData;
    }
    //===============================================
    getMap(_code, _map, _obj) {        
        var lSize = this.countNode(sprintf("/rdv/datas/data[code='%s']/map/data", _code));
        if(!lSize) return;
        
        for(var i = 0; i < lSize; i++) {
            var lDom = new GXml();
            lDom = this.getNode(sprintf("/rdv/datas/data[code='%s']/map/data[position()=%s]", _code, i + 1));
            var lData = lDom.toNode();
            lData = this.toCode(lData);
            var lObj = _obj.clone();
            lObj.deserialize(lData, _code);
            _map.push(lObj);
        }
    }
    //===============================================
    loadData(_data) {
        if(_data == "") return;
        var lData = this.toDatas(_data);
        if(lData != "") {
            var lDom = new GCode();
            lDom = this.getNode(sprintf("/rdv/datas"));
            lDom.loadNode(lData);
        }
    }
    //===============================================
    toDatas(_data) {
        _data = _data.trim();
        if(_data == "") return "";
        var lDom = new GXml();
        var lDomC = new GXml();
        lDom.loadXml(_data);
        lDomC = lDom.getNode(sprintf("/rdv/datas/data"));
        if(!lDomC.m_node) return "";
        var lData = lDomC.toNode();
        return lData;
    }
    //===============================================
    toCode(_data) {
        _data = _data.trim();
        if(_data == "") return "";
        var lDom = new GCode();
        var lDomC = new GCode();
        lDom.createDoc();
        lDomC = lDom.createDatas();
        lDomC.loadNode(_data);
        var lData = lDom.toString();
        return lData;
    }
    //===============================================
}
//===============================================
