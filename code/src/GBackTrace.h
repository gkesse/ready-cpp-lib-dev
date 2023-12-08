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
    static void printLogStack();
    static int32_t getaddr(char *in,char *out,size_t size);
    static int32_t addr2line(char *addr,char *output,int32_t size);
    static size_t convertToVMA(size_t addr);
    static void printCallStack();
    static void printStackTrace();
    static int addr2line(char const * const program_name, void const * const addr);
    static void printBackStack();
};
//===============================================
#endif
//===============================================
