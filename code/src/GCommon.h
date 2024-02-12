//===============================================
#ifndef _GCommon_
#define _GCommon_
//===============================================
#include "GDebug.h"
//===============================================
class GSocket;
//===============================================
class GCommon {
public:
    GCommon();
    virtual ~GCommon();
    virtual void setCommon(const GCommon& _obj);
    virtual void setDebug(const GDebug& _obj);
    virtual void setSocket(const GSocket& _obj);

protected:
    GDebug slog;
};
//===============================================
#endif
//===============================================
