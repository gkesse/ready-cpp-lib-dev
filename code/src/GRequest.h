//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GObject.h"
#include "GRequestHttp.h"
//===============================================
class GRequest : public GObject {
public:
    enum class Type {
        REQ_TYPE_UNKNOWN
        , REQ_TYPE_HTTP_GET
        , REQ_TYPE_HTTP_POST
    };

public:
    GRequest();
    ~GRequest();
    void setData(const GString& _data);
    virtual void setRequest(const GRequest& _request);
    bool analyzeHeader();
    bool analyzeRequest();
    int getTotal() const;
    const GRequestHttp& getHttp() const;

protected:
    GRequestHttp m_http;
    GString m_data;
    Type m_type;
    int m_total;
};
//===============================================
#endif
//===============================================
