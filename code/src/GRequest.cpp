//===============================================
#include "GRequest.h"
#include "GRequestHttp.h"
//===============================================
GRequest::GRequest()
: GObject()
, m_type(Type::REQ_TYPE_UNKNOWN)
, m_total(0) {

}
//===============================================
GRequest::~GRequest() {

}
//===============================================
void GRequest::setData(const GString& _data) {
    m_data = _data;
}
//===============================================
void GRequest::setRequest(const GRequest& _request) {
    m_type = _request.m_type;
    m_http.setRequest(_request.m_http);
}
//===============================================
bool GRequest::analyzeHeader() {
    if(m_data.isEmpty()) return false;
    if(m_data.startsWith("GET")) {
        m_type = Type::REQ_TYPE_HTTP_GET;
        m_http.setData(m_data);
        if(!m_http.analyzeHeader()) {
            slog(eGERR, "L'analyse de la requête GET a échoué."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|type=%d"
                        "|size=%d"
                        "|data=%s", m_addressIP.c_str(), m_port, m_pid, m_type, m_data.size(), m_data.c_str());
            return false;
        }
        m_total = m_http.getTotal();
    }
    else if(m_data.startsWith("POST")) {
        m_type = Type::REQ_TYPE_HTTP_POST;
        m_http.setData(m_data);
        if(!m_http.analyzeHeader()) {
            slog(eGERR, "L'analyse de la requête POST a échoué."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|type=%d"
                        "|size=%d"
                        "|data=%s", m_addressIP.c_str(), m_port, m_pid, m_type, m_data.size(), m_data.c_str());
            return false;
        }
        m_total = m_http.getTotal();
    }
    else {
        slog(eGERR, "La méthode de la requête est inconnue."
                    "|adresse_ip=%s"
                    "|port=%d"
                    "|process=%d"
                    "|type=%d"
                    "|size=%d"
                    "|data=%s", m_addressIP.c_str(), m_port, m_pid, m_type, m_data.size(), m_data.c_str());
        m_type = Type::REQ_TYPE_UNKNOWN;
        m_total = m_data.size();
        return false;
    }
    return true;
}
//===============================================
bool GRequest::analyzeRequest() {
    if(m_data.isEmpty()) return false;
    if(m_data.startsWith("GET")) {
        m_type = Type::REQ_TYPE_HTTP_GET;
        m_http.setObject(*this);
        m_http.setData(m_data);
        if(!m_http.analyzeGet()) {
            slog(eGERR, "L'analyse de la requête HTTP a échoué."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|type=%d"
                        "|size=%d"
                        "|data=%s", m_addressIP.c_str(), m_port, m_pid, m_type, m_data.size(), m_data.c_str());
            return false;
        }
    }
    else if(m_data.startsWith("POST")) {
        m_type = Type::REQ_TYPE_HTTP_POST;
        m_http.setObject(*this);
        m_http.setData(m_data);
        if(!m_http.analyzePost()) {
            slog(eGERR, "L'analyse de la requête HTTP a échoué."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|type=%d"
                        "|size=%d"
                        "|data=%s", m_addressIP.c_str(), m_port, m_pid, m_type, m_data.size(), m_data.c_str());
            return false;
        }
    }
    else {
        slog(eGERR, "La méthode de la requête est inconnue."
                    "|adresse_ip=%s"
                    "|port=%d"
                    "|process=%d"
                    "|type=%d"
                    "|size=%d"
                    "|data=%s", m_addressIP.c_str(), m_port, m_pid, m_type, m_data.size(), m_data.c_str());
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
const GRequestHttp& GRequest::getHttp() const {
    return m_http;
}
//===============================================
