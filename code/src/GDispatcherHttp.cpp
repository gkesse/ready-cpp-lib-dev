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
