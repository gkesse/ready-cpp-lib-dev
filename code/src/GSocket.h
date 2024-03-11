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
    GString readData() const;
    const GString& getAddressIP() const;
    int getPort() const;
    pid_t getPid() const;
    const GDebug& getDebug() const;
    void sendResponse();
    static void* onThread(void* _params);

private:
    int m_socket;
    GString m_addressIP;
    int m_port;
    pid_t m_pid;

protected:
    GString m_response;
    bool m_isClose;
};
//===============================================
#endif
//===============================================
