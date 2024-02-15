//===============================================
#include "GPage.h"
#include "GDispatcherHttp.h"
#include "GCarpoolUi.h"
#include "GCallback.h"
//===============================================
GPage::GPage()
: GResponseHttp() {

}
//===============================================
GPage::~GPage() {

}
//===============================================
void GPage::setPage(const GPage& _page) {
    m_method = _page.m_method;
    m_uri = _page.m_uri;
    m_version = _page.m_version;
    m_contentType = _page.m_contentType;
    m_request = _page.m_request;
    m_type = _page.m_type;
}
//===============================================
void GPage::setDispatcher(const GDispatcherHttp& _dispatcher) {
    m_method = _dispatcher.getMethod();
    m_uri = _dispatcher.getUri();
    m_version = _dispatcher.getVersion();
    m_contentType = _dispatcher.getContentType();
    m_request = _dispatcher.getRequest();
    m_type = _dispatcher.getType();
}
//===============================================
void GPage::createCallback() {
    slog(eGINF, "Traitement du callback."
                "|uri=%s"
                "|request=%s", m_uri.c_str(), m_request.c_str());

    GCallback lPage;
    lPage.setCommon(*this);
    lPage.setPage(*this);
    lPage.run();
    m_response += lPage.toResponse();
}
//===============================================
void GPage::createCarpool() {
    slog(eGINF, "Création de la page carpool."
                "|uri=%s", m_uri.c_str());

    GCarpoolUi lPage;
    lPage.setCommon(*this);
    lPage.setPage(*this);
    lPage.create();
    m_response += lPage.toResponse();
}
//===============================================
void GPage::createUnknown() {
    slog(eGWAR, "La ressource est introuvable."
                "|uri=%s", m_uri.c_str());

    GString lContent;
    lContent += sformat("Page non trouvée.");

    GResponseHttp lResponse;
    lResponse.setCommon(*this);
    lResponse.setContent(lContent);
    lResponse.create();
    m_response += lResponse.toResponse();
}
//===============================================
