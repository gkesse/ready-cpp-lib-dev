//===============================================
#ifndef _GChatCB_
#define _GChatCB_
//===============================================
#include "GManager.h"
//===============================================
class GChatCB : public GManager {
public:
    GChatCB();
    ~GChatCB();
    void deserializeXml();
    void run();
    void runUser();
};
//===============================================
#endif
//===============================================
