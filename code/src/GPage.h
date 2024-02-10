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
    void createNotFound();
    void createCarpool();

protected:
    GString m_method;
    GString m_uri;
    GString m_version;
    GString m_request;
};
//===============================================
#endif
//===============================================
