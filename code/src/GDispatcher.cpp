//===============================================
#include "GDispatcher.h"
#include "GPageGet.h"
#include "GPageWebsocket.h"
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
    if(m_type == eGRequestType::REQ_TYPE_HTTP_GET) {
        runHttpGet();
    }
    else if(m_type == eGRequestType::REQ_TYPE_HTTP_POST) {
        runHttpPost();
    }
    else if(m_type == eGRequestType::REQ_TYPE_HTTP_WEBSOCKET) {
        runWebsocket();
    }
    else {
        slog(eGERR, "Le type de la requête est inconnu."
                    "|type=%d", m_type);
        m_logs.addProblem();
        createUnknown();
    }
}
//===============================================
void GDispatcher::runHttpGet() {
    GPageGet lObj;
    lObj.setCommon(*this);
    lObj.setRequest(*this);
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
void GDispatcher::runWebsocket() {
    GPageWebsocket lObj;
    lObj.setCommon(*this);
    lObj.setRequest(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponse(lObj);
}
//===============================================
