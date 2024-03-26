//===============================================
#ifndef _GDispatcherHttp_
#define _GDispatcherHttp_
//===============================================
#include "GDispatcher.h"
#include "GPage.h"
//===============================================
class GDispatcherHttp : public GDispatcher {
public:
    GDispatcherHttp();
    ~GDispatcherHttp();
    void setDispatcher(const GDispatcher& _dispatcher);

    const GString& getMethod() const            {return m_method;}
    const GString& getUri() const               {return m_uri;}
    const GString& getVersion() const           {return m_version;}
    const GString& getContentType() const       {return m_contentType;}
    const GString& getSecWebSocketKey() const   {return m_secWebSocketKey;}
    const GString& getRequest() const           {return m_request;}

protected:
    GString m_method;
    GString m_uri;
    GString m_version;
    GString m_contentType;
    GString m_secWebSocketKey;
    GString m_request;
    GPage m_page;
};
//===============================================
#endif
//===============================================
