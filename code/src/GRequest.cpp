//===============================================
#include "GRequest.h"
//===============================================
// GRequest
//===============================================
GRequest::GRequest() {
    m_type = Type::REQ_TYPE_UNKNOWN;
    m_total = 0;
}
//===============================================
GRequest::GRequest(const GRequest& _req) {
    *this = _req;
}
//===============================================
GRequest::~GRequest() {

}
//===============================================
void GRequest::setData(const GString& _data) {
    m_data = _data;
}
//===============================================
bool GRequest::analyze() {
    if(m_data.isEmpty()) return false;
    if(m_data.startsWith("GET")) {
        m_type = Type::REQ_TYPE_HTTP_GET;
        m_http.setData(m_data);
        if(!m_http.analyze()) return false;
        m_total = m_http.getTotal();
    }
    else {
        m_type = Type::REQ_TYPE_UNKNOWN;
        m_total = m_data.size();
        return false;
    }
    return true;
}
//===============================================
int GRequest::getTotal() const {
    return m_total;
}
//===============================================
GRequest& GRequest::operator=(const GRequest& _req) {
    m_data = _req.m_data;
    m_type = _req.m_type;
    return *this;
}
//===============================================
// GRequest::GHttp
//===============================================
GRequest::GHttp::GHttp() {
    m_total = 0;
}
//===============================================
GRequest::GHttp::~GHttp() {

}
//===============================================
void GRequest::GHttp::setData(const GString& _data) {
    m_data = _data;
}
//===============================================
int GRequest::GHttp::getTotal() const {
    return m_total;
}
//===============================================
bool GRequest::GHttp::analyze() {
    if(m_data.isEmpty()) return false;
    const GString CRLF = "\r\n";
    const GString CRLFCRLF = "\r\n\r\n";
    int lContentLenght = m_data.extract("Content-Length:", CRLF).trim().toInt();
    GString lHeader = m_data.extract(CRLFCRLF);
    if(lHeader.isEmpty()) {
        sformat("Impossible de continuer, le HEADER de la requête HTTP est NUL."
                "|data=%s", m_data.c_str()).print();
        return false;
    }
    m_total = lHeader.size() + CRLFCRLF.size() + lContentLenght;
    return true;
}
//===============================================
