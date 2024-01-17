//===============================================
#ifndef _GBackTrace_
#define _GBackTrace_
//===============================================
#include "GInclude.h"
//===============================================
#define GBACKTRACE GBackTrace::Instance()
//===============================================
class GBackTrace {
public:
    GBackTrace();
    ~GBackTrace();
    static GBackTrace* Instance();
    void init();
    size_t convertToVMA(size_t addr);
    static void onSignal(int _signo);
    void print();

private:
    static GBackTrace* m_instance;
};
//===============================================
#endif
//===============================================
