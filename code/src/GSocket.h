//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
//===============================================
typedef std::map<GString, GSocket*> GSocketClients;
//===============================================
class GSocket : public GObject {
public:
    GSocket();
    ~GSocket();
    void setResponse(const GSocket& _obj);
    void runServer();
    void runThread();
    virtual void createUnknown();
    bool sendData(const GString& _data);
    GString readData();
    void sendResponse();
    void writeResponse();
    void closeSocket();
    void continueSocket();
    bool addClient(const GString& _name);
    GSocket* getClient(const GString& _name) const;
    void printClients() const;
    static void* onThread(void* _params);
    static void* onThreadCB(void* _params);

    const GString& getAddressIP() const     {return m_addressIP;}
    int getPort() const                     {return m_port;}
    pid_t getPid() const                    {return m_pid;}

private:
    GSocket* m_server;
    int m_socket;
    GString m_addressIP;
    int m_port;
    pid_t m_pid;
    std::map<GString, GSocket*> m_clients;
    bool m_isServer;

protected:
    GString m_response;
};
//===============================================
#endif
//===============================================
