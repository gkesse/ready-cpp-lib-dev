//===============================================
#ifndef _GPage_
#define _GPage_
//===============================================
#include "GResponseHttp.h"
//===============================================
class GDispatcherHttp;
//===============================================
class GPage : public GResponseHttp {
public:
    GPage();
    ~GPage();
    void setPage(const GPage& _page);
    void setDispatcher(const GDispatcherHttp& _dispatcher);
    void createHelloWrold();
    void createUnknown();
    void createCarpool();

protected:
    GString m_method;
    GString m_uri;
    GString m_version;
    GMap m_forms;
};
//===============================================
#endif
//===============================================
