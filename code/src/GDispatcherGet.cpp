//===============================================
#include "GDispatcherGet.h"
#include "GResponseHttp.h"
//===============================================
GDispatcherGet::GDispatcherGet()
: GDispatcher() {

}
//===============================================
GDispatcherGet::~GDispatcherGet() {

}
//===============================================
void GDispatcherGet::setDispatcher(const GDispatcher& _dispatcher) {
    m_method = _dispatcher.getHttp().getMethod();
    m_uri = _dispatcher.getHttp().getUri();
    m_version = _dispatcher.getHttp().getVersion();
}
//===============================================
void GDispatcherGet::run() {
    slog(eGINF, "Traitement de la requête HTTP GET."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());

    if(m_uri == "/hello/world") {
        runHelloWorld();
    }
    else {
        runUnknown();
    }
}
//===============================================
void GDispatcherGet::runHelloWorld() {
    GString lContent;
    lContent += sformat("Bonjour tout le monde.");

    GResponseHttp lResponse;
    lResponse.setContent(lContent);
    lResponse.create();

    m_response += lResponse;
}
//===============================================
void GDispatcherGet::runUnknown() {
    GString lContent;
    lContent += sformat("Page non trouvée.");

    GResponseHttp lResponse;
    lResponse.setStatus(GResponseHttp::eGStatus::NotFound);
    lResponse.setContent(lContent);
    lResponse.create();

    m_response += lResponse;
}
//===============================================
