//===============================================
#include "GDispatcherHttp.h"
#include "GRequestHttp.h"
//===============================================
GDispatcherHttp::GDispatcherHttp()
: GDispatcher() {

}
//===============================================
GDispatcherHttp::~GDispatcherHttp() {

}
//===============================================
void GDispatcherHttp::setDispatcher(const GDispatcher& _dispatcher) {
    m_method = _dispatcher.getHttp().getMethod();
    m_uri = _dispatcher.getHttp().getUri();
    m_version = _dispatcher.getHttp().getVersion();
    m_contentType = _dispatcher.getHttp().getContentType();
    m_secWebSocketKey = _dispatcher.getHttp().getSecWebSocketKey();
    m_request = _dispatcher.getHttp().getRequest();
    m_type = _dispatcher.getType();
}
//===============================================
