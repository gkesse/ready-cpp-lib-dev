//===============================================
#include "GObject.h"
#include "GSocket.h"
//===============================================
GObject* GObject::m_instance = 0;
//===============================================
GObject::GObject()
: m_port(-1)
, m_pid(-1) {

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
    m_logs.clearMap();
}
//===============================================
void GObject::init() {
    m_dataPath = getEnv("GPROJECT_DATA");

    if(m_dataPath.isEmpty()) {
        slog(eGERR, "Le chemin des données n'a pas été configuré.");
    }
    else {
        slog(eGINF, "Le chemin des données a été bien configuré."
                    "|data_path=%s", m_dataPath.c_str());
    }
}
//===============================================
void GObject::setObject(const GObject& _obj) {
    m_addressIP = _obj.m_addressIP;
    m_port = _obj.m_port;
    m_pid = _obj.m_pid;
}
//===============================================
void GObject::setSocket(const GSocket& _socket) {
    m_addressIP = _socket.getAddressIP();
    m_port = _socket.getPort();
    m_pid = _socket.getPid();
}
//===============================================
const GLog& GObject::getLogs() const {
    return m_logs;
}
//===============================================
GString GObject::getEnv(const GString& _env) const {
    char* lEnv = getenv(_env.c_str());
    if(lEnv == 0) return "";
    return lEnv;
}
//===============================================
GString GObject::getPath(const GString& _path) const {
    return sformat("%s%s", m_dataPath.c_str(), _path.c_str());
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
