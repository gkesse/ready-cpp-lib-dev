//===============================================
#include "GResponse.h"
#include "GResponseUnknown.h"
//===============================================
GResponse::GResponse()
: GRequest() {

}
//===============================================
GResponse::~GResponse() {

}
//===============================================
void GResponse::addResp(const GResponse& _resp) {
    m_response += _resp.m_response;
}
//===============================================
GString GResponse::toResponse() const {
    if(m_response.isEmpty()) {
        GResponseUnknown lResp;
        lResp.create();
        return lResp.toResponse();
    }
    return m_response;
}
//===============================================
GResponse& GResponse::operator+=(const GString& _data) {
    m_response += _data;
    return *this;
}
//===============================================
GResponse& GResponse::operator+=(const GResponse& _resp) {
    m_response += _resp.m_response;
    return *this;
}
//===============================================
