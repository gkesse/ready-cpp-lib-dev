//===============================================
#ifndef _GBackTrace_
#define _GBackTrace_
//===============================================
#include "GObject.h"
//===============================================
struct sGBackTraceSignal {
    int m_signo;
    const char* m_name;
    const char* m_desc;
};
//===============================================
class GBackTrace : public GObject {
public:
    GBackTrace();
    ~GBackTrace();
    void init();
    size_t convertToVMA(size_t addr);
    sGBackTraceSignal getSignal(int _signo);
    void print();
    void runSignal(int _signo);
    static void onSignal(int _signo);
};
//===============================================
#endif
//===============================================
