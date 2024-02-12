//===============================================
#include "GCallback.h"
//===============================================
GCallback::GCallback()
: GPage() {

}
//===============================================
GCallback::~GCallback() {

}
//===============================================
void GCallback::run() {
    if(m_contentType == "application/xml") {
        runXml();
    }
    else {
        slog(eGERR, "Le content-type n'est pas géré."
                    "|uri=%s"
                    "|content_type=%s"
                    "|request=%s", m_uri.c_str(), m_contentType.c_str(), m_request.c_str());
        createUnknown();
    }
}
//===============================================
void GCallback::runXml() {
    GXml lDom;
    lDom.loadXml(m_request);

    if(m_uri.startsWith("/callback/carpool")) {
        runCarpool();
    }
    else {
        createUnknown();
    }
}
//===============================================
void GCallback::runCarpool() {
    createUnknown();
}
//===============================================
