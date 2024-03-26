//===============================================
#include "GCarpoolEmail.h"
#include "GEmail.h"
#include "GMySQL.h"
//===============================================
GCarpoolEmail::GCarpoolEmail()
: GManager()
, m_id(0)
, m_status(0)
, m_isNewsletter(false) {

}
//===============================================
GCarpoolEmail::~GCarpoolEmail() {

}
//===============================================
GString GCarpoolEmail::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "id", m_id);
    lDom.addData(_code, "uuid", m_uuid);
    lDom.addData(_code, "email", m_email);
    lDom.addData(_code, "password", m_password);
    lDom.addData(_code, "confirm", m_confirm);
    lDom.addData(_code, "is_newletter", m_isNewsletter);
    lDom.addData(_code, "status", m_status);
    return lDom.toString();
}
//===============================================
void GCarpoolEmail::deserialize(const GString& _data, const GString& _code) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_id = lDom.getData(_code, "id").toInt();
    m_uuid = lDom.getData(_code, "uuid");
    m_email = lDom.getData(_code, "email");
    m_password = lDom.getData(_code, "password");
    m_confirm = lDom.getData(_code, "confirm");
    m_isNewsletter = lDom.getData(_code, "is_newsletter").toBool();
    m_status = lDom.getData(_code, "status").toChar();
}
//===============================================
void GCarpoolEmail::run() {
    deserialize(m_request);

    if(m_method == "inscription") {
        runInscription();
    }
    else {
        slog(eGERR, "La méthode est inconnue."
                    "|module=%s"
                    "|method=%s", m_module.c_str(), m_method.c_str());
        createUnknown();
    }
    createResponse();
}
//===============================================
void GCarpoolEmail::runInscription() {
    if(m_email.isEmpty()) {
        slog(eGERR, "L'email est obligatoire.");
        return;
    }
    if(m_email.size() >= 50) {
        slog(eGERR, "L'email est supérieur à 50 caractères."
                    "|size=%d", m_email.size());
        return;
    }
    GEmail lEmail = m_email;
    if(!lEmail.isValid()) {
        slog(eGERR, "L'email est invalide."
                    "|email=%s", m_email.c_str());
        return;
    }

    if(insertEmail()) {
        updateUuid(suuid());
        updateStatus(CARPOOL_STATUS_EMAIL_CREATE);
    }

    if(!m_logs.hasErrors()) {
        m_logs.addSuccess();
    }
}
//===============================================
bool GCarpoolEmail::insertEmail() {
    if(m_id) {
        slog(eGERR, "L'email est déjà inséré.");
        return false;
    }
    if(m_email.isEmpty()) {
        slog(eGERR, "L'email est obligatoire.");
        return false;
    }
    GMySQL dbSQL;
    dbSQL.setCommon(*this);
    dbSQL.insertQuery(""
            " insert into _user (_email) "
            " values ( #(email)s ) "
            "", "email", m_email.c_str());
    m_logs.addLogs(dbSQL.getLogs());
    m_id = dbSQL.getId();

    slog(eGINF, "Enregistrement des données."
                "|id=%d"
                "|email=%s"
                "|isNewsletter=%d", m_id, m_email.c_str(), m_isNewsletter);

    return !m_logs.hasErrors();
}
//===============================================
bool GCarpoolEmail::updateUuid(const GString& _uuid) {
    if(!m_id) {
        slog(eGERR, "L'id est obligatoire.");
        return false;
    }
    if(_uuid.isEmpty()) {
        slog(eGERR, "L'uuid est obligatoire.");
        return false;
    }
    m_uuid = _uuid;
    GMySQL dbSQL;
    dbSQL.setCommon(*this);
    dbSQL.execQuery(""
            " update _user set "
            " _uuid = #(uuid)s "
            " where _id = #(id)i "
            "", "id", m_id
            , "uuid", _uuid.c_str());
    m_logs.addLogs(dbSQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GCarpoolEmail::updateStatus(char _status) {
    if(!m_id) {
        slog(eGERR, "L'id est obligatoire.");
        return false;
    }
    if(!_status) {
        slog(eGERR, "Le status est obligatoire.");
        return false;
    }
    m_status = _status;
    GString lStatus = _status;
    GMySQL dbSQL;
    dbSQL.setCommon(*this);
    dbSQL.execQuery(""
            " update _user set "
            " _status = #(status)s "
            " where _id = #(id)i "
            "", "id", m_id
            , "status", lStatus.c_str());
    m_logs.addLogs(dbSQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GCarpoolEmail::loadEmail() {
    return !m_logs.hasErrors();
}
//===============================================
