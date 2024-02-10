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
    void setData(const GString& _data);
    void setRequest(const GRequestHttp& _request);
    int getTotal() const;
    bool analyzeHeader();
    bool analyzeGet();
    bool analyzePost();
    const GString& getMethod() const;
    const GString& getUri() const;
    const GString& getVersion() const;
    const GString& getRequest() const;

private:
    GString m_data;
    GString m_method;
    GString m_uri;
    GString m_version;
    GString m_contentType;
    GString m_request;
    int m_total;
};
//===============================================
#endif
//===============================================
