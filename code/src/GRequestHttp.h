//===============================================
#ifndef _GRequestHttp_
#define _GRequestHttp_
//===============================================
#include "GObject.h"
//===============================================
class GRequestHttp : public GObject {
public:
    GRequestHttp();
    ~GRequestHttp();
    void setRequest(const GRequestHttp& _request);
    bool analyzeHeader();
    bool analyzeGet();
    bool analyzePost();

    void setData(const GString& _data)          {m_data = _data;}
    int getTotal() const                        {return m_total;}
    const GString& getMethod() const            {return m_method;}
    const GString& getUri() const               {return m_uri;}
    const GString& getVersion() const           {return m_version;}
    const GString& getContentType() const       {return m_contentType;}
    const GString& getSecWebSocketKey() const   {return m_secWebSocketKey;}
    const GString& getRequest() const           {return m_request;}
    bool isWebsocket() const                    {return (!m_secWebSocketKey.isEmpty());}

private:
    GString m_data;
    GString m_method;
    GString m_uri;
    GString m_version;
    GString m_contentType;
    GString m_secWebSocketKey;
    GString m_request;
    int m_total;
};
//===============================================
#endif
//===============================================
