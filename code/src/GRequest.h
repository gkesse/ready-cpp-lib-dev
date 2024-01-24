//===============================================
#ifndef _GRequest_
#define _GRequest_
//===============================================
#include "GObject.h"
//===============================================
class GRequest {
public:
    class GHttp {
    public:
        GHttp();
        ~GHttp();
        void setData(const GString& _data);
        int getTotal() const;
        bool analyze();

    private:
        GString m_data;
        GString m_method;
        GString m_uri;
        GString m_version;
        int m_total;
    };

public:
    enum class Type {
        REQ_TYPE_UNKNOWN
        , REQ_TYPE_HTTP_GET
    };

public:
    GRequest();
    GRequest(const GRequest& _req);
    ~GRequest();
    void setData(const GString& _data);
    bool analyze();
    int getTotal() const;
    GRequest& operator=(const GRequest& _req);

private:
    GHttp m_http;
    GString m_data;
    Type m_type;
    int m_total;
};
//===============================================
#endif
//===============================================
