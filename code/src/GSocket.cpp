//===============================================
#include "GSocket.h"
#include "GRequest.h"
//===============================================
#define SOCKET_HOSTNAME "0.0.0.0"
#define SOCKET_PORT     9050
#define SOCKET_BACKLOG  5
//===============================================
GSocket::GSocket()
: GObject()
, m_socket(-1)
, m_server(0)
, m_port(0)
, m_pid(-1) {

}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::runServer() {
    GString lHostname = SOCKET_HOSTNAME;
    int lPort = SOCKET_PORT;
    int lBacklog = SOCKET_BACKLOG;

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_socket == -1) {
        slog(eGERR, "Erreur lors de la création du socket."
                    "|hostname=%s"
                    "|port=%d"
                    "|backlog=%d"
                    "|errno=%d"
                    "|errmsg=%s", lHostname.c_str(), lPort, lBacklog, errno, strerror(errno));
        m_logs.addError("Un problème a été rencontré.");
        return;
    }

    struct sockaddr_in lAddressIn;
    bzero(&lAddressIn, sizeof(lAddressIn));
    lAddressIn.sin_family = AF_INET;
    lAddressIn.sin_addr.s_addr = inet_addr(lHostname.c_str());
    lAddressIn.sin_port = htons(lPort);

    int lOptVal = 1;
    int isSockopt = setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &lOptVal, sizeof(int));
    if(isSockopt == -1) {
        close(m_socket);
        slog(eGERR, "Erreur lors de l'initialisation de l'option SO_REUSEADDR sur le socket."
                    "|hostname=%s"
                    "|port=%d"
                    "|backlog=%d"
                    "|errno=%d"
                    "|errmsg=%s", lHostname.c_str(), lPort, lBacklog, errno, strerror(errno));
        m_logs.addError("Un problème a été rencontré.");
        return;
    }


    int isBind = bind(m_socket, (struct sockaddr*)&lAddressIn, sizeof(lAddressIn));
    if(isBind == -1) {
        close(m_socket);
        slog(eGERR, "Erreur lors de la liaison du socket à son adresse."
                    "|hostname=%s"
                    "|port=%d"
                    "|backlog=%d"
                    "|errno=%d"
                    "|errmsg=%s", lHostname.c_str(), lPort, lBacklog, errno, strerror(errno));
        m_logs.addError("Un problème a été rencontré.");
        return;
    }

    int isListen = listen(m_socket, lBacklog);
    if(isListen == -1) {
        close(m_socket);
        slog(eGERR, "Erreur lors de l'initialisation du nombre de connexions simultanées."
                    "|hostname=%s"
                    "|port=%d"
                    "|backlog=%d"
                    "|errno=%d"
                    "|errmsg=%s", lHostname.c_str(), lPort, lBacklog, errno, strerror(errno));
        m_logs.addError("Un problème a été rencontré.");
        return;
    }

    struct sockaddr_in lAddressOut;
    socklen_t lSize = sizeof(lAddressOut);

    slog(eGINF, "Démarrage du serveur..."
                "|hostname=%s"
                "|port=%d"
                "|backlog=%d", lHostname.c_str(), lPort, lBacklog);

    while(1) {
        GSocket* lClient = new GSocket;
        lClient->m_server = this;

        lClient->m_socket = accept(m_socket, (struct sockaddr*)&lAddressOut, &lSize);
        if(lClient->m_socket == -1) {
            slog(eGERR, "Erreur lors de l'acceptation d'une connexion client."
                        "|hostname=%s"
                        "|port=%d"
                        "|backlog=%d"
                        "|errno=%d"
                        "|errmsg=%s", lHostname.c_str(), lPort, lBacklog, errno, strerror(errno));
            continue;
        }

        lClient->m_addressIP = inet_ntoa(lAddressOut.sin_addr);
        lClient->m_port = (int)ntohs(lAddressOut.sin_port);

        slog(eGINF, "Connexion du client."
                    "|adresse_ip=%s"
                    "|port=%d", lClient->m_addressIP.c_str(), lClient->m_port);

        pthread_t lThread;
        int isThread = pthread_create(&lThread, 0, onThread, lClient);
        if(isThread == -1) {
            close(lClient->m_socket);
            slog(eGERR, "Erreur lors de la création du thread client."
                    "|hostname=%s"
                    "|port=%d"
                    "|backlog=%d"
                    "|errno=%d"
                    "|errmsg=%s", lHostname.c_str(), lPort, lBacklog, errno, strerror(errno));
            continue;
        }
    }

    close(m_socket);
}
//===============================================
void GSocket::runThread() {
    if(m_socket == -1) return;
    m_pid = gettid();
    slog(eGINF, "Début du traitement de la requête du client."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d", m_addressIP.c_str(), m_port, m_pid);

    GString lRequest = readData();

    if(!lRequest.isEmpty()) {
        slog(eGINF, "Requête reçu du client."
                    "|adresse_ip=%s"
                    "|port=%d"
                    "|process=%d"
                    "|data=%s", m_addressIP.c_str(), m_port, m_pid, lRequest.c_str());
    }

    slog(eGINF, "Fin du traitement de la requête du client."
                "|adresse_ip=%s"
                "|port=%d"
                "|process=%d", m_addressIP.c_str(), m_port, m_pid);
    close(m_socket);
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
            slog(eGERR, "Erreur lors de la lecture des données sur le socket."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|errno=%d"
                        "|errmsg=%s"
                        "|data=%s", m_addressIP.c_str(), m_port, m_pid, errno, strerror(errno), lData.c_str());
            return "";
        }
        lSize += lBytes;
        if(lSize >= SOCKET_BUFFER_MAX) {
            slog(eGERR, "Erreur le nombre maximal de données à lire sur le socket est atteint."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|errno=%d"
                        "|errmsg=%s"
                        "|data=%s", m_addressIP.c_str(), m_port, m_pid, errno, strerror(errno), lData.c_str());
            return "";
        }
        lData += GString(lBuffer, lBytes);
        if(!isData) {
            lReq.setData(lData);
            if(!lReq.analyze()) return "";
            isData = true;
        }
        int lRemaing = 0;
        int isRemaing = ioctl(m_socket, FIONREAD, &lRemaing);
        if(isRemaing == -1) {
            slog(eGERR, "Erreur lors de la lecture des données sur le socket."
                        "|adresse_ip=%s"
                        "|port=%d"
                        "|process=%d"
                        "|errno=%d"
                        "|errmsg=%s"
                        "|data=%s", m_addressIP.c_str(), m_port, m_pid, errno, strerror(errno), lData.c_str());
            return "";
        }
        if((lRemaing == 0) && (lSize >= lReq.getTotal())) break;
    }
    return lData;
}
//===============================================
void* GSocket::onThread(void* _params) {
    GSocket* lClient = (GSocket*)_params;
    lClient->runThread();
    delete lClient;
    return 0;
}
//===============================================
