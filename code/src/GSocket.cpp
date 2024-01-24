//===============================================
#include "GSocket.h"
#include "GRequest.h"
//===============================================
GSocket::GSocket() {
    m_socket = -1;
    m_server = 0;
    m_port = 0;
}
//===============================================
GSocket::~GSocket() {

}
//===============================================
void GSocket::runServer() {
    GString lHostname = "0.0.0.0";
    int lPort = 9050;
    int lBacklog = 5;

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_socket == -1) {
        eThrow("Impossible de créer le socket."
                "|errno=%d"
                "|errmsg=%s", errno, strerror(errno));
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
        eThrow("Impossible d'initialiser l'option SO_REUSEADDR sur le socket."
                "|socket=%d"
                "|errno=%d"
                "|errmsg=%s", m_socket, errno, strerror(errno));
    }


    int isBind = bind(m_socket, (struct sockaddr*)&lAddressIn, sizeof(lAddressIn));
    if(isBind == -1) {
        close(m_socket);
        eThrow("Impossible de lier le socket à son adresse."
                "|socket=%d"
                "|errno=%d"
                "|errmsg=%s", m_socket, errno, strerror(errno));
    }

    int isListen = listen(m_socket, lBacklog);
    if(isListen == -1) {
        close(m_socket);
        eThrow("Impossible d'initialiser le nombre de connexions simultanées."
                "|socket=%d"
                "|errno=%d"
                "|errmsg=%s", m_socket, errno, strerror(errno));
    }

    struct sockaddr_in lAddressOut;
    socklen_t lSize = sizeof(lAddressOut);

    sformat("Démarrage du serveur..."
            "|socket=%d", m_socket).print();

    while(1) {
        GSocket* lClient = new GSocket;
        lClient->m_server = this;

        lClient->m_socket = accept(m_socket, (struct sockaddr*)&lAddressOut, &lSize);
        if(lClient->m_socket == -1) {
            sformat("Impossible d'accepter la connexion client."
                    "|errno=%d"
                    "|errmsg=%s", errno, strerror(errno)).print();
            continue;
        }

        lClient->m_addressIP = inet_ntoa(lAddressOut.sin_addr);
        lClient->m_port = (int)ntohs(lAddressOut.sin_port);

        pthread_t lThread;
        int isThread = pthread_create(&lThread, 0, onThread, lClient);
        if(isThread == -1) {
            close(lClient->m_socket);
            sformat("Impossible de créer le thread client."
                    "|socket=%d"
                    "|errno=%d"
                    "|errmsg=%s", lClient->m_socket, errno, strerror(errno)).print();
            continue;
        }
    }

    close(m_socket);
}
//===============================================
void GSocket::runThread() {
    if(m_socket == -1) return;
    sformat("Début de la connexion du client."
            "|socket=%d"
            "|ip=%s"
            "|port=%d", m_socket, m_addressIP.c_str(), m_port).print();

    GString lRequest = readData();

    if(!lRequest.isEmpty()) {
        lRequest.print();
    }

    sformat("Fin de la connexion du client."
            "|socket=%d"
            "|ip=%s"
            "|port=%d", m_socket, m_addressIP.c_str(), m_port).print();
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
        if(lBytes <= 0) {
            sformat("Impossible de continuer, une erreur est survenue lors de la lecture des données sur le socket."
                    "|socket=%d"
                    "|errno=%d"
                    "|errmsg=%s"
                    "|data=%s", m_socket, errno, strerror(errno), lData.c_str()).print();
            return "";
        }
        lSize += lBytes;
        if(lSize >= SOCKET_BUFFER_MAX) {
            sformat("Impossible de continuer, le nombre maximal de données à lire sur le socket a été atteint."
                    "|socket=%d"
                    "|errno=%d"
                    "|errmsg=%s"
                    "|data=%s", m_socket, errno, strerror(errno), lData.c_str()).print();
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
        if(isRemaing == -1) break;
        if((lRemaing <= 0) && (lSize >= lReq.getTotal())) break;
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
