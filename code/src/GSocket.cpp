//===============================================
#include "GSocket.h"
#include "GRequest.h"
#include "GDispatcher.h"
#include "GResponse.h"
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

    slog(eGSTA, "Début du traitement de la requête du client.");

    GString lRequest = readData();
    GResponse lResp;

    if(!lRequest.isEmpty()) {
        slog(eGINF, "Requête reçu du client."
                    "|size=%d"
                    "|data=%s", lRequest.size(), lRequest.c_str());

        GRequest lReq;
        lReq.setSocket(*this);
        lReq.setData(lRequest);

        if(lReq.analyzeRequest()) {
            GDispatcher lDispatcher;
            lDispatcher.setCommon(lReq);
            lDispatcher.setRequest(lReq);
            lDispatcher.run();
            lResp.addResp(lDispatcher.getResp());
        }
    }

    sendData(lResp.toResponse());

    slog(eGEND, "Fin du traitement de la requête du client.");

    close(m_socket);
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
GString GSocket::readData() const {
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
const GString& GSocket::getAddressIP() const {
    return m_addressIP;
}
//===============================================
int GSocket::getPort() const {
    return m_port;
}
//===============================================
pid_t GSocket::getPid() const {
    return m_pid;
}
//===============================================
const GDebug& GSocket::getDebug() const {
    return slog;
}
//===============================================
void* GSocket::onThread(void* _params) {
    GSocket* lClient = (GSocket*)_params;
    lClient->runThread();
    delete lClient;
    return 0;
}
//===============================================
