//===============================================
#ifndef _GDispatcherHttpPost_
#define _GDispatcherHttpPost_
//===============================================
#include "GDispatcherHttp.h"
//===============================================
class GDispatcherHttpPost : public GDispatcherHttp {
public:
    GDispatcherHttpPost();
    ~GDispatcherHttpPost();
    void run();
    void runCarpool();
    void runUnknown();
};
//===============================================
#endif
//===============================================
