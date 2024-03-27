//===============================================
#include "GRequestWebsocket.h"
//===============================================
GRequestWebsocket::GRequestWebsocket()
: GObject()
, m_total(0)
, m_pos(0) {

}
//===============================================
GRequestWebsocket::~GRequestWebsocket() {

}
//===============================================
void GRequestWebsocket::setRequest(const GRequestWebsocket& _obj) {
    m_request       = _obj.m_request;
}
//===============================================
bool GRequestWebsocket::analyzeHeader() {
    if(m_data.isEmpty()) return false;
    ulong lByte;

    // 1B : FIN-RSV1-RSV2-RSV3-OPCODE1-OPCODE2-OPCODE3-OPCODE4
    lByte = m_data[m_pos++];
    bool isFin = ((lByte & 0x80) >> 7);
    char lRsv = ((lByte & 0x70) >> 4);
    char lOpcode = ((lByte & 0x0F) >> 0);

    if((lOpcode != WEBSOCKET_OPCODE_CONTINUE) &&
       (lOpcode != WEBSOCKET_OPCODE_TEXT) &&
       (lOpcode != WEBSOCKET_OPCODE_BINARY) &&
       (lOpcode != WEBSOCKET_OPCODE_CLOSE) &&
       (lOpcode != WEBSOCKET_OPCODE_PING) &&
       (lOpcode != WEBSOCKET_OPCODE_PONG)) {
        slog(eGERR, "Le code opération  n'est pas supporté."
                    "|isFin=%d"
                    "|rsv=%d"
                    "|opcode=%d", isFin, lRsv, lOpcode);
        m_logs.addProblem();
        return false;
    }

    if(lRsv) {
        slog(eGERR, "Les extensions du protocole WEBSOCKET ne sont pas supportées."
                    "|isFin=%d"
                    "|rsv=%d"
                    "|opcode=%d", isFin, lRsv, lOpcode);
        m_logs.addProblem();
        return false;
    }

    // 1B : MASK-PL1-PL2-PL3-PL4-PL5-PL6-PL7
    lByte = m_data[m_pos++];
    bool isMask = ((lByte & 0x80) >> 7);
    char lPayloadLength = ((lByte & 0x7F) >> 0);
    int lContentLength = 0;

    // 0B
    if(lPayloadLength >= 0 && lPayloadLength <= 125) {
        lContentLength = lPayloadLength;
    }
    // 2B : LENGHT1-LENGTH2
    else if(lPayloadLength == 126) {
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 8);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 0);
    }
    // 8B : LENGHT1-LENGTH2-LENGTH3-LENGTH4-LENGTH5-LENGTH6-LENGTH7-LENGTH8
    else if(lPayloadLength == 127) {
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 56);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 48);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 40);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 32);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 24);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 16);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 8);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 0);
    }

    // 4B : MASK1-MASK2-MASK3-MASK4;
    char masks[4] = {0}, iMask = 0;
    if(isMask) {
        lByte = m_data[m_pos++];
        masks[iMask++] = lByte;
        lByte = m_data[m_pos++];
        masks[iMask++] = lByte;
        lByte = m_data[m_pos++];
        masks[iMask++] = lByte;
        lByte = m_data[m_pos++];
        masks[iMask++] = lByte;
    }

    iMask = 0;
    slog(eGINF, "Analyse de la requête WEBSOCKET."
                "|isFin=%d"
                "|rsv=%d"
                "|opcode=%d"
                "|isMask=%d"
                "|payloadLength=%d"
                "|contentLength=%d"
                "|pos=%d"
                "|mask_1=0x%02X"
                "|mask_2=0x%02X"
                "|mask_3=0x%02X"
                "|mask_4=0x%02X", isFin, lRsv, lOpcode, isMask, lPayloadLength, lContentLength, m_pos
                , masks[iMask++], masks[iMask++], masks[iMask++], masks[iMask++]);

    m_total = lContentLength + m_pos;
    return true;
}
//===============================================
bool GRequestWebsocket::analyzeRequest() {
    if(m_data.isEmpty()) return false;
    ulong lByte;

    // 1B : FIN-RSV1-RSV2-RSV3-OPCODE1-OPCODE2-OPCODE3-OPCODE4
    lByte = m_data[m_pos++];
    bool isFin = ((lByte & 0x80) >> 7);
    char lRsv = ((lByte & 0x70) >> 4);
    char lOpcode = ((lByte & 0x0F) >> 0);

    if((lOpcode != WEBSOCKET_OPCODE_CONTINUE) &&
       (lOpcode != WEBSOCKET_OPCODE_TEXT) &&
       (lOpcode != WEBSOCKET_OPCODE_BINARY) &&
       (lOpcode != WEBSOCKET_OPCODE_CLOSE) &&
       (lOpcode != WEBSOCKET_OPCODE_PING) &&
       (lOpcode != WEBSOCKET_OPCODE_PONG)) {
        slog(eGERR, "Le code opération  n'est pas supporté."
                    "|isFin=%d"
                    "|rsv=%d"
                    "|opcode=%d", isFin, lRsv, lOpcode);
        m_logs.addProblem();
        return false;
    }

    if(lOpcode == WEBSOCKET_OPCODE_CLOSE) {
        m_isClose = true;
    }

    if(lRsv) {
        slog(eGERR, "Les extensions du protocole WEBSOCKET ne sont pas supportées."
                    "|isFin=%d"
                    "|rsv=%d"
                    "|opcode=%d", isFin, lRsv, lOpcode);
        m_logs.addProblem();
        return false;
    }

    // 1B : MASK-PL1-PL2-PL3-PL4-PL5-PL6-PL7
    lByte = m_data[m_pos++];
    bool isMask = ((lByte & 0x80) >> 7);
    char lPayloadLength = ((lByte & 0x7F) >> 0);
    int lContentLength = 0;

    // 0B
    if(lPayloadLength >= 0 && lPayloadLength <= 125) {
        lContentLength = lPayloadLength;
    }
    // 2B : LENGHT1-LENGTH2
    else if(lPayloadLength == 126) {
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 8);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 0);
    }
    // 8B : LENGHT1-LENGTH2-LENGTH3-LENGTH4-LENGTH5-LENGTH6-LENGTH7-LENGTH8
    else if(lPayloadLength == 127) {
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 56);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 48);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 40);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 32);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 24);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 16);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 8);
        lByte = m_data[m_pos++];
        lContentLength |= (lByte << 0);
    }

    // 4B : MASK1-MASK2-MASK3-MASK4;
    char masks[4] = {0}, iMask = 0;
    if(isMask) {
        lByte = m_data[m_pos++];
        masks[iMask++] = lByte;
        lByte = m_data[m_pos++];
        masks[iMask++] = lByte;
        lByte = m_data[m_pos++];
        masks[iMask++] = lByte;
        lByte = m_data[m_pos++];
        masks[iMask++] = lByte;
    }

    // nB : DATA[1]-...-DATA[n]
    int lPos = m_pos;
    for(int i = 0; i < lContentLength; i++) {
        m_data[m_pos] = masks[i % 4] ^ m_data[m_pos];
        m_pos++;
    }

    m_request = GString(&m_data[lPos], lContentLength);

    iMask = 0;
    slog(eGINF, "Les données de la trame WEBSOCKET."
                "|isFin=%d"
                "|rsv=%d"
                "|opcode=%d"
                "|isClose=%d"
                "|isMask=%d"
                "|payloadLength=%d"
                "|contentLength=%d"
                "|mask_1=0x%02X"
                "|mask_2=0x%02X"
                "|mask_3=0x%02X"
                "|mask_4=0x%02X"
                "|requestData=%s", isFin, lRsv, lOpcode, m_isClose, isMask, lPayloadLength, lContentLength
                , masks[iMask++], masks[iMask++], masks[iMask++], masks[iMask++], m_request.c_str());

    m_total = lContentLength + m_pos;
    return true;
}
//===============================================
