//===============================================
#ifndef _GDispatcher_
#define _GDispatcher_
//===============================================
#include "GRequest.h"
//===============================================
class GDispatcher : public GRequest {
public:
    GDispatcher();
    ~GDispatcher();
    void run();
    void runHttpGet();
    void runHttpPost();
    void runWebsocket();
};
//===============================================
#endif
//===============================================
