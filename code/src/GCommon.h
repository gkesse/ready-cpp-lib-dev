//===============================================
#ifndef _GCommon_
#define _GCommon_
//===============================================
#include "GDebug.h"
//===============================================
class GSocket;
//===============================================
enum class eGRequestType {
    REQ_TYPE_UNKNOWN
    , REQ_TYPE_HTTP_GET
    , REQ_TYPE_HTTP_POST
    , REQ_TYPE_HTTP_WEBSOCKET
};
//===============================================
class GCommon {
public:
    GCommon();
    virtual ~GCommon();
    virtual void setCommon(const GCommon& _obj);

    const eGRequestType& getType() const    {return m_type;}
    bool isClose() const                    {return m_isClose;}

protected:
    GDebug slog;
    eGRequestType m_type;
    bool m_isContinue;
    bool m_isClose;
};
//===============================================
#endif
//===============================================
