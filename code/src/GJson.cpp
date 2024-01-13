//===============================================
#include "GJson.h"
//===============================================
GJson::GJson() {
    m_dom = 0;
    m_node = 0;
}
//===============================================
GJson::GJson(struct json_object* _node) {
    m_dom = 0;
    m_node = _node;
}
//===============================================
GJson::GJson(const GJson& _json) {
    m_dom = 0;
    m_node = _json.m_node;
}
//===============================================
GJson::~GJson() {
    clear();
}
//===============================================
void GJson::clear() {
    if(m_dom) json_object_put(m_dom);
    m_dom = 0;
    m_node = 0;
}
//===============================================
bool GJson::createObj() {
    clear();
    m_dom = json_object_new_object();
    if(!m_dom) return false;
    m_node = m_dom;
    return true;
}
//===============================================
bool GJson::createArr() {
    clear();
    m_dom = json_object_new_array();
    if(!m_dom) return false;
    m_node = m_dom;
    return true;
}
//===============================================
bool GJson::loadXml(const GString& _data) {
    m_dom = json_tokener_parse(_data.c_str());
    if(!m_dom) return false;
    m_node = m_dom;
    return true;
}
//===============================================
GJson GJson::addObj() {
    if(!m_node) return GJson();
    if(json_object_get_type(m_node) != json_type_array) return GJson();
    struct json_object* lNode = json_object_new_object();
    json_object_array_add(m_node, lNode);
    return GJson(lNode);
}
//===============================================
GJson GJson::addObj(const GString& _key) {
    if(!m_node) return GJson();
    if(json_object_get_type(m_node) != json_type_object) return GJson();
    struct json_object* lNode = json_object_new_object();
    json_object_object_add(m_node, _key.c_str(), lNode);
    return GJson(lNode);
}
//===============================================
GJson GJson::addArr(const GString& _key) {
    if(!m_node) return GJson();
    if(json_object_get_type(m_node) != json_type_object) return GJson();
    struct json_object* lNode = json_object_new_array();
    json_object_object_add(m_node, _key.c_str(), lNode);
    return GJson(lNode);
}
//===============================================
void GJson::addData(const GString& _value) {
    if(!m_node) return;
    if(json_object_get_type(m_node) != json_type_array) return;
    json_object_array_add(m_node, json_object_new_string(_value.c_str()));
}
//===============================================
void GJson::addData(const GString& _key, const GString& _value) {
    if(!m_node) return;
    if(json_object_get_type(m_node) != json_type_object) return;
    json_object_object_add(m_node, _key.c_str(), json_object_new_string(_value.c_str()));
}
//===============================================
GString GJson::toString() const {
    if(!m_dom) return "";
    GString lData = json_object_to_json_string_ext(m_dom, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY);
    return lData;
}
//===============================================
GString GJson::toNode() const {
    if(!m_node) return "";
    GString lData = json_object_to_json_string_ext(m_node, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY);
    return lData;
}
//===============================================
GJson& GJson::operator=(const GJson& _json) {
    clear();
    m_node = _json.m_node;
    return *this;
}
//===============================================
