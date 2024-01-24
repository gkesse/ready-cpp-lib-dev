//===============================================
#ifndef _GBackTrace_
#define _GBackTrace_
//===============================================
#include "GObject.h"
//===============================================
#define GBACKTRACE GBackTrace::Instance()
//===============================================
class GBackTrace {
public:
    struct GSignal {
        int m_signo;
        const char* m_name;
        const char* m_desc;
    };

public:
    GBackTrace();
    ~GBackTrace();
    static GBackTrace* Instance();
    void init();
    size_t convertToVMA(size_t addr);
    GSignal getSignal(int _signo);
    static void onSignal(int _signo);
    void print();

private:
    static GBackTrace* m_instance;
};
//===============================================
#endif
//===============================================
