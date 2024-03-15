//===============================================
#ifndef _GDispatcherHttpGet_
#define _GDispatcherHttpGet_
//===============================================
#include "GDispatcherHttp.h"
#include "GPage.h"
//===============================================
class GDispatcherHttpGet : public GDispatcherHttp {
public:
    GDispatcherHttpGet();
    ~GDispatcherHttpGet();
    void run();
    bool loadResource();
    void runCarpool();
    void runChat();
};
//===============================================
#endif
//===============================================
