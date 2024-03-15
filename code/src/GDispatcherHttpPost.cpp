//===============================================
#include "GDispatcherHttpPost.h"
#include "GCallback.h"
#include "GCarpoolUi.h"
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
        slog(eGERR, "L'uri n'est pas gérée."
                    "|uri=%s", m_uri.c_str());
        m_logs.addProblem();
        m_page.createUnknown();
    }
    m_page.createResponse();
    setResponse(m_page);
}
//===============================================
void GDispatcherHttpPost::runCallback() {
    GCallback lObj;
    lObj.setCommon(*this);
    lObj.setDispatcher(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    m_page.setResponseHttp(lObj);
}
//===============================================
void GDispatcherHttpPost::runCarpool() {
    GCarpoolUi lObj;
    lObj.setCommon(*this);
    lObj.setDispatcher(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    m_page.setResponseHttp(lObj);
}
//===============================================
