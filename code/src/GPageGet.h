//===============================================
#ifndef _GPageGet_
#define _GPageGet_
//===============================================
#include "GPage.h"
//===============================================
class GPageGet : public GPage {
public:
    GPageGet();
    ~GPageGet();
    void run();
    bool loadResource();
    void runCarpool();
    void runChat();
};
//===============================================
#endif
//===============================================
