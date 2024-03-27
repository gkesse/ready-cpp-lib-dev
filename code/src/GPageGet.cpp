//===============================================
#include "GPageGet.h"
#include "GResourceUi.h"
#include "GCarpoolUi.h"
#include "GChatUi.h"
#include "GResponseWebsocket.h"
//===============================================
GPageGet::GPageGet()
: GPage() {

}
//===============================================
GPageGet::~GPageGet() {

}
//===============================================
void GPageGet::run() {
    slog(eGINF, "Traitement de la requête HTTP GET."
                "|uri=%s", m_uri.c_str());

    m_client->printClients();
    GSocket* lClient = m_client->getClient("mon_client");
    if(lClient) {
        GResponseWebsocket lObj;
        lObj.setCommon(*lClient);
        lObj.setData("Bonjour tout le monde.");
        lObj.createResponse();
        lClient->setResponse(lObj);
        lClient->writeResponse();
    }

    if(!loadResource()) {
        if(m_uri.startsWith("/carpool")) {
            runCarpool();
        }
        else if(m_uri.startsWith("/chat")) {
            runChat();
        }
        else {
            slog(eGERR, "L'uri n'est pas gérée."
                        "|uri=%s", m_uri.c_str());
            m_logs.addProblem();
            createUnknown();
        }
    }
    else {
        slog(eGINF, "La ressource a bien été chargée."
                    "|uri=%s", m_uri.c_str());
    }

    createResponse();
}
//===============================================
bool GPageGet::loadResource() {
    GResourceUi lObj;
    lObj.setCommon(*this);
    lObj.setPage(*this);
    if(lObj.loadResource()) {
        setResponseHttp(lObj);
        return true;
    }
    return false;
}
//===============================================
void GPageGet::runCarpool() {
    GCarpoolUi lObj;
    lObj.setCommon(*this);
    lObj.setPage(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponseHttp(lObj);
}
//===============================================
void GPageGet::runChat() {
    GChatUi lObj;
    lObj.setCommon(*this);
    lObj.setPage(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponseHttp(lObj);
}
//===============================================
