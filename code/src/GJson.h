//===============================================
#ifndef _GJson_
#define _GJson_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GJson {
public:
    GJson();
    GJson(struct json_object* _node);
    GJson(const GJson& _json);
    virtual ~GJson();
    void clear();
    bool createObj();
    bool createArr();
    bool loadXml(const GString& _data);
    GJson addObj();
    GJson addObj(const GString& _key);
    GJson addArr(const GString& _key);
    void addData(const GString& _value);
    void addData(const GString& _key, const GString& _value);
    GString toString() const;
    GString toNode() const;

    GJson& operator=(const GJson& _json);

private:
    struct json_object* m_dom;
    struct json_object* m_node;
};
//===============================================
#endif
//===============================================
