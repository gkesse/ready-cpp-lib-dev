//===============================================
#ifndef _GCode_
#define _GCode_
//===============================================
#include "GXml.h"
//===============================================
class GLog;
class GObject;
//===============================================
class GCode : public GXml {
public:
    GCode();
    GCode(xmlDocPtr _doc2, xmlNodePtr _node2, xmlNodePtr _node);
    GCode(const GXml& _xml);
    ~GCode();
    GCode createDatas();
    GCode createCode(const GString& _code);
    void addData(const GString& _code, const GString& _name, const GString& _value);
    void addData(const GString& _code, const std::vector<GObject*>& _map);
    void addData(const GString& _code, const std::vector<GLog*>& _map);
    GString getData(const GString& _code, const GString& _name) const;
    void getData(const GString& _code, std::vector<GObject*>& _map, GObject* _obj);
    void getData(const GString& _code, std::vector<GLog*>& _map, GLog* _obj);
    void loadData(const GString& _data);
    GString toDatas(const GString& _data) const;
    GString toCode(const GString& _data) const;
    bool hasDatas() const;
};
//===============================================
#endif
//===============================================
