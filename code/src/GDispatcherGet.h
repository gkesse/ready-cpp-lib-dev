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
    bool isPage(const GString& _page);
    void runHelloWorld();
    void runCarpool();
    void runUnknown();

private:
    GString m_pageId;
};
//===============================================
#endif
//===============================================
