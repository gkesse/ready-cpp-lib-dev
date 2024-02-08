//===============================================
#ifndef _GDispatcherHttpGet_
#define _GDispatcherHttpGet_
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
