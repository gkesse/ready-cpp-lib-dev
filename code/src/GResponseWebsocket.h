//===============================================
#ifndef _GResponseWebsocket_
#define _GResponseWebsocket_
//===============================================
#include "GResponse.h"
//===============================================
class GResponseWebsocket : public GResponse {
public:
    GResponseWebsocket();
    ~GResponseWebsocket();
    void createResponse();
    void createClose();
    int getLength();

    void setIsFin(bool _isFin)          {m_isFin = _isFin;}
    void setRsv(char _rsv)              {m_rsv = _rsv;}
    void setOpcode(char _opcode)        {m_opcode = _opcode;}
    void setIsMask(bool _isMask)        {m_isMask = _isMask;}

private:
    bool m_isFin;
    char m_rsv;
    char m_opcode;
    bool m_isMask;
    char m_payloadLength;
};
//===============================================
#endif
//===============================================
