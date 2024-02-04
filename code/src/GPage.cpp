//===============================================
#include "GPage.h"
#include "GDispatcherHttp.h"
//===============================================
GPage::GPage()
: GResponseHttp() {

}
//===============================================
GPage::~GPage() {

}
//===============================================
void GPage::setDispatcher(const GDispatcherHttp& _dispatcher) {
    m_method = _dispatcher.getMethod();
    m_uri = _dispatcher.getUri();
    m_version = _dispatcher.getVersion();
}
//===============================================
void GPage::createHelloWrold() {
    slog(eGINF, "Création de la page Hello World."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());

    GPage lPage;
    GString lContent;
    lContent += sformat("Bonjour tout le monde.");

    GResponseHttp lResponse;
    lResponse.setContent(lContent);
    lResponse.create();

    m_response += lResponse.toResponse();
}
//===============================================
void GPage::createHome() {
    slog(eGINF, "Création de la page Home."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());

    GPage lPage;
    GString lContent;
    lContent += sformat("<!DOCTYPE html>");
    lContent += sformat("<html lang='fr'>");
    lContent += sformat("<head>");
    lContent += sformat("<title>ReadyPad</title>");
    lContent += sformat("</head>");
    lContent += sformat("<body>");
    lContent += sformat("<h1>Bonjour Tout le Monde.</h1>");
    lContent += sformat("</body>");
    lContent += sformat("</html>");

    GResponseHttp lResponse;
    lResponse.setContent(lContent);
    lResponse.create();

    m_response += lResponse.toResponse();
}
//===============================================
void GPage::createUnknown() {
    slog(eGINF, "Création de la page Not Found."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());

    GResponseHttp lResponse;
    lResponse.setStatus(GResponseHttp::eGStatus::NotFound);
    lResponse.create();

    m_response += lResponse.toResponse();
}
//===============================================
