//===============================================
#include "GDebug.h"
//===============================================
GDebug* GDebug::m_instance = 0;
//===============================================
#define LOG_FILENAME "logs.txt";
//===============================================
GDebug::GDebug()
: m_isTestEnv(false) {

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
bool GDebug::init() {
    m_isTestEnv = isTestEnv();
    m_enviro = (m_isTestEnv ? "test" : "prod");
    return true;
}
//===============================================
bool GDebug::isTestEnv() const {
    char* lEnv = getenv("GPROJECT_ENV");
    if(lEnv == 0) return false;
    GString lData = lEnv;
    return (lData == "TEST");
}
//===============================================
bool GDebug::writeFile(const GString& _data) {
    GString lFilename = getLogFile();
    lFilename.getFilepath().createPath(0777);
    std::ofstream lFile(lFilename.c_str(), std::ios::app);
    if(!lFile) return false;
    lFile << _data.c_str() << std::endl;
    return true;

}
//===============================================
bool GDebug::writeData(int _level, const char* _name, const char* _file, int _line, const char* _func, const char* _format, ...) {
    if(_level == 0) return false;
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lBuffer = new char[lSize + 1];
    vsnprintf(lBuffer, lSize + 1, _format, lArgs);
    va_end(lArgs);
    GString lData(lBuffer, lSize);
    delete[] lBuffer;
    GString lLog = sformat("%s|%s|%d|%s|%s|%s", getDate().c_str(), _file, _line, _func, _name, lData.c_str());
    if(m_isTestEnv) {
        lLog.print();
        writeFile(lLog);
    }
    else {
        writeFile(lLog);
    }
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
GString GDebug::getLogFile() const {
    const char* lFilename = LOG_FILENAME;
    char* lEnv = getenv("GPROJECT_DATA");
    if(lEnv == 0) return "";
    GString lDate = getDate("%Y/%m/%d");
    GString lPath = sformat("%s/logs/%s/%s/%s", lEnv, lDate.c_str(), m_enviro.c_str(), lFilename);
    return lPath;
}
//===============================================
