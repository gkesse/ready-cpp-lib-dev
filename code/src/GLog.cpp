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
GString GLog::serialize(const GString& _code) {
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
    lObj->setLog(*this);
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
void GLog::setLog(const GLog& _obj) {
    m_type = _obj.m_type;
    m_side = _obj.m_side;
    m_msg = _obj.m_msg;
}
//===============================================
void GLog::addError(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = "error";
    lObj->m_side = "server";
    lObj->m_msg = _msg;
    m_map.push_back(lObj);
}
//===============================================
void GLog::addTechError(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = "tech_error";
    lObj->m_side = "server";
    lObj->m_msg = _msg;
    m_map.push_back(lObj);
}
//===============================================
void GLog::addLog(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = "log";
    lObj->m_side = "server";
    lObj->m_msg = _msg;
    m_map.push_back(lObj);
}
//===============================================
void GLog::addData(const GString& _msg) {
    GLog* lObj = new GLog;
    lObj->m_type = "data";
    lObj->m_side = "server";
    lObj->m_msg = _msg;
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
void GLog::showErrors() {
    if(!m_map.size()) return;
    printf("\n");
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lObj = m_map.at(i);
        if(lObj->m_type == "error") {
            printf("[ERROR] : %s\n", lObj->m_msg.c_str());
        }
        if(lObj->m_type == "tech_error") {
            printf("[ETECH] : %s\n", lObj->m_msg.c_str());
        }
        else if(lObj->m_type == "log") {
            printf("[INFOS] : %s\n", lObj->m_msg.c_str());
        }
        else if(lObj->m_type == "data") {
            //printf("[DATAS] :\n%s\n", GBase64(lObj->m_msg).decodeData().c_str());
        }
    }
    printf("\n");
}
//===============================================
bool GLog::hasErrors() const {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lObj = m_map.at(i);
        if(lObj->m_type == "error") return true;
        if(lObj->m_type == "tech_error") return true;
    }
    return false;
}
//===============================================
bool GLog::hasTechErrors() const {
    for(int i = 0; i < (int)m_map.size(); i++) {
        GLog* lObj = m_map.at(i);
        if(lObj->m_type == "tech_error") return true;
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
GString GLog::toJson() {
    GCode lDom;
    lDom.loadXml(serialize());
    return "lDom.toJson()";
}
//===============================================
