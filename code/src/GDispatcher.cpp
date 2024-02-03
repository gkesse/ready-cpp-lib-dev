//===============================================
#include "GDispatcher.h"
#include "GDispatcherGet.h"
#include "GRequest.h"
//===============================================
GDispatcher::GDispatcher()
: GRequest() {

}
//===============================================
GDispatcher::~GDispatcher() {

}
//===============================================
void GDispatcher::run() {
    if(m_type == Type::REQ_TYPE_HTTP_GET) {
        runGet();
    }
}
//===============================================
void GDispatcher::runGet() {
    GDispatcherGet lObj;
    lObj.setObject(*this);
    lObj.setDispatcher(*this);
    lObj.run();
}
//===============================================
