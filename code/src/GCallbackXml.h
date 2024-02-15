//===============================================
#ifndef _GCallbackXml_
#define _GCallbackXml_
//===============================================
#include "GCallback.h"
#include "GErrorXml.h"
//===============================================
class GCallbackXml : public GCallback {
public:
    GCallbackXml();
    ~GCallbackXml();
    void createResponse();
    void createUnknown();

protected:
    GErrorXml m_errors;
};
//===============================================
#endif
//===============================================
