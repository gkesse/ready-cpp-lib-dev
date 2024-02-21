//===============================================
#include "GObject.h"
//===============================================
GObject* GObject::m_instance = 0;
//===============================================
GObject::GObject()
: GCommon() {

}
//===============================================
GObject::~GObject() {
    clearMap();
}
//===============================================
GObject* GObject::Instance() {
    if(m_instance == 0) {
        m_instance = new GObject;
        m_instance->init();
    }
    return m_instance;
}
//===============================================
void GObject::clearMap() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GObject* lObj = m_map[i];
        delete lObj;
    }
    m_map.clear();
}
//===============================================
void GObject::init() {
    m_webRoot = getEnv("GWEB_ROOT");

    if(m_webRoot.isEmpty()) {
        slog(eGERR, "La racine du serveur web n'a pas été configurée.");
    }
    else {
        slog(eGINF, "La racine du serveur web a été bien configurée."
                    "|webroot=%s", m_webRoot.c_str());
    }
}
//===============================================
GString GObject::getEnv(const GString& _env) const {
    char* lEnv = getenv(_env.c_str());
    if(lEnv == 0) return "";
    return lEnv;
}
//===============================================
GString GObject::getResource(const GString& _path) const {
    return sformat("%s%s", m_webRoot.c_str(), _path.c_str());
}
//===============================================
const GLog& GObject::getLogs() const {
    return m_logs;
}
//===============================================
void GObject::print() const {
    printf("%s\n", serialize().c_str());
}
//===============================================
GObject* GObject::clone() const {return new GObject;}
GString GObject::serialize(const GString& _code) const {return "";}
void GObject::deserialize(const GString& _data, const GString& _code) {}
//===============================================
