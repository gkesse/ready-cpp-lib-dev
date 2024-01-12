//===============================================
#include "GCode.h"
#include "GLog.h"
#include "GObject.h"
//===============================================
GCode::GCode()
: GXml() {

}
//===============================================
GCode::GCode(xmlDocPtr _doc2, xmlNodePtr _node2, xmlNodePtr _node)
: GXml(_doc2, _node2, _node) {

}
//===============================================
GCode::GCode(const GXml& _xml)
: GXml(_xml) {

}
//===============================================
GCode::~GCode() {

}
//===============================================
GCode GCode::createDatas() {
    GCode lDom = getNode(sformat("/rdv/datas"));
    if(lDom.isEmpty()) {
        lDom = lDom.addNode(sformat("/rdv/datas"));
    }
    return lDom;
}
//===============================================
GCode GCode::createCode(const GString& _code) {
    GCode lDom = getNode(sformat("/rdv/datas/data[code='%s']", _code.c_str()));
    if(lDom.isEmpty()) {
        lDom = createDatas();
        lDom = lDom.addObj("data");
        lDom.GXml::addData("code", _code);
    }
    return lDom;
}
//===============================================
void GCode::addData(const GString& _code, const GString& _name, const GString& _value) {
    if(_value.isEmpty()) return;
    GCode lDom = getNode(sformat("/rdv/datas/data[code='%s']/%s", _code.c_str(), _name.c_str()));
    if(lDom.isEmpty()) {
        lDom = createCode(_code);
        lDom.GXml::addData(_name, _value);
    }
    else {
        lDom.setValue(_value);
    }
}
//===============================================
void GCode::addData(const GString& _code, const std::vector<GObject*>& _map) {
    int lSize = (int)_map.size();
    if(!lSize) return;

    GCode lDom = getNode(sformat("/rdv/datas/data[code='%s']/map", _code.c_str()));
    if(lDom.isEmpty()) {
        lDom = createCode(_code);
        lDom = lDom.addObj("map");
    }

    for(int i = 0; i < lSize; i++) {
        GObject* lObj = _map[i];
        GString lData = lObj->serialize(_code);
        lData = toDatas(lData);
        lDom.loadNode(lData);
    }
}
//===============================================
void GCode::addData(const GString& _code, const std::vector<GLog*>& _map) {
    int lSize = (int)_map.size();
    if(!lSize) return;

    GCode lDom = getNode(sformat("/rdv/datas/data[code='%s']/map", _code.c_str()));
    if(lDom.isEmpty()) {
        lDom = createCode(_code);
        lDom = lDom.addObj("map");
    }

    for(int i = 0; i < lSize; i++) {
        GLog* lObj = _map[i];
        GString lData = lObj->serialize(_code);
        lData = toDatas(lData);
        lDom.loadNode(lData);
    }
}
//===============================================
GString GCode::getData(const GString& _code, const GString& _name) const {
    GCode lDom = getNode(sformat("/rdv/datas/data[code='%s']/%s", _code.c_str(), _name.c_str()));
    if(lDom.isEmpty()) return "";
    return lDom.getValue();
}
//===============================================
void GCode::getData(const GString& _code, std::vector<GObject*>& _map, GObject* _obj) {
    _obj->clearMap();

    int lCount = countNode(sformat("/rdv/datas/data[code='%s']/map/data", _code.c_str()));

    if(!lCount) return;

    for(int i = 0; i < lCount; i++) {
        GCode lDom = getNode(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code.c_str(), i + 1));
        GString lData = lDom.toNode();
        lData = toCode(lData);
        GObject* lObj = _obj->clone();
        lObj->deserialize(lData, _code);
        _map.push_back(lObj);
    }
}
//===============================================
void GCode::getData(const GString& _code, std::vector<GLog*>& _map, GLog* _obj) {
    _obj->clearMap();

    int lCount = countNode(sformat("/rdv/datas/data[code='%s']/map/data", _code.c_str()));

    if(!lCount) return;

    for(int i = 0; i < lCount; i++) {
        GCode lDom = getNode(sformat("/rdv/datas/data[code='%s']/map/data[position()=%d]", _code.c_str(), i + 1));
        GString lData = lDom.toNode();
        lData = toCode(lData);
        GLog* lObj = _obj->clone();
        lObj->deserialize(lData, _code);
        _map.push_back(lObj);
    }
}
//===============================================
void GCode::loadData(const GString& _data) {
    if(_data.isEmpty()) return;
    GCode lDom = createDatas();
    GString lData = toDatas(_data);
    lDom.loadNode(lData);
}
//===============================================
GString GCode::toDatas(const GString& _data) const {
    if(_data.isEmpty()) return "";
    GCode lDom;
    if(!lDom.loadXml(_data)) return "";
    GCode lDom2 = lDom.getNode(sformat("/rdv/datas"));
    return lDom2.toNode();
}
//===============================================
GString GCode::toCode(const GString& _data) const {
    if(_data.isEmpty()) return "";
    GCode lDom;
    lDom.createDoc();
    lDom = lDom.createDatas();
    GString lData = sformat("<rdv>%s</rdv>", _data.c_str());
    lDom.loadNode(lData);
    return lDom.toString();
}
//===============================================
bool GCode::hasDatas() const {
    return existNode(sformat("/rdv/datas/data[code]"));
}
//===============================================
