//===============================================
#include "GDispatcherGet.h"
#include "GRequest.h"
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
}
//===============================================
