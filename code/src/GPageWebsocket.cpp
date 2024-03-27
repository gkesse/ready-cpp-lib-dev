//===============================================
#include "GPageWebsocket.h"
#include "GResponseWebsocket.h"
//===============================================
GPageWebsocket::GPageWebsocket()
: GPage() {

}
//===============================================
GPageWebsocket::~GPageWebsocket() {

}
//===============================================
void GPageWebsocket::run() {
    slog(eGINF, "Traitement de la requête WEBSOCKET."
                "|uri=%s"
                "|isContinue=%d"
                "|type=%d"
                "|secWebSocketKey=%s", m_uri.c_str(), m_isContinue, m_type, m_secWebSocketKey.c_str());
    if(!m_isContinue) {
        m_isContinue = true;
        createResponse();
    }
    else if(m_isClose) {
        GResponseWebsocket lObj;
        lObj.setCommon(*this);
        lObj.createClose();
        setResponse(lObj);
    }
    else {
        GResponseWebsocket lObj;
        lObj.setCommon(*this);
        lObj.setData("Bonjour tout le monde.");
        lObj.createResponse();
        setResponse(lObj);
    }
}
//===============================================
