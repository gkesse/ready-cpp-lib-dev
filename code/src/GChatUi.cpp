//===============================================
#include "GChatUi.h"
//===============================================
GChatUi::GChatUi()
: GPage() {

}
//===============================================
GChatUi::~GChatUi() {

}
//===============================================
void GChatUi::run() {
    if(m_uri == "/chat/connect") {
        runConnect();
    }
    else {
        slog(eGERR, "L'uri n'est pas gérée."
                    "|uri=%s", m_uri.c_str());
        m_logs.addProblem();
        createUnknown();
    }
}
//===============================================
void GChatUi::runConnect() {
    slog(eGINF, "Traitement de la connexion.");
    m_isContinue = true;
    m_logs.addSuccess();
}
//===============================================
