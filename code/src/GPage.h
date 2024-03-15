//===============================================
#ifndef _GPage_
#define _GPage_
//===============================================
#include "GResponseHttp.h"
//===============================================
class GRequestHttp;
class GDispatcherHttp;
//===============================================
class GPage : public GResponseHttp {
public:
    GPage();
    ~GPage();
    void setPage(const GPage& _obj);
    void setRequest(const GRequest& _obj);
    void setDispatcher(const GDispatcherHttp& _obj);
    void createResponse();
    void createOK();
    void createUnknown();

protected:
    GString m_method;
    GString m_uri;
    GString m_version;
    GString m_contentTypeReq;
    GString m_request;
};
//===============================================
#endif
//===============================================
