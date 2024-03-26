//===============================================
#include "GSocket.h"
#include "GRequest.h"
#include "GDispatcher.h"
//===============================================
GSocket::GSocket()
: GObject()
, m_socket(-1)
, m_addressIP("0.0.0.0")
, m_port(0)
, m_pid(0) {

}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::setResponse(const GSocket& _obj) {
    m_response      = _obj.m_response;
    m_type          = _obj.m_type;
    m_isContinue    = _obj.m_isContinue;
    m_isClose       = _obj.m_isClose;
}
//===============================================
void GSocket::runServer() {
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_socket == -1) {
        slog(eGERR, "La création du socket a échoué."
                    "|hostname=%s"
                    "|port=%d"
                    "|backlog=%d"
                    "|errno=%d"
                    "|errmsg=%s", SOCKET_HOSTNAME, SOCKET_PORT, SOCKET_BACKLOG, errno, strerror(errno));
        return;
    }

    struct sockaddr_in lAddressIn;
    bzero(&lAddressIn, sizeof(lAddressIn));
    lAddressIn.sin_family = AF_INET;
    lAddressIn.sin_addr.s_addr = inet_addr(SOCKET_HOSTNAME);
    lAddressIn.sin_port = htons(SOCKET_PORT);

    int lReuseAddr = 1;
    int isReuseAddr = setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &lReuseAddr, sizeof(int));
    if(isReuseAddr == -1) {
        close(m_socket);
        slog(eGERR, "L'initialisation de l'option SO_REUSEADDR sur le socket a échoué."
                    "|hostname=%s"
                    "|port=%d"
                    "|backlog=%d"
                    "|errno=%d"
                    "|errmsg=%s", SOCKET_HOSTNAME, SOCKET_PORT, SOCKET_BACKLOG, errno, strerror(errno));
        return;
    }

    int isBind = bind(m_socket, (struct sockaddr*)&lAddressIn, sizeof(lAddressIn));
    if(isBind == -1) {
        close(m_socket);
        slog(eGERR, "La liaison du socket à son adresse a échoué."
                    "|hostname=%s"
                    "|port=%d"
                    "|backlog=%d"
                    "|errno=%d"
                    "|errmsg=%s", SOCKET_HOSTNAME, SOCKET_PORT, SOCKET_BACKLOG, errno, strerror(errno));
        return;
    }

    int isListen = listen(m_socket, SOCKET_BACKLOG);
    if(isListen == -1) {
        close(m_socket);
        slog(eGERR, "L'initialisation du nombre de connexions simultanées a échoué."
                    "|hostname=%s"
                    "|port=%d"
                    "|backlog=%d"
                    "|errno=%d"
                    "|errmsg=%s", SOCKET_HOSTNAME, SOCKET_PORT, SOCKET_BACKLOG, errno, strerror(errno));
        return;
    }

    struct sockaddr_in lAddressOut;
    socklen_t lSize = sizeof(lAddressOut);

    slog(eGSRV, "Démarrage du serveur."
                "|hostname=%s"
                "|port=%d"
                "|backlog=%d", SOCKET_HOSTNAME, SOCKET_PORT, SOCKET_BACKLOG);

    while(1) {
        GSocket* lClient = new GSocket;

        lClient->m_socket = accept(m_socket, (struct sockaddr*)&lAddressOut, &lSize);
        if(lClient->m_socket == -1) {
            slog(eGERR, "L'acceptation de la connexion du client a échoué."
                        "|hostname=%s"
                        "|port=%d"
                        "|backlog=%d"
                        "|errno=%d"
                        "|errmsg=%s", SOCKET_HOSTNAME, SOCKET_PORT, SOCKET_BACKLOG, errno, strerror(errno));
            continue;
        }

        lClient->m_addressIP = inet_ntoa(lAddressOut.sin_addr);
        lClient->m_port = (int)ntohs(lAddressOut.sin_port);

        slog.setSocket(*lClient);

        slog(eGINF, "Connexion du client.");

        pthread_t lThread;
        int isThread = pthread_create(&lThread, 0, onThread, lClient);
        if(isThread == -1) {
            close(lClient->m_socket);
            slog(eGERR, "La création du thread du client a échoué."
                        "|errno=%d"
                        "|errmsg=%s", errno, strerror(errno));
            continue;
        }
    }

    close(m_socket);
}
//===============================================
void GSocket::runThread() {
    if(m_socket == -1) return;
    m_pid = gettid();
    slog.setSocket(*this);

    slog(eGSTA, "Début du traitement de la requête du client."
                "|isContinue=%d"
                "|type=%d", m_isContinue, m_type);

    GString lRequest = readData();

    if(!lRequest.isEmpty()) {
        if(m_type == eGRequestType::REQ_TYPE_HTTP_WEBSOCKET) {
            slog(eGINF, "Réception de la requête du client."
                        "|type=%d"
                        "|size=%d", m_type, lRequest.size());
        }
        else {
            slog(eGINF, "Réception de la requête du client."
                        "|type=%d"
                        "|size=%d"
                        "|data=%s", m_type, lRequest.size(), lRequest.c_str());
        }

        GRequest lReq;
        lReq.setCommon(*this);
        lReq.setData(lRequest);

        if(lReq.analyzeRequest()) {
            GDispatcher lDispatcher;
            lDispatcher.setCommon(lReq);
            lDispatcher.setRequest(lReq);
            lDispatcher.run();
            m_logs.addLogs(lDispatcher.getLogs());
            setResponse(lDispatcher);
        }
        else {
            createUnknown();
        }
    }
    else {
        createUnknown();
    }
    sendResponse();
}
//===============================================
void GSocket::createUnknown() {
    m_response += sformat("Un problème a été rencontré.");
}
//===============================================
bool GSocket::sendData(const GString& _data) {
    slog(eGEND, "Réponse envoyée au client."
                "|size=%d"
                "|data=%s", _data.size(), _data.c_str());

    int lIndex = 0;
    const char* lBuffer = _data.c_str();
    int lSize = _data.size();
    while(1) {
        int lBytes = send(m_socket, &lBuffer[lIndex], lSize - lIndex, 0);
        if(lBytes == -1) {
            slog(eGERR, "L'envoi des données sur le socket a échoué."
                        "|errno=%d"
                        "|errmsg=%s"
                        "|size=%d"
                        "|data=%s", errno, strerror(errno), _data.size(), _data.c_str());
            return false;
        }
        lIndex += lBytes;
        if(lIndex >= lSize) break;
    }
    return true;
}
//===============================================
GString GSocket::readData() {
    char lBuffer[SOCKET_BUFFER_SIZE + 1];
    GString lData;
    GRequest lReq;
    int lSize = 0;
    bool isData = false;
    while(1) {
        int lBytes = recv(m_socket, lBuffer, SOCKET_BUFFER_SIZE, 0);
        if(lBytes == -1) {
            slog(eGERR, "La lecture des données sur le socket a échoué."
                        "|errno=%d"
                        "|errmsg=%s"
                        "|size=%d"
                        "|data=%s", errno, strerror(errno), lData.size(), lData.c_str());
            return "";
        }
        lSize += lBytes;
        if(lSize >= SOCKET_BUFFER_MAX) {
            slog(eGERR, "Le nombre maximal de données à lire sur le socket est atteint."
                        "|errno=%d"
                        "|errmsg=%s"
                        "|size=%d"
                        "|data=%s", errno, strerror(errno), lData.size(), lData.c_str());
            return "";
        }
        lData += GString(lBuffer, lBytes);
        if(!isData) {
            lReq.setData(lData);
            lReq.setCommon(*this);
            if(!lReq.analyzeHeader()) return "";
            setResponse(lReq);
            isData = true;
        }
        int lRemaing = 0;
        int isRemaing = ioctl(m_socket, FIONREAD, &lRemaing);
        if(isRemaing == -1) {
            slog(eGERR, "La lecture des données sur le socket a échoué."
                        "|errno=%d"
                        "|errmsg=%s"
                        "|size=%d"
                        "|data=%s", errno, strerror(errno), lData.size(), lData.c_str());
            return "";
        }
        if((lRemaing == 0) && (lSize >= lReq.getTotal())) break;
    }
    return lData;
}
//===============================================
void GSocket::sendResponse() {
    sendData(m_response);
    if(!m_isContinue) {
        closeSocket();
    }
    else {
        continueSocket();
    }
}
//===============================================
void GSocket::closeSocket() {
    slog(eGINF, "Fermeture du point de connexion socket.");
    close(m_socket);
    delete this;
    slog(eGEND, "Fin du traitement de la requête du client.");
}
//===============================================
void GSocket::continueSocket() {
    pthread_t lThread;
    int isThread = pthread_create(&lThread, 0, onThread, this);
    if(isThread == -1) {
        closeSocket();
        slog(eGERR, "La création du thread de la connexion en continue a échoué."
                    "|errno=%d"
                    "|errmsg=%s", errno, strerror(errno));
    }
}
//===============================================
void* GSocket::onThread(void* _params) {
    GSocket* lClient = (GSocket*)_params;
    lClient->runThread();
    return 0;
}
//===============================================
