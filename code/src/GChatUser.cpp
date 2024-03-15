//===============================================
#include "GChatUser.h"
#include "GChatDao.h"
//===============================================
GChatUser::GChatUser()
: GChatCB() {

}
//===============================================
GChatUser::~GChatUser() {

}
//===============================================
GString GChatUser::serializeXml() const {
    GXml lDom;
    lDom.createDoc("datas");
    lDom.addData("uuid", m_uuid);
    lDom.addData("pseudo", m_pseudo);
    return lDom.toString();
}
//===============================================
void GChatUser::deserializeXml() {
    GXml lDom;
    lDom.loadXml(m_request);
    m_uuid      = lDom.getNode("/datas/params/uuid").getValue();
    m_pseudo    = lDom.getNode("/datas/params/pseudo").getValue();
}
//===============================================
void GChatUser::run() {
    deserializeXml();

    if(m_method == "create") {
        runCreate();
    }
    else if(m_method == "connect") {
        runConnect();
    }
    else {
        slog(eGERR, "La méthode est inconnue."
                    "|module=%s"
                    "|method=%s", m_module.c_str(), m_method.c_str());
        createUnknown();
    }
}
//===============================================
void GChatUser::runCreate() {
    slog(eGINF, "Exécution de la méthode."
                "|module=%s"
                "|method=%s", m_module.c_str(), m_method.c_str());

    if(!m_uuid.isEmpty()) {
        slog(eGERR, "L'utilisateur est déjà connecté.");
        return;
    }
    if(m_pseudo.isEmpty()) {
        slog(eGERR, "Le pseudo est obligatoire.");
        return;
    }
    if(m_pseudo.size() >= 50) {
        slog(eGERR, "Le pseudo est supérieur à 50 caractères."
                    "|size=%d", m_pseudo.size());
        return;
    }

    GChatDao dao;
    dao.createUser(*this);
    m_logs.addLogs(dao.getLogs());

    if(!m_logs.hasErrors()) {
        m_content += serializeXml();
    }
}
//===============================================
void GChatUser::runConnect() {
    slog(eGINF, "Exécution de la méthode."
                "|module=%s"
                "|method=%s", m_module.c_str(), m_method.c_str());

    if(!m_uuid.isEmpty()) {
        slog(eGERR, "L'utilisateur est déjà connecté.");
        return;
    }
    if(m_pseudo.isEmpty()) {
        slog(eGERR, "Le pseudo est obligatoire.");
        return;
    }
    if(m_pseudo.size() >= 50) {
        slog(eGERR, "Le pseudo est supérieur à 50 caractères."
                    "|size=%d", m_pseudo.size());
        return;
    }

    GChatDao dao;
    dao.connectUser(*this);
    m_logs.addLogs(dao.getLogs());

    if(!m_logs.hasErrors()) {
        GChatUser lObj;
        lObj.setUuid(m_uuid);
        m_content += lObj.serializeXml();
        m_isContinue = false;
    }
}
//===============================================
