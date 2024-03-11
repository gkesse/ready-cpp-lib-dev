//===============================================
#include "GChatDao.h"
#include "GChatUser.h"
#include "GMySQL.h"
//===============================================
GChatDao::GChatDao()
: GObject()
, m_dbSQL("db_chat_test") {

}
//===============================================
GChatDao::~GChatDao() {

}
//===============================================
bool GChatDao::createUser(GChatUser& _obj) {
    m_dbSQL.setCommon(*this);
    m_dbSQL.insertQuery(""
            "insert into _user ( _pseudo ) "
            "values ( #(pseudo)s ) "
            "", "pseudo", _obj.getPseudo().c_str());
    m_logs.addLogs(m_dbSQL.getLogs());
    if(!m_logs.hasErrors()) {
        updateUuid(_obj);
    }
    return !m_logs.hasErrors();
}
//===============================================
bool GChatDao::updateUuid(GChatUser& _obj) {
    _obj.setUuid(suuid());
    m_dbSQL.setCommon(*this);
    m_dbSQL.insertQuery(""
            "update _user set "
            "_uuid = #(uuid)s "
            "where _pseudo = #(pseudo)s "
            "", "uuid", _obj.getUuid().c_str()
            , "pseudo", _obj.getPseudo().c_str());
    m_logs.addLogs(m_dbSQL.getLogs());
    return !m_logs.hasErrors();
}
//===============================================
bool GChatDao::connectUser(GChatUser& _obj) {
    m_dbSQL.setCommon(*this);
    GMySQLMap lMap = m_dbSQL.readMap(""
            "select _uuid from _user "
            "where _pseudo = #(pseudo)s "
            "", "pseudo", _obj.getPseudo().c_str());
    m_logs.addLogs(m_dbSQL.getLogs());

    if(lMap.size() == 0) {
        slog(eGERR, "L'utilisateur n'existe pas."
                    "|pseudo=%s", _obj.getPseudo().c_str());
        m_logs.addProblem();
    }
    else if(lMap.size() > 1) {
        slog(eGERR, "L'utilisateur a des doublons."
                    "|pseudo=%s", _obj.getPseudo().c_str());
        m_logs.addProblem();
    }
    else {
        for(int i = 0, j = 0; i < lMap.size(); i++) {
            GMySQLRow lRow = lMap[i];
            _obj.setUuid(lRow[j++]);
        }
    }
    return !m_logs.hasErrors();
}
//===============================================
