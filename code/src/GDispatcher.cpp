//===============================================
#include "GDispatcher.h"
#include "GDispatcherHttpGet.h"
#include "GDispatcherHttpPost.h"
#include "GRequest.h"
//===============================================
GDispatcher::GDispatcher()
: GRequest() {

}
//===============================================
GDispatcher::~GDispatcher() {

}
//===============================================
const GResponse& GDispatcher::getResp() const {
    return m_response;
}
//===============================================
void GDispatcher::run() {
    if(m_type == Type::REQ_TYPE_HTTP_GET) {
        runHttpGet();
    }
    else if(m_type == Type::REQ_TYPE_HTTP_POST) {
        runHttpPost();
    }
    else {
        slog(eGERR, "Le type de la requête est inconnu."
                    "|adresse_ip=%s"
                    "|port=%d"
                    "|process=%d"
                    "|type=%d", m_addressIP.c_str(), m_port, m_pid, m_type);
    }
}
//===============================================
void GDispatcher::runHttpGet() {
    GDispatcherHttpGet lObj;
    lObj.setObject(*this);
    lObj.setDispatcher(*this);
    lObj.run();
    m_response.addResp(lObj.getResp());
}
//===============================================
void GDispatcher::runHttpPost() {
    GDispatcherHttpPost lObj;
    lObj.setObject(*this);
    lObj.setDispatcher(*this);
    lObj.run();
    m_response.addResp(lObj.getResp());
}
//===============================================
