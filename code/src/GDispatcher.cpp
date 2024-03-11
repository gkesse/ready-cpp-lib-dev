//===============================================
#include "GDispatcher.h"
#include "GDispatcherHttpGet.h"
#include "GDispatcherHttpPost.h"
//===============================================
GDispatcher::GDispatcher()
: GRequest() {

}
//===============================================
GDispatcher::~GDispatcher() {

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
                    "|type=%d", m_type);
        createUnknown();
    }
}
//===============================================
void GDispatcher::runHttpGet() {
    GDispatcherHttpGet lObj;
    lObj.setCommon(*this);
    lObj.setDispatcher(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponse(lObj);
}
//===============================================
void GDispatcher::runHttpPost() {
    GDispatcherHttpPost lObj;
    lObj.setCommon(*this);
    lObj.setDispatcher(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponse(lObj);
}
//===============================================
