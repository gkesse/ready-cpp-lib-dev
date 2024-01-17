//===============================================
#include "GException.h"
#include "GBackTrace.h"
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
void GException::throwError(const GString& _msg) {
    throw GException(_msg);
}
//===============================================
