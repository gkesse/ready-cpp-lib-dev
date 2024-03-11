//===============================================
#include "GChatCB.h"
#include "GChatUser.h"
//===============================================
GChatCB::GChatCB()
: GManager() {

}
//===============================================
GChatCB::~GChatCB() {

}
//===============================================
void GChatCB::deserializeXml() {
    GXml lDom;
    lDom.loadXml(m_request);
    m_module = lDom.getNode("/datas/module").getValue();
    m_method = lDom.getNode("/datas/method").getValue();
}
//===============================================
void GChatCB::run() {
    deserializeXml();

    if(m_module == "user") {
        runUser();
    }
    else {
        slog(eGERR, "Le module est inconnu."
                    "|module=%s", m_module.c_str());
        createUnknown();
    }
}
//===============================================
void GChatCB::runUser() {
    GChatUser lObj;
    lObj.setCommon(*this);
    lObj.setManager(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponseHttp(lObj);
}
//===============================================
