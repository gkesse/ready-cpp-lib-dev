//===============================================
#ifndef _GBackTrace_
#define _GBackTrace_
//===============================================
#include "GInclude.h"
//===============================================
#define GBACKTRACE GBackTrace::Instance()
#define stacktrace GBACKTRACE->printBackStack
//===============================================
class GBackTrace {
public:
    GBackTrace();
    ~GBackTrace();
    static GBackTrace* Instance();
    size_t convertToVMA(size_t addr);
    void printBackStack();

private:
    static GBackTrace* m_instance;
};
//===============================================
#endif
//===============================================
