//===============================================
#ifndef _GDebug_
#define _GDebug_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
#define eGOFF   0, "OFF", __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGSTA   1, "START", __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGEND   2, "END", __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGINF   3, "INFO", __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGWAR   4, "WARNING", __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGERR   5, "ERROR", __FILE__, __LINE__, __PRETTY_FUNCTION__
//===============================================
#define GDEBUG  GDebug::Instance()
#define slog    GDEBUG->writeData
//===============================================
class GDebug {
public:
    GDebug();
    ~GDebug();
    static GDebug* Instance();
    bool init();
    bool isTestEnv() const;
    bool writeFile(const GString& _data);
    bool writeData(int _level, const char* _name, const char* _file, int _line, const char* _func, const char* _format, ...);
    GString getDate(const GString& _format = "%d/%m/%Y %H:%M:%S") const;
    GString getLogFile() const;

private:
    static GDebug* m_instance;
    bool m_isTestEnv;
    GString m_enviro;
};
//===============================================
#endif
//===============================================
