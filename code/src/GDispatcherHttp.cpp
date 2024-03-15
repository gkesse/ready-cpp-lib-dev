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
const GString& GDispatcherHttp::getMethod() const {
    return m_method;
}
//===============================================
const GString& GDispatcherHttp::getUri() const {
    return m_uri;
}
//===============================================
const GString& GDispatcherHttp::getVersion() const {
    return m_version;
}
//===============================================
const GString& GDispatcherHttp::getContentType() const {
    return m_contentType;
}
//===============================================
const GString& GDispatcherHttp::getSecWebSocketKey() const {
    return m_secWebSocketKey;
}
//===============================================
const GString& GDispatcherHttp::getRequest() const {
    return m_request;
}
//===============================================
