//===============================================
#include "GDispatcherHttpPost.h"
#include "GResponseHttp.h"
#include "GPage.h"
#include "GFile.h"
#include "GMimeType.h"
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

    if(m_uri.startsWith("/carpool")) {
        runCarpool();
    }
    else {
        runUnknown();
    }
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
void GDispatcherHttpPost::runUnknown() {
    GPage lPage;
    lPage.setObject(*this);
    lPage.setDispatcher(*this);
    lPage.createUnknown();
    m_response += lPage;
}
//===============================================
