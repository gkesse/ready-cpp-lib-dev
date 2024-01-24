//===============================================
#ifndef _GDebug_
#define _GDebug_
//===============================================
#include "GInclude.h"
//===============================================
#define eGOFF   0, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGDBG   1, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGLOG   2, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGWAR   3, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGERR   4, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGCRI   5, __FILE__, __LINE__, __PRETTY_FUNCTION__
#define eGFAT   6, __FILE__, __LINE__, __PRETTY_FUNCTION__
//===============================================
class GDebug {
public:
    GDebug();
    ~GDebug();

private:
};
//===============================================
#endif
//===============================================
