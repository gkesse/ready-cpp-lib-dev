//===============================================
#include "GCallback.h"
#include "GCallbackXml.h"
//===============================================
GCallback::GCallback()
: GPage() {

}
//===============================================
GCallback::~GCallback() {

}
//===============================================
void GCallback::run() {
    if(m_contentTypeReq.startsWith("application/xml")) {
        runXml();
    }
    else {
        slog(eGERR, "Le content-type est inconnu."
                    "|uri=%s"
                    "|contentTypeRequest=%s"
                    "|request=%s", m_uri.c_str(), m_contentTypeReq.c_str(), m_request.c_str());
        createUnknown();
    }
}
//===============================================
void GCallback::runXml() {
    GCallbackXml lObj;
    lObj.setCommon(*this);
    lObj.setPage(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponse(lObj);
}
//===============================================
