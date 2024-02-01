//===============================================
#include "GException.h"
#include "GDebug.h"
//===============================================
GException* GException::m_instance = 0;
//===============================================
GException::GException() {

}
//===============================================
GException::GException(const GString& _msg) {
    m_msg = _msg;
}
//===============================================
GException::~GException() {

}
//===============================================
GException* GException::Instance() {
    if(m_instance) {
        m_instance = new GException;
    }
    return m_instance;
}
//===============================================
const char* GException::what() const throw() {
    return m_msg.c_str();
}
//===============================================
void GException::throwError(const char* _format, ...) {
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lBuffer = new char[lSize + 1];
    vsnprintf(lBuffer, lSize + 1, _format, lArgs);
    va_end(lArgs);
    GString lMsg(lBuffer, lSize);
    delete[] lBuffer;
    slog(eGERR, lMsg.c_str());
    throw GException(lMsg);
}
//===============================================
