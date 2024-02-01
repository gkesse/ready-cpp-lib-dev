//===============================================
#include "GJson.h"
#include "GCode.h"
#include "GDebug.h"
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
GJson::GJson(const GString& _name, const GString& _value, struct json_object* _node) {
    m_dom = 0;
    m_node = _node;
    m_name = _name;
    m_value = _value;
}
//===============================================
GJson::GJson(const GJson& _json) {
    *this = _json;
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
    if(!m_dom) {
        slog(eGERR, "Erreur lors de la création de l'objet JSON.");
        return false;
    }
    m_node = m_dom;
    return true;
}
//===============================================
bool GJson::createArr() {
    clear();
    m_dom = json_object_new_array();
    if(!m_dom) {
        slog(eGERR, "Erreur lors de la création de l'objet JSON.");
        return false;
    }
    m_node = m_dom;
    return true;
}
//===============================================
bool GJson::loadJson(const GString& _data) {
    m_dom = json_tokener_parse(_data.c_str());
    if(!m_dom) {
        slog(eGERR, "Erreur lors du chargement du document JSON.");
        return false;
    }
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
int GJson::countArr(const GString& _path) const {
    if(!m_node) return 0;
    struct json_object* lNode;
    if(json_pointer_get(m_node, _path.c_str(), &lNode) < 0) return 0;
    return json_object_array_length(lNode);
}
//===============================================
int GJson::countObj(const GString& _path) const {
    if(!m_node) return 0;
    struct json_object* lNode;
    if(json_pointer_get(m_node, _path.c_str(), &lNode) < 0) return 0;
    return json_object_object_length(lNode);
}
//===============================================
GJson GJson::getObj(const GString& _path) const {
    if(!m_node) return GJson();
    struct json_object* lNode;
    if(json_pointer_get(m_node, _path.c_str(), &lNode) < 0) return GJson();
    return GJson(lNode);
}
//===============================================
GJson GJson::getObj(const GString& _path, int _index) const {
    if(!m_node) return GJson();
    struct json_object *lNode, *lNode2;
    GString lName, lValue;
    if(json_pointer_get(m_node, _path.c_str(), &lNode) < 0) return GJson();
    int lCount = json_object_object_length(lNode);
    if(!lCount) return GJson();
    struct json_object_iterator it = json_object_iter_begin(lNode);
    struct json_object_iterator itEnd = json_object_iter_end(lNode);
    int lIndex = 0;
    while(!json_object_iter_equal(&it, &itEnd) && lIndex < lCount) {
        lName = json_object_iter_peek_name(&it);
        lNode2 = json_object_iter_peek_value(&it);
        lValue = "";
        if(json_object_get_type(lNode2) != json_type_object &&
           json_object_get_type(lNode2) != json_type_array) {
            lValue = json_object_get_string(lNode2);
        }
        if(lIndex == _index) break;
        lIndex++;
        json_object_iter_next(&it);
    }

    return GJson(lName, lValue, lNode2);
}
//===============================================
GString GJson::toNode() const {
    if(!m_node) return "";
    GString lData = json_object_to_json_string_ext(m_node, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY);
    return lData;
}
//===============================================
GJson& GJson::operator=(const GJson& _json) {
    m_dom = 0;
    m_node = _json.m_node;
    m_name = _json.m_name;
    m_value = _json.m_value;
    return *this;
}
//===============================================
GString GJson::toCode() const {
    GCode lDom, lDom2, lDom3, lDom4, lDom5;
    GJson lJson;
    lDom.createDoc();
    int lCount = countArr("/datas");
    if(lCount) {
        lDom2 = lDom.addObj("datas");
        for(int i = 0; i < lCount; i++) {
            lDom3 = lDom2.addObj("data");
            lJson = getObj(sformat("/datas/%d", i));
            int lCount2 = countObj(sformat("/datas/%d", i));
            for(int i2 = 0; i2 < lCount2; i2++) {
                lJson = getObj(sformat("/datas/%d", i), i2);
                if(lJson.m_name != "map") {
                    lDom3.GXml::addData(lJson.m_name, lJson.m_value);
                }
                else {
                    int lCount3 = countArr(sformat("/datas/%d/map", i));
                    if(lCount3) {
                        lDom4 = lDom3.addObj("map");
                        for(int i3 = 0; i3 < lCount3; i3++) {
                            lDom5 = lDom4.addObj("data");
                            int lCount4 = countObj(sformat("/datas/%d/map/%d", i, i3));
                            for(int i4 = 0; i4 < lCount4; i4++) {
                                lJson = getObj(sformat("/datas/%d/map/%d", i, i3), i4);
                                lDom5.GXml::addData(lJson.m_name, lJson.m_value);
                            }
                        }
                    }
                }
            }
        }
    }
    return lDom.toString();
}
//===============================================
