//===============================================
#include "GDispatcherGet.h"
#include "GResponseHttp.h"
#include "GPage.h"
//===============================================
GDispatcherGet::GDispatcherGet()
: GDispatcherHttp() {

}
//===============================================
GDispatcherGet::~GDispatcherGet() {

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
    else if(m_uri == "/home") {
        runHome();
    }
    else {
        runUnknown();
    }
}
//===============================================
void GDispatcherGet::runHelloWorld() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createHelloWrold();
    m_response += lPage;
}
//===============================================
void GDispatcherGet::runHome() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createHome();
    m_response += lPage;
}
//===============================================
void GDispatcherGet::runUnknown() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createUnknown();
    m_response += lPage;
}
//===============================================
