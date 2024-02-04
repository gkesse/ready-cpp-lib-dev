//===============================================
#ifndef _GDispatcherGet_
#define _GDispatcherGet_
//===============================================
#include "GDispatcherHttp.h"
//===============================================
class GDispatcherGet : public GDispatcherHttp {
public:
    GDispatcherGet();
    ~GDispatcherGet();
    void run();
    void runHelloWorld();
    void runHome();
    void runUnknown();
};
//===============================================
#endif
//===============================================
