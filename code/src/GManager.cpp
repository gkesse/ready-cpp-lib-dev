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
void GManager::run() {
    deserialize(m_request);
    slog(eGINF, "Traitement de la requête XML."
                "|module=%s"
                "|method=%s", m_module.c_str(), m_method.c_str());
}
//===============================================
