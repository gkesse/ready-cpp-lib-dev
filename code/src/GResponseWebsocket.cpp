//===============================================
#include "GResponseWebsocket.h"
//===============================================
GResponseWebsocket::GResponseWebsocket()
: GResponse()
, m_isFin(true)
, m_rsv(0)
, m_opcode(WEBSOCKET_OPCODE_TEXT)
, m_isMask(false)
, m_payloadLength(0) {

}
//===============================================
GResponseWebsocket::~GResponseWebsocket() {

}
//===============================================
void GResponseWebsocket::create() {
    int lSize = m_data.size();
    int lLength = getLength();
    char* lData = new char[lLength];
    char lMasks[4];
    ulong lByte;
    ulong lChar;
    int lPos = 0;

    // 1B : FIN-RSV1-RSV2-RSV3-OPCODE1-OPCODE2-OPCODE3-OPCODE4
    lByte = 0;
    lChar = m_isFin;
    lByte |= (lChar << 7);
    lChar = m_rsv;
    lByte |= (lChar << 4);
    lChar = m_opcode;
    lByte |= (lChar << 0);
    lData[lPos++] = lByte;

    // 1B : MASK-LENGTH1-LENGTH2-LENGTH3-LENGTH4-LENGTH5-LENGTH6-LENGTH7
    lByte = 0;
    lChar = m_isMask;
    lByte |= (lChar << 7);
    lChar = m_payloadLength;
    lByte |= (lChar << 0);
    lData[lPos++] = lByte;

    // 0B :
    if(m_payloadLength >= 0 && m_payloadLength <= 125) {

    }
    // 2B : LENGTH1-LENGTH2
    else if(m_payloadLength == 126) {
        lChar = lSize;
        lByte = ((lChar & 0xFF00) >> 8);
        lData[lPos++] = lByte;
        lByte = ((lChar & 0x00FF) >> 0);
        lData[lPos++] = lByte;
    }
    // 8B : LENGTH1-LENGTH2-LENGTH3-LENGTH4-LENGTH5-LENGTH6-LENGTH7-LENGTH8
    else if(m_payloadLength == 127) {
        lChar = lSize;
        lByte = ((lChar & 0xFF00000000000000LL) >> 56);
        lData[lPos++] = lByte;
        lByte = ((lChar & 0x00FF000000000000LL) >> 48);
        lData[lPos++] = lByte;
        lByte = ((lChar & 0x0000FF0000000000LL) >> 40);
        lData[lPos++] = lByte;
        lByte = ((lChar & 0x000000FF00000000LL) >> 32);
        lData[lPos++] = lByte;
        lByte = ((lChar & 0x00000000FF000000LL) >> 24);
        lData[lPos++] = lByte;
        lByte = ((lChar & 0x0000000000FF0000LL) >> 16);
        lData[lPos++] = lByte;
        lByte = ((lChar & 0x000000000000FF00LL) >> 8);
        lData[lPos++] = lByte;
        lByte = ((lChar & 0x00000000000000FFLL) >> 0);
        lData[lPos++] = lByte;
    }
    else {
        slog(eGERR, "La taille maximale des données est atteinte."
                "|payloadLength=%d"
                "|size=%d", m_payloadLength, lSize);
        m_logs.addProblem();
    }

    // 4B : MASK1-MASK2-MASK3-MASK4
    if(m_isMask) {
        srand(time(NULL));
        lChar = rand();
        memcpy(lMasks, &lChar, 4);
        memcpy(&lData[lPos], lMasks, 4);
        lPos += 4;
    }

    // nB : DATA[1]-...-DATA[n]
    int iPos = lPos;
    memcpy(&lData[lPos], m_data.c_str(), lSize);
    lPos += lSize;

    if(m_isMask) {
        for(int i = 0; i < lSize; i++) {
            lData[iPos] = lMasks[i % 4] ^ lData[iPos];
            iPos++;
        }
    }

    m_response = GString(lData, lPos);
}
//===============================================
int GResponseWebsocket::getLength() {
    ulong lSize = m_data.size();
    ulong lLength = 0;

    // 1B : FIN-RSV1-RSV2-RSV3-OPCODE1-OPCODE2-OPCODE3-OPCODE4
    lLength += 1;
    // 1B : MASK-LENGTH1-LENGTH2-LENGTH3-LENGTH4-LENGTH5-LENGTH6-LENGTH7
    lLength += 1;

    // 0B :
    if(lSize >= 0 && lSize <= 125) {
        lLength += 0;
        m_payloadLength = lSize;
    }
    // 2B : LENGTH1-LENGTH2
    else if(lSize > 125 && lSize <= 0xFFFF) {
        lLength += 2;
        m_payloadLength = 126;
    }
    // 8B : LENGTH1-LENGTH2-LENGTH3-LENGTH4-LENGTH5-LENGTH6-LENGTH7-LENGTH8
    else if(lSize > 0xFFFF && lSize <= 0xFFFFFFFFFFFFFFFFLL) {
        lLength += 8;
        m_payloadLength = 127;
    }
    else {
        slog(eGERR, "La taille maximale des données est atteinte."
                "|payloadLength=%d"
                "|size=%d", m_payloadLength, lSize);
        m_logs.addProblem();
    }

    // 4B : MASK1-MASK2-MASK3-MASK4
    if(m_isMask) {
        lLength += 4;
    }

    // nB : DATA[1]-...-DATA[n]
    lLength += lSize;
    return lLength;
}
//===============================================
