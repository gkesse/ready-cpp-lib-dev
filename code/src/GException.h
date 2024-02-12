//===============================================
#ifndef _GException_
#define _GException_
//===============================================
#include "GString.h"
//===============================================
#define GEXCEPTION  GException::Instance()
#define eThrow      GEXCEPTION->throwError
//===============================================
class GException : public std::exception {
public:
    GException();
    GException(const GString& _msg);
    ~GException();
    static GException* Instance();
    const char* what() const throw();
    static void throwError(const char* _msg, ...);

private:
    static GException* m_instance;
    GString m_msg;
};
//===============================================
#endif
//===============================================
