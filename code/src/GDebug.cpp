//===============================================
#include "GDebug.h"
#include "GSocket.h"
//===============================================
GDebug* GDebug::m_instance = 0;
//===============================================
GDebug::GDebug()
: m_addressIP("0.0.0.0")
, m_isTestEnv(false)
, m_port(0)
, m_pid(0) {

}
//===============================================
GDebug::GDebug(const GDebug& _obj) {
    *this = _obj;
}
//===============================================
GDebug::~GDebug() {

}
//===============================================
GDebug* GDebug::Instance() {
    if(m_instance == 0) {
        m_instance = new GDebug;
        m_instance->init();
    }
    return m_instance;
}
//===============================================
void GDebug::setSocket(const GSocket& _obj) {
    m_addressIP = _obj.getAddressIP();
    m_port = _obj.getPort();
    m_pid = _obj.getPid();
}
//===============================================
bool GDebug::init() {
    m_isTestEnv = isTestEnv();
    m_enviro = (m_isTestEnv ? "test" : "prod");
    m_logRoot = getLogRoot();
    return true;
}
//===============================================
bool GDebug::isTestEnv() const {
    char* lEnv = getenv("GENV_TYPE");
    if(lEnv == 0) return false;
    GString lData = lEnv;
    return (lData == "TEST");
}
//===============================================
bool GDebug::writeFile(const GString& _data) const {
    GString lFilename = getLogFile();
    lFilename.getFilepath().createPath(0777);
    std::ofstream lFile(lFilename.c_str(), std::ios::app);
    if(!lFile) return false;
    lFile << _data.c_str() << std::endl;
    return true;

}
//===============================================
GString GDebug::getDate(const GString& _format) const {
    time_t lTime;
    struct tm* lTimeInfo;
    char lBuffer[80];
    time(&lTime);
    lTimeInfo = localtime(&lTime);
    strftime(lBuffer, sizeof(lBuffer), _format.c_str(), lTimeInfo);
    return lBuffer;
}
//===============================================
GString GDebug::getLogRoot() const {
    char* lEnv = getenv("GLOG_ROOT");
    if(lEnv == 0) return "";
    return lEnv;
}
//===============================================
GString GDebug::getLogFile() const {
    GString lLogRoot = GDEBUG->m_logRoot;
    if(lLogRoot.isEmpty()) return "";
    GString lEnviro = GDEBUG->m_enviro;
    const char* lFilename = DEBUG_LOG_FILENAME;
    GString lDate = getDate("%Y/%m/%d");
    GString lPath = sformat("%s/logs/%s/%s/%s", lLogRoot.c_str(), lDate.c_str(), lEnviro.c_str(), lFilename);
    return lPath;
}
//===============================================
GDebug& GDebug::operator=(const GDebug& _obj) {
    m_addressIP = _obj.m_addressIP;
    m_port = _obj.m_port;
    m_pid = _obj.m_pid;
    return *this;
}
//===============================================
bool GDebug::operator()(int _level, const char* _name, const char* _file, int _line, const char* _func, const char* _format, ...) const {
    if(_level == 0) return false;
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lBuffer = new char[lSize + 1];
    vsnprintf(lBuffer, lSize + 1, _format, lArgs);
    va_end(lArgs);
    GString lData(lBuffer, lSize);
    delete[] lBuffer;
    GString lDate = getDate(DEBUG_LOG_DATE_FORMAT);
    GString lLog = sformat("%s|%s|%d|%s|%s|%s|%d|%d|%s", lDate.c_str(), _file, _line, _func, _name, m_addressIP.c_str(), m_port, m_pid, lData.c_str());
    bool isTestEnv = GDEBUG->m_isTestEnv;
    if(isTestEnv) {
        lLog.print();
        writeFile(lLog);
    }
    else {
        writeFile(lLog);
    }
    return true;
}
//===============================================
