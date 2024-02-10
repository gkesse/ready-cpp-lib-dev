//===============================================
#include "GDispatcherHttpPost.h"
#include "GPage.h"
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
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d"
                "|uri=%s", m_addressIP.c_str(), m_port, m_pid, m_uri.c_str());

    if(m_uri.startsWith("/callback")) {
        runCallback();
    }
    else if(m_uri.startsWith("/carpool")) {
        runCarpool();
    }
    else {
        runNotFound();
    }
}
//===============================================
void GDispatcherHttpPost::runCallback() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createCarpool();
    m_response += lPage;
}
//===============================================
void GDispatcherHttpPost::runCarpool() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createCarpool();
    m_response += lPage;
}
//===============================================
void GDispatcherHttpPost::runNotFound() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createNotFound();
    m_response += lPage;
}
//===============================================
