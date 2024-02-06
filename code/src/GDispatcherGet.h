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
    bool loadResource();
    void runHelloWorld();
    void runCarpool();
    void runUnknown();
};
//===============================================
#endif
//===============================================
