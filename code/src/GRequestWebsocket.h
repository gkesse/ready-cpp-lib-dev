//===============================================
#ifndef _GRequestWebsocket_
#define _GRequestWebsocket_
//===============================================
#include "GObject.h"
//===============================================
class GRequestWebsocket : public GObject {
public:
    GRequestWebsocket();
    ~GRequestWebsocket();
    void setRequest(const GRequestWebsocket& _request);
    bool analyzeHeader();
    bool analyzeRequest();

    void setData(const GString& _data)          {m_data = _data;}
    int getTotal() const                        {return m_total;}
    const GString& getRequest() const           {return m_request;}

private:
    GString m_data;
    int m_pos;
    GString m_request;
    int m_total;
};
//===============================================
#endif
//===============================================
