//===============================================
#include "GDispatcherHttpGet.h"
#include "GPageGet.h"
#include "GResponseHttp.h"
#include "GResourceUi.h"
#include "GCarpoolUi.h"
#include "GChatUi.h"
//===============================================
GDispatcherHttpGet::GDispatcherHttpGet()
: GDispatcherHttp() {

}
//===============================================
GDispatcherHttpGet::~GDispatcherHttpGet() {

}
//===============================================
void GDispatcherHttpGet::run() {
    GPageGet lObj;
    lObj.setCommon(*this);
    lObj.setDispatcher(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponse(lObj);
}
//===============================================
bool GDispatcherHttpGet::loadResource() {
    GResourceUi lObj;
    lObj.setCommon(*this);
    lObj.setDispatcher(*this);
    if(lObj.loadResource()) {
        m_page.setResponseHttp(lObj);
        return true;
    }
    return false;
}
//===============================================
void GDispatcherHttpGet::runCarpool() {
    GCarpoolUi lObj;
    lObj.setCommon(*this);
    lObj.setDispatcher(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    m_page.setResponseHttp(lObj);
}
//===============================================
void GDispatcherHttpGet::runChat() {
    GChatUi lObj;
    lObj.setCommon(*this);
    lObj.setDispatcher(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    m_page.setResponseHttp(lObj);
}
//===============================================
