//===============================================
#ifndef _GResponseHttp_
#define _GResponseHttp_
//===============================================
#include "GObject.h"
//===============================================
class GResponseHttp : public GObject {
public:
    struct sGStatus {
        bool flag;
        int code;
        const char* name;
        const char* desc;
    };

public:
    GResponseHttp();
    ~GResponseHttp();
    void setStatus(int _status);
    void setContentType(const GString& _contentType);
    void setData(const GString& _data);
    GString toReason(int _status) const;
    GString toResponse() const;
    GString toError() const;

private:
    int m_status;
    GString m_data;
    GString m_contentType;
    GString m_connection;
};
//===============================================
#endif
//===============================================
