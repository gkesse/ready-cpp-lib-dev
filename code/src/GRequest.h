//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GSocket.h"
#include "GRequestHttp.h"
//===============================================
enum class eGRequestType {
    REQ_TYPE_UNKNOWN
    , REQ_TYPE_HTTP_GET
    , REQ_TYPE_HTTP_POST
};
//===============================================
class GRequest : public GSocket {
public:
    GRequest();
    ~GRequest();
    void setData(const GString& _data);
    virtual void setRequest(const GRequest& _obj);
    bool analyzeHeader();
    bool analyzeRequest();
    int getTotal() const;
    const eGRequestType& getType() const;
    const GRequestHttp& getHttp() const;

protected:
    GRequestHttp m_http;
    GString m_data;
    eGRequestType m_type;
    int m_total;
};
//===============================================
#endif
//===============================================
