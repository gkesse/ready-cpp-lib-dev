//===============================================
#include "GLog.h"
#include "GCode.h"
//===============================================
GLog::GLog() {

}
//===============================================
GLog::~GLog() {
    clearMap();
}
//===============================================
GString GLog::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "type", m_type);
    lDom.addData(_code, "side", m_side);
    lDom.addData(_code, "msg", m_msg);
    lDom.addData(_code, m_map);
    return lDom.toString();
}
//===============================================
void GLog::deserialize(const GString& _data, const GString& _code) {
    GCode lDom;
    lDom.loadXml(_data);
    m_type = lDom.getData(_code, "type");
    m_side = lDom.getData(_code, "side");
    m_msg = lDom.getData(_code, "msg");
    lDom.getData(_code, m_map, this);
}
//===============================================
GLog* GLog::clone() {
    GLog* lObj = new GLog;
    lObj->setObj(*this);
    return lObj;
}
//===============================================
void GLog::clearMap() {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lObj = m_map.at(i);
        delete lObj;
    }
    m_map.clear();
}
//===============================================
void GLog::setObj(const GLog& _obj) {
    m_type = _obj.m_type;
    m_side = _obj.m_side;
    m_msg = _obj.m_msg;
}
//===============================================
void GLog::addProblem() {
    addError("Un problème a été rencontré.");
}
//===============================================
void GLog::addError(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = LOG_TYPE_ERROR;
    lObj->m_side = "server";
    lObj->m_msg = _msg;
    m_map.push_back(lObj);
}
//===============================================
void GLog::addInfo(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = LOG_TYPE_INFO;
    lObj->m_side = "server";
    lObj->m_msg = _msg;
    m_map.push_back(lObj);
}
//===============================================
void GLog::addData(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = LOG_TYPE_DATA;
    lObj->m_side = "server";
    lObj->m_msg = _msg.toBase64();
    m_map.push_back(lObj);
}
//===============================================
void GLog::addLogs(const GLog& _obj) {
    for(int i = 0; i < (int)_obj.m_map.size(); i++) {
        GLog* lObj = _obj.m_map.at(i);
        m_map.push_back(lObj->clone());
    }
}
//===============================================
void GLog::showLogs() const {
    for(int i = 0; i < size(); i++) {
        GLog* lObj = m_map.at(i);
        printf("[%5s]|[%s]|%s\n", lObj->m_type.c_str(), lObj->m_side.c_str(), lObj->m_msg.c_str());
    }
}
//===============================================
bool GLog::hasErrors() const {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lObj = m_map.at(i);
        if(lObj->m_type == LOG_TYPE_ERROR) return true;
    }
    return false;
}
//===============================================
int GLog::size() const {
    return (int)m_map.size();
}
//===============================================
bool GLog::isEmpty() const {
    return (size() == 0);
}
//===============================================
GString GLog::toJson() const {
    GCode lDom;
    lDom.loadXml(serialize());
    return lDom.toJson();
}
//===============================================
