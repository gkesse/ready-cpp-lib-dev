//===============================================
#ifndef _GCallbackXml_
#define _GCallbackXml_
//===============================================
#include "GCallback.h"
//===============================================
class GCallbackXml : public GCallback {
public:
    GCallbackXml();
    ~GCallbackXml();
    void run();
    void runCarpool();
    void runChat();
    void createResponse();
    void createOK();
    void createUnknown();
};
//===============================================
#endif
//===============================================
