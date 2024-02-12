//===============================================
#ifndef _GDebug_
#define _GDebug_
//===============================================
#include "GString.h"
//===============================================
#define eGOFF   0, "OFF", __FILE__, __LINE__, __FUNCTION__
#define eGSRV   1, "SERVER", __FILE__, __LINE__, __FUNCTION__
#define eGEXT   2, "EXIT", __FILE__, __LINE__, __FUNCTION__
#define eGSTA   3, "START", __FILE__, __LINE__, __FUNCTION__
#define eGEND   4, "END", __FILE__, __LINE__, __FUNCTION__
#define eGINF   5, "INFO", __FILE__, __LINE__, __FUNCTION__
#define eGWAR   6, "WARNING", __FILE__, __LINE__, __FUNCTION__
#define eGERR   7, "ERROR", __FILE__, __LINE__, __FUNCTION__
#define eGMAN   7, "MAIN", __FILE__, __LINE__, __FUNCTION__
//===============================================
#define GDEBUG  GDebug::Instance()
//===============================================
class GSocket;
//===============================================
class GDebug {
public:
    GDebug();
    GDebug(const GDebug& _obj);
    ~GDebug();
    static GDebug* Instance();
    void setSocket(const GSocket& _obj);
    bool init();
    bool isTestEnv() const;
    bool writeFile(const GString& _data) const;
    GString getDate(const GString& _format) const;
    GString getLogRoot() const;
    GString getLogFile() const;
    bool operator()(int _level, const char* _name, const char* _file, int _line, const char* _func, const char* _format, ...) const;
    GDebug& operator=(const GDebug& _obj);

private:
    static GDebug* m_instance;
    bool m_isTestEnv;
    GString m_enviro;
    GString m_logRoot;
    GString m_addressIP;
    int m_port;
    pid_t m_pid;
};
//===============================================
#endif
//===============================================
