//===============================================
#ifndef _GDebug_
#define _GDebug_
//===============================================
#include "GString.h"
#include "GLog.h"
//===============================================
#define eGOFF   DEBUG_TYPE_OFF, "OFF", __FILE__, __LINE__, __FUNCTION__
#define eGSRV   DEBUG_TYPE_SRV, "SERVER", __FILE__, __LINE__, __FUNCTION__
#define eGEXT   DEBUG_TYPE_EXT, "EXIT", __FILE__, __LINE__, __FUNCTION__
#define eGSTA   DEBUG_TYPE_STA, "START", __FILE__, __LINE__, __FUNCTION__
#define eGEND   DEBUG_TYPE_END, "END", __FILE__, __LINE__, __FUNCTION__
#define eGINF   DEBUG_TYPE_INF, "INFO", __FILE__, __LINE__, __FUNCTION__
#define eGWAR   DEBUG_TYPE_WAR, "WARNING", __FILE__, __LINE__, __FUNCTION__
#define eGERR   DEBUG_TYPE_ERR, "ERROR", __FILE__, __LINE__, __FUNCTION__
#define eGMAN   DEBUG_TYPE_MAN, "MAIN", __FILE__, __LINE__, __FUNCTION__
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
    GLog m_logs;
};
//===============================================
#endif
//===============================================
