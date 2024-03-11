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
    if(m_contentType.startsWith("application/xml")) {
        runXml();
    }
    else {
        slog(eGERR, "Le content-type est inconnu."
                    "|uri=%s"
                    "|content_type=%s"
                    "|request=%s", m_uri.c_str(), m_contentType.c_str(), m_request.c_str());
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
