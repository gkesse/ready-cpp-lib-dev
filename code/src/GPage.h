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
    void createCallback();
    void createCarpool();
    void createUnknown();

protected:
    GString m_method;
    GString m_uri;
    GString m_version;
    GString m_contentType;
    GString m_request;
};
//===============================================
#endif
//===============================================
