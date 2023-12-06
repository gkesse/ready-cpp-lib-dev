//===============================================
#ifndef _GBackTrace_
#define _GBackTrace_
//===============================================
#include "GInclude.h"
//===============================================
class GBackTrace {
public:
    GBackTrace();
    ~GBackTrace();
    static void log_stack();
    static int32_t getaddr(char *in,char *out,size_t size);
    static int32_t addr2line(char *addr,char *output,int32_t size);
};
//===============================================
#endif
//===============================================
