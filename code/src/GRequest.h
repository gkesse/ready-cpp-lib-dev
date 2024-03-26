//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GSocket.h"
#include "GRequestHttp.h"
#include "GRequestWebsocket.h"
//===============================================
class GRequest : public GSocket {
public:
    GRequest();
    ~GRequest();
    virtual void setRequest(const GRequest& _obj);
    bool analyzeHeader();
    bool analyzeRequest();

    void setData(const GString& _data)              {m_data = _data;}
    int getTotal() const                            {return m_total;}
    const GRequestHttp& getHttp() const             {return m_http;}
    const GRequestWebsocket& getWebsocket() const   {return m_websocket;}

protected:
    GRequestHttp m_http;
    GRequestWebsocket m_websocket;
    GString m_data;
    int m_total;
};
//===============================================
#endif
//===============================================
