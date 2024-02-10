//===============================================
#include "GPage.h"
#include "GDispatcherHttp.h"
#include "GCarpoolUi.h"
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
    m_request = _page.m_request;
    m_type = _page.m_type;
}
//===============================================
void GPage::setDispatcher(const GDispatcherHttp& _dispatcher) {
    m_method = _dispatcher.getMethod();
    m_uri = _dispatcher.getUri();
    m_version = _dispatcher.getVersion();
    m_request = _dispatcher.getRequest();
    m_type = _dispatcher.getType();
}
//===============================================
void GPage::createHelloWrold() {
    slog(eGINF, "Création de la page hello world."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());

    GString lContent;
    lContent += sformat("Bonjour tout le monde.");

    GResponseHttp lResponse;
    lResponse.setObject(*this);
    lResponse.setContent(lContent);
    lResponse.create();
    m_response += lResponse.toResponse();
}
//===============================================
void GPage::createNotFound() {
    slog(eGINF, "Création de la page not found."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());

    GString lContent;
    lContent += sformat("Page non trouvée !!!");

    GResponseHttp lResponse;
    lResponse.setObject(*this);
    lResponse.setStatus(GResponseHttp::eGStatus::NotFound);
    lResponse.setContent(lContent);
    lResponse.create();
    m_response += lResponse.toResponse();
}
//===============================================
void GPage::createCarpool() {
    slog(eGINF, "Création de la page carpool."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());

    GCarpoolUi lPage;
    lPage.setObject(*this);
    lPage.setPage(*this);
    lPage.create();
    m_response += lPage.toResponse();
}
//===============================================
