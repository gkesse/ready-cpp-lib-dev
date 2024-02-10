//===============================================
class GObject {
    //===============================================
    constructor() {
        this.m_map = [];
        this.m_module = "";
        this.m_method = "";
        this.m_obj = null;
        this.m_params = null;
    }
    //===============================================
    setObjects(_module, _method, _obj, _params) {
        this.m_module = _module;
        this.m_method = _method;
        this.m_obj = _obj;
        this.m_params = _params;
    }
    //===============================================
    setObject(_obj) {
        this.m_module = _obj.m_module;
        this.m_method = _obj.m_method;
        this.m_obj = _obj.m_obj;
        this.m_params = _obj.m_params;
    }
    //===============================================
    clone() {return new GObject();}
    serialize(_code = "object") {return "";}
    deserialize(_data, _code = "object") {}
    //===============================================
}
//===============================================