//===============================================
#ifndef _GResponse_
#define _GResponse_
//===============================================
#include "GObject.h"
//===============================================
class GResponse : public GObject {
public:
    GResponse();
    ~GResponse();
    void addResp(const GResponse& _resp);
    GString toResponse() const;
    GResponse& operator+=(const GString& _resp);
    GResponse& operator+=(const GResponse& _resp);

protected:
    GString m_response;
};
//===============================================
#endif
//===============================================