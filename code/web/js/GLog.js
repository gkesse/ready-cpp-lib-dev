//===============================================
class GLog {
    //===============================================
    constructor() {
        this.m_type = "";
        this.m_side = "";
        this.m_msg = "";
        this.m_map = [];
    }
    //===============================================
    clone() {
        return new GLog();
    }
    //===============================================
    setObj(_obj) {
        this.m_type = _obj.m_type;
        this.m_side = _obj.m_side;
        this.m_msg = _obj.m_msg;
    }
    //===============================================
    clearMap() {
        this.m_map = [];
    }
    //===============================================
    addError(_msg) {
        var lObj = new GLog();
        lObj.m_type = "error";
        lObj.m_side = "client_js";
        lObj.m_msg = _msg;
        this.m_map.push(lObj);
    }
    //===============================================
    addLog(_msg) {
        var lObj = new GLog();
        lObj.m_type = "log";
        lObj.m_side = "client_js";
        lObj.m_msg = _msg;
        this.m_map.push(lObj);
    }
    //===============================================
    addData(_msg) {
        var lObj = new GLog();
        lObj.m_type = "data";
        lObj.m_side = "client_js";
        lObj.m_msg =  _msg;
        this.m_map.push(lObj);
    }
    //===============================================
    addLogs(_obj) {
        for(var i = 0; i < _obj.m_map.length; i++) {
            var lObj = _obj.m_map[i];
            var lNew = new GLog();
            lNew.setObj(lObj);
            this.m_map.push(lNew);
        }
    }
    //===============================================
    loadFromMap(_index) {
        if(_index >= 1 && _index <= this.m_map.length) {
            var lObj = this.m_map[_index - 1];
            this.setObj(lObj);
        }
    }
    //===============================================
    loadToMap(_index) {
        if(_index >= 1 && _index <= this.m_map.length) {
            var lObj = this.m_map[_index - 1];
            lObj.setObj(this);
        }
    }
    //===============================================
    hasErrors() {
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type == "error") return true;
        }
        return false;
    }
    //===============================================
    hasLogs() {
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type == "log") return true;
        }
        return false;
    }
    //===============================================
    hasDatas() {
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type == "data") return true;
        }
        return false;
    }
    //===============================================
    getErrors() {
        var lErrors = "";
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type != "error") continue;
            var lError = lObj.m_msg;
            if(i != 0) lErrors += "<br>";
            lError = sprintf("<i class='fa fa-chevron-right'></i> %s", lError);
            lErrors += lError;
        }
        return lErrors;
    }
    //===============================================
    getLogs() {
        var lLogs = "";
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type != "log") continue;
            var lLog = lObj.m_msg;
            if(i != 0) lLogs += "<br>";
            lLog = sprintf("<i class='fa fa-chevron-right'></i> %s", lLog);
            lLogs += lLog;
        }
        return lLogs;
    }
    //===============================================
    getDatas() {
        var lDatas = "";
        for(var i = 0; i < this.m_map.length; i++) {
            var lObj = this.m_map[i];
            if(lObj.m_type != "data") continue;
            var lData = lObj.m_msg;
            if(i != 0) lDatas += "<br>";
            lData = sprintf("<xmp>%s</xmp>\n", lData);
            lDatas += lData;
        }
        return lDatas;
    }
    //===============================================
    serialize(_code = "logs") {
        var lDom = new GCode();
        lDom.createDoc();
        lDom.addData(_code, "type", this.m_type);
        lDom.addData(_code, "side", this.m_side);
        if(this.m_type == "data") lDom.addData(_code, "msg", this.m_msg.toBase64());
        else lDom.addData(_code, "msg", this.m_msg);
        lDom.addMap(_code, this.m_map);
        return lDom.toString();
    }
    //===============================================
    deserialize(_data, _code = "logs") {
        var lDom = new GCode();
        lDom.loadXml(_data);
        this.m_type = lDom.getData(_code, "type");
        this.m_side = lDom.getData(_code, "side");
        if(this.m_type == "data") this.m_msg = lDom.getData(_code, "msg").fromBase64();
        else this.m_msg = lDom.getData(_code, "msg");
        lDom.getMap(_code, this.m_map, this);
    }
    //===============================================
}
//===============================================
