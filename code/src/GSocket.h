//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
class GSocket {
public:
    GSocket();
    ~GSocket();
    void runServer();
    void runThread();
    GString readData() const;
    static void* onThread(void* _params);

private:
    static const int SOCKET_BUFFER_SIZE = 1024; // 1Ko
    static const int SOCKET_BUFFER_MAX = 1*1024*1024; // 1Mo

private:
    GSocket* m_server;
    std::vector<GSocket*> m_map;
    int m_socket;
    GString m_addressIP;
    int m_port;
};
//===============================================
#endif
//===============================================
