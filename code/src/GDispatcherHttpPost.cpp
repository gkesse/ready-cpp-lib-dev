//===============================================
#include "GDispatcherHttpPost.h"
#include "GPage.h"
//===============================================
GDispatcherHttpPost::GDispatcherHttpPost()
: GDispatcherHttp() {

}
//===============================================
GDispatcherHttpPost::~GDispatcherHttpPost() {

}
//===============================================
void GDispatcherHttpPost::run() {
    slog(eGINF, "Traitement de la requête HTTP POST."
                "|uri=%s", m_uri.c_str());

    if(m_uri.startsWith("/callback")) {
        runCallback();
    }
    else if(m_uri.startsWith("/carpool")) {
        runCarpool();
    }
    else {
        createUnknown();
    }
}
//===============================================
void GDispatcherHttpPost::runCallback() {
    GPage lPage;
    lPage.setCommon(*this);
    lPage.setDispatcher(*this);
    lPage.createCallback();
    m_logs.addLogs(lPage.getLogs());
    setResponse(lPage);
}
//===============================================
void GDispatcherHttpPost::runCarpool() {
    GPage lPage;
    lPage.setCommon(*this);
    lPage.setDispatcher(*this);
    lPage.createCarpool();
    m_logs.addLogs(lPage.getLogs());
    setResponse(lPage);
}
//===============================================
void GDispatcherHttpPost::createUnknown() {
    GPage lPage;
    lPage.setCommon(*this);
    lPage.setDispatcher(*this);
    lPage.createUnknown();
    m_logs.addLogs(lPage.getLogs());
    setResponse(lPage);
}
//===============================================
