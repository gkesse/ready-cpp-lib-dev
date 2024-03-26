//===============================================
#include "GRequest.h"
#include "GRequestHttp.h"
//===============================================
GRequest::GRequest()
: GSocket()
, m_total(0) {

}
//===============================================
GRequest::~GRequest() {

}
//===============================================
void GRequest::setRequest(const GRequest& _obj) {
    m_type                  = _obj.m_type;
    m_http.setRequest       (_obj.m_http);
    m_websocket.setRequest  (_obj.m_websocket);
}
//===============================================
bool GRequest::analyzeHeader() {
    if(m_data.isEmpty()) return false;
    if(m_data.startsWith("GET")) {
        m_type = eGRequestType::REQ_TYPE_HTTP_GET;
        m_http.setData(m_data);
        if(!m_http.analyzeHeader()) {
            slog(eGERR, "L'analyse de la requête GET a échoué."
                        "|type=%d"
                        "|size=%d"
                        "|data=%s", m_type, m_data.size(), m_data.c_str());
            return false;
        }
        m_total = m_http.getTotal();
    }
    else if(m_data.startsWith("POST")) {
        m_type = eGRequestType::REQ_TYPE_HTTP_POST;
        m_http.setData(m_data);
        if(!m_http.analyzeHeader()) {
            slog(eGERR, "L'analyse de la requête POST a échoué."
                        "|type=%d"
                        "|size=%d"
                        "|data=%s", m_type, m_data.size(), m_data.c_str());
            return false;
        }
        m_total = m_http.getTotal();
    }
    else if(m_type == eGRequestType::REQ_TYPE_HTTP_WEBSOCKET) {
        m_websocket.setData(m_data);
        if(!m_websocket.analyzeHeader()) {
            slog(eGERR, "L'analyse de la requête WEBSOCKET a échoué."
                        "|type=%d"
                        "|size=%d"
                        "|data=%s", m_type, m_data.size(), m_data.c_str());
            return false;
        }
        m_total = m_websocket.getTotal();
    }
    else {
        slog(eGERR, "La méthode de la requête est inconnue."
                    "|type=%d"
                    "|size=%d"
                    "|data=%s", m_type, m_data.size(), m_data.c_str());
        m_type = eGRequestType::REQ_TYPE_UNKNOWN;
        m_total = m_data.size();
        return false;
    }

    return !m_logs.hasErrors();
}
//===============================================
bool GRequest::analyzeRequest() {
    if(m_data.isEmpty()) return false;
    if(m_data.startsWith("GET")) {
        m_type = eGRequestType::REQ_TYPE_HTTP_GET;
        m_http.setCommon(*this);
        m_http.setData(m_data);
        if(!m_http.analyzeGet()) {
            slog(eGERR, "L'analyse de la requête HTTP GET a échoué."
                        "|type=%d"
                        "|size=%d"
                        "|data=%s", m_type, m_data.size(), m_data.c_str());
            return false;
        }
        if(m_http.isWebsocket()) {
            m_type = eGRequestType::REQ_TYPE_HTTP_WEBSOCKET;
        }
    }
    else if(m_data.startsWith("POST")) {
        m_type = eGRequestType::REQ_TYPE_HTTP_POST;
        m_http.setCommon(*this);
        m_http.setData(m_data);
        if(!m_http.analyzePost()) {
            slog(eGERR, "L'analyse de la requête HTTP POST a échoué."
                        "|type=%d"
                        "|size=%d"
                        "|data=%s", m_type, m_data.size(), m_data.c_str());
            return false;
        }
    }
    else if(m_type == eGRequestType::REQ_TYPE_HTTP_WEBSOCKET) {
        m_websocket.setData(m_data);
        if(!m_websocket.analyzeRequest()) {
            slog(eGERR, "L'analyse de la requête WEBSOCKET a échoué."
                        "|type=%d"
                        "|size=%d", m_type, m_data.size());
            return false;
        }
        setCommon(m_websocket);
    }
    else {
        slog(eGERR, "La méthode de la requête est inconnue."
                    "|type=%d"
                    "|size=%d"
                    "|data=%s", m_type, m_data.size(), m_data.c_str());
        m_type = eGRequestType::REQ_TYPE_UNKNOWN;
        m_total = m_data.size();
        return false;
    }

    return !m_logs.hasErrors();
}
//===============================================
