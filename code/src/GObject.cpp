//===============================================
#include "GObject.h"
#include "GSocket.h"
//===============================================
GObject* GObject::m_instance = 0;
//===============================================
GObject::GObject()
: m_port(-1)
, m_pid(-1) {
    m_resp.createDoc();
    m_resp.createDatas();
}
//===============================================
GObject::~GObject() {
    clearMap();
}
//===============================================
GObject* GObject::Instance() {
    if(m_instance == 0) {
        m_instance = new GObject;
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
void GObject::print() const {
    printf("%s\n", serialize().c_str());
}
//===============================================
GObject* GObject::clone() const {return new GObject;}
GString GObject::serialize(const GString& _code) const {return "";}
void GObject::deserialize(const GString& _data, const GString& _code) {}
//===============================================
