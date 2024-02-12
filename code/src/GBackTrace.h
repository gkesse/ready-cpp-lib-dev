//===============================================
#ifndef _GBackTrace_
#define _GBackTrace_
//===============================================
#include "GObject.h"
//===============================================
class GBackTrace : public GObject {
public:
    struct GSignal {
        int m_signo;
        const char* m_name;
        const char* m_desc;
    };

public:
    GBackTrace();
    ~GBackTrace();
    void init();
    size_t convertToVMA(size_t addr);
    GSignal getSignal(int _signo);
    void print();
    void runSignal(int _signo);
    static void onSignal(int _signo);
};
//===============================================
#endif
//===============================================
