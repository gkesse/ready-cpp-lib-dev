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
    GJson(const GJson& _xml);
    virtual ~GJson();
    void clear();
    bool create();

private:
    json_object* m_current;
    std::stack<json_object*> m_map;
    json_object* m_parent;
    json_object* m_child;
    bool m_isFormat;
};
//===============================================
#endif
//===============================================
