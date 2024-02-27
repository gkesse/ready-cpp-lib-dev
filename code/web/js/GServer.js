//===============================================
class GServer extends GObject {
    //===============================================
    constructor() {
        super();
        this.m_module = "";
        this.m_method = "";
        this.m_obj = null;
        this.m_params = "";
        this.m_response = "";
    }
    //===============================================
    setParams(_module, _method, _obj, _params) {
        this.m_module = _module;
        this.m_method = _method;
        this.m_obj = _obj;
        this.m_params = _params;
    }
    //===============================================
    setServer(_obj) {
        this.m_module = _obj.m_module;
        this.m_method = _obj.m_method;
        this.m_obj = _obj.m_obj;
        this.m_params = _obj.m_params;
    }
    //===============================================
    setResponse(_response) {
        this.m_response = _response;
    }
    //===============================================
    isOK() {
        var lLog = new GLog();
        lLog.deserialize(this.m_response);
        if(lLog.isEmpty()) return false;
        return !lLog.hasErrors();
    }
    //===============================================
    getLog() {
        var lLog = new GLog();
        lLog.deserialize(this.m_response);
        lLog.loadFromMap(1);
        return lLog.m_msg;
    }
    //===============================================
    run() {
        if(this.m_module == "test") {
            this.runTest();
        }
        else {
            console.log(sprintf("Le module est inconnu."+
                                "|module=%s"+
                                "|method=%s", this.m_module, this.m_method));
        }
    }
    //===============================================
    runTest() {
        var lObj = new GTestJs();
        lObj.setServer(this);
        lObj.run();
    }
    //===============================================
}
//===============================================