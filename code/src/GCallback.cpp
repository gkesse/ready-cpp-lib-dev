//===============================================
#include "GCallback.h"
#include "GCarpoolCB.h"
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
    if(m_uri.startsWith("/callback/carpool")) {
        runCarpool();
    }
    else {
        slog(eGERR, "Le callback n'est pas géré."
                    "|uri=%s"
                    "|content_type=%s"
                    "|request=%s", m_uri.c_str(), m_contentType.c_str(), m_request.c_str());
        createUnknown();
    }
}
//===============================================
void GCallback::runCarpool() {
    GCarpoolCB lObj;
    lObj.setCommon(*this);
    lObj.setPage(*this);
    lObj.run();
    m_response += lObj.toResponse();
}
//===============================================
