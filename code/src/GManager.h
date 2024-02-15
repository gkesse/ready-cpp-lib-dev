//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GCallbackXml.h"
//===============================================
class GManager : public GCallbackXml {
public:
    GManager();
    ~GManager();
    GString serialize(const GString& _code = "manager") const;
    void deserialize(const GString& _data, const GString& _code = "manager");
    void run();

protected:
    GString m_module;
    GString m_method;
};
//===============================================
#endif
//===============================================
