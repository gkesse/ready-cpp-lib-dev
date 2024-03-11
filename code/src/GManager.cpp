//===============================================
#include "GManager.h"
//===============================================
GManager::GManager()
: GCallbackXml() {

}
//===============================================
GManager::~GManager() {

}
//===============================================
void GManager::setManager(const GManager& _obj) {
    m_module = _obj.m_module;
    m_method = _obj.m_method;
    m_request = _obj.m_request;
}
//===============================================
GString GManager::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "module", m_module);
    lDom.addData(_code, "method", m_method);
    return lDom.toString();
}
//===============================================
void GManager::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_module = lDom.getData(_code, "module");
    m_method = lDom.getData(_code, "method");
}
//===============================================
