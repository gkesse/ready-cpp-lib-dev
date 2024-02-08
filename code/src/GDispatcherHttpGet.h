//===============================================
#ifndef _GDispatcherHttpGet_
#define _GDispatcherHttpGet_
//===============================================
#include "GDispatcherHttp.h"
//===============================================
class GDispatcherHttpGet : public GDispatcherHttp {
public:
    GDispatcherHttpGet();
    ~GDispatcherHttpGet();
    void run();
    bool loadResource();
    void runHelloWorld();
    void runCarpool();
    void runUnknown();
};
//===============================================
#endif
//===============================================