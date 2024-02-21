//===============================================
#include "GCarpoolCB.h"
#include "GMySQL.h"
//===============================================
GCarpoolCB::GCarpoolCB()
: GManager() {

}
//===============================================
GCarpoolCB::~GCarpoolCB() {

}
//===============================================
GString GCarpoolCB::serialize(const GString& _code) const {
    GCode lDom;
    lDom.createDoc();
    lDom.addData(_code, "email", m_email);
    lDom.addData(_code, "password", m_password);
    return lDom.toString();
}
//===============================================
void GCarpoolCB::deserialize(const GString& _data, const GString& _code) {
    GManager::deserialize(_data);
    GCode lDom;
    lDom.loadXml(_data);
    m_email = lDom.getData(_code, "email");
    m_password = lDom.getData(_code, "password");
}
//===============================================
void GCarpoolCB::run() {
    deserialize(m_request);

    slog(eGINF, "Traitement de la requête XML."
                "|module=%s"
                "|method=%s", m_module.c_str(), m_method.c_str());

    if(m_module == "carpool") {
        runCarpool();
    }
    else {
        slog(eGERR, "Le module est inconnue."
                    "|uri=%s"
                    "|content_type=%s"
                    "|request=%s", m_uri.c_str(), m_contentType.c_str(), m_request.c_str());
        createUnknown();
    }
}
//===============================================
void GCarpoolCB::runCarpool() {
    if(m_method == "hello_world") {
        runHelloWorld();
    }
    else if(m_method == "inscription_email") {
        runInscriptionEmail();
    }
    else {
        slog(eGERR, "La méthode est inconnue."
                    "|uri=%s"
                    "|content_type=%s"
                    "|request=%s", m_uri.c_str(), m_contentType.c_str(), m_request.c_str());
        createUnknown();
    }
    createResponse();
}
//===============================================
void GCarpoolCB::runHelloWorld() {
    m_content += serialize();
}
//===============================================
void GCarpoolCB::runInscriptionEmail() {
    if(m_email.isEmpty()) {
        slog(eGERR, "L'email est obligatoire.");
        m_logs.addProblem();
        return;
    }

    GMySQL dbSQL;
    dbSQL.insertQuery(""
            " insert into _user (_email) "
            " values (?) "
            "", MYSQL_TYPE_STRING, m_email.c_str()
            , MYSQL_TYPE_END);

    m_logs.addLogs(dbSQL.getLogs());
}
//===============================================
