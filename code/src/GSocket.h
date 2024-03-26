//===============================================
#ifndef _GSocket_
#define _GSocket_
//===============================================
#include "GObject.h"
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
    void closeSocket();
    void continueSocket();
    static void* onThread(void* _params);

    const GString& getAddressIP() const     {return m_addressIP;}
    int getPort() const                     {return m_port;}
    pid_t getPid() const                    {return m_pid;}

private:
    int m_socket;
    GString m_addressIP;
    int m_port;
    pid_t m_pid;

protected:
    GString m_response;
};
//===============================================
#endif
//===============================================
