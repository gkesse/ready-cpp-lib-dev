//===============================================
#include "GDispatcherHttp.h"
#include "GRequestHttp.h"
//===============================================
GDispatcherHttp::GDispatcherHttp()
: GDispatcher() {
    m_forms.createMap();
}
//===============================================
GDispatcherHttp::~GDispatcherHttp() {

}
//===============================================
void GDispatcherHttp::setDispatcher(const GDispatcher& _dispatcher) {
    m_method = _dispatcher.getHttp().getMethod();
    m_uri = _dispatcher.getHttp().getUri();
    m_version = _dispatcher.getHttp().getVersion();
    m_forms.loadMap(_dispatcher.getHttp().getForms());
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
const GMap& GDispatcherHttp::getForms() const {
    return m_forms;
}
//===============================================
