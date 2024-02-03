//===============================================
#ifndef _GJson_
#define _GJson_
//===============================================
#include "GString.h"
//===============================================
class GJson {
public:
    GJson();
    GJson(struct json_object* _node);
    GJson(const GString& _name, const GString& _value, struct json_object* _node);
    GJson(const GJson& _json);
    virtual ~GJson();
    void clear();
    bool createObj();
    bool createArr();
    bool loadJson(const GString& _data);
    GJson addObj();
    GJson addObj(const GString& _key);
    GJson addArr(const GString& _key);
    void addData(const GString& _value);
    void addData(const GString& _key, const GString& _value);
    int countArr(const GString& _path) const;
    int countObj(const GString& _path) const;
    GJson getObj(const GString& _path) const;
    GJson getObj(const GString& _path, int _index) const;
    GString toString() const;
    GString toNode() const;
    GString toCode() const;
    GJson& operator=(const GJson& _json);

private:
    struct json_object* m_dom;
    struct json_object* m_node;
    GString m_name;
    GString m_value;
};
//===============================================
#endif
//===============================================
