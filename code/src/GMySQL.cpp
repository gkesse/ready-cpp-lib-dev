//===============================================
#include "GMySQL.h"
#include "GRegex.h"
//===============================================
GMySQL* GMySQL::m_instance = 0;
//===============================================
GMySQL::GMySQL()
: GObject()
, m_protocol(MYSQL_CONN_PROTOCOL)
, m_hostname(MYSQL_CONN_HOSTNAME)
, m_database(MYSQL_CONN_DATABASE)
, m_username(MYSQL_CONN_USERNAME)
, m_password(MYSQL_CONN_PASSWORD)
, m_port(MYSQL_CONN_PORT)
, m_id(0)
, m_errorCode(0) {

}
//===============================================
GMySQL::GMySQL(const GString& _database)
: GObject()
, m_protocol(MYSQL_CONN_PROTOCOL)
, m_hostname(MYSQL_CONN_HOSTNAME)
, m_database(_database)
, m_username(MYSQL_CONN_USERNAME)
, m_password(MYSQL_CONN_PASSWORD)
, m_port(MYSQL_CONN_PORT)
, m_id(0)
, m_errorCode(0) {

}
//===============================================
GMySQL::~GMySQL() {

}
//===============================================
GMySQL* GMySQL::Instance() {
    if(m_instance == 0) {
        m_instance = new GMySQL;
    }
    return m_instance;
}
//===============================================
int GMySQL::getId() const {
    return m_id;
}
//===============================================
int GMySQL::getErrorCode() const {
    return m_errorCode;
}
//===============================================
GString GMySQL::convertZeroToNull(int _data) const {
    if(_data == 0) return "null";
    return _data;
}
//===============================================
GString GMySQL::convertBooleanToChar(bool _data) const {
    if(_data) return "'1'";
    return "'0'";
}
//===============================================
GString GMySQL::getUUID() const {
    GMySQL dbSQL;
    return dbSQL.readData("select uuid() as _uuid");
}
//===============================================
int GMySQL::getColumnCount(std::shared_ptr<sql::ResultSet>& _resultSet) const {
    int lColumns = _resultSet->getMetaData()->getColumnCount();
    return lColumns;
}
//===============================================
bool GMySQL::openDatabase(std::shared_ptr<sql::Connection>& _conn) {
    try {
        sql::Driver* lDriver = get_driver_instance();

        if(!lDriver) {
            slog(eGERR, "Le driver mysql n'est pas initialisé.");
            m_logs.addProblem();
            return false;
        }

        GString lPath = sformat("%s://%s:%d/%s"
                , m_protocol.c_str()
                , m_hostname.c_str()
                , m_port
                , m_database.c_str()
        );

        _conn.reset(lDriver->connect(lPath.c_str(), m_username.c_str(), m_password.c_str()));
    }
    catch(sql::SQLException& e) {
        slog(eGERR, "Le connecteur mysql n'est pas initialisé."
                    "|error_code=%d"
                    "|error_state=%s"
                    "|error_msg=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what());
        m_logs.addProblem();
        m_errorCode = e.getErrorCode();
        return false;
    }
    return true;
}
//===============================================
bool GMySQL::execQuery(const GString& _sql, ...) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::PreparedStatement> lStatement;

    try {
        if(!openDatabase(lConn)) {
            slog(eGERR, "L'ouverture de la base donnée a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return false;
        }

        GRegex lRegex = _sql;
        int lCount = lRegex.countMatch("#\\([A-Za-z]+\\)[a-z]");
        GMap lTypes, lPatterns, lValues;
        std::vector<GString> lParams;

        lTypes.createMap();
        lPatterns.createMap();
        lValues.createMap();

        for(int i = 0; i < lCount; i++) {
            GString lPattern = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 0);
            GString lName = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 1);
            GString lType = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 2);

            if((lType != "b") && (lType != "bool") &&
               (lType != "i") && (lType != "int") &&
               (lType != "ii") && (lType != "bigint") &&
               (lType != "s") && (lType != "string") &&
               (lType != "d") && (lType != "double") &&
               (lType != "bb") && (lType != "blob") &&
               (lType != "dt") && (lType != "datetime")) {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|pattern=%s"
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lPattern.c_str(), lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return false;
            }

            lTypes.addData(lName, lType);
            lPatterns.addData(lPattern, lName);
            lParams.push_back(lPattern);
        }

        if(lTypes.size() != lPatterns.size()) {
            slog(eGERR, "Les nombres de paramètres et de patterns sont différents."
                        "|pattern=%d"
                        "|name=%d"
                        "|sql=%s", lPatterns.size(), lTypes.size(), _sql.c_str());
            m_logs.addProblem();
            return false;
        }

        va_list lArgs;
        va_start(lArgs, _sql);

        for(int i = 0; i < lTypes.size(); i++) {
            GString lName = (const char*)va_arg(lArgs, const char*);
            if(!lTypes.isKey(lName)) {
                slog(eGERR, "Le nom de paramètre est inconnu."
                            "|name=%s"
                            "|sql=%s", lName.c_str(), _sql.c_str());
                m_logs.addProblem();
                return false;
            }
            GString lType = lTypes.getData(lName);
            GString lValue;

            if((lType == "b") || (lType == "bool")) {
                lValue = (bool)va_arg(lArgs, int);
            }
            else if((lType == "i") || (lType == "int")) {
                lValue = (int)va_arg(lArgs, int);
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lValue = (long)va_arg(lArgs, long);
            }
            else if((lType == "d") || (lType == "double")) {
                lValue = (double)va_arg(lArgs, double);
            }
            else if((lType == "s") || (lType == "string")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "bb") && (lType == "blob")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return false;
            }

            lValues.addData(lName, lValue);
        }

        va_end(lArgs);

        GString lSql = lRegex.replaceMatch("#\\([A-Za-z]+\\)[a-z]", "?");

        slog(eGOFF, "La requête sql a été transformée."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSql.c_str());

        lStatement.reset(lConn->prepareStatement(lSql.c_str()));

        GString lSqlText = lRegex;

        for(int i = 0; i < lPatterns.size(); i++) {
            GMapKV lMapKV = lPatterns.getData(i);
            GString lPattern = lMapKV.m_key;
            GString lName = lMapKV.m_value;
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            if((lType == "s") || (lType == "string")) {
                lValue = sformat("'%s'", lValue.c_str());
            }

            lSqlText = lSqlText.replaceAll(lPattern, lValue);
        }

        slog(eGOFF, "La requête sql a été traduite."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSqlText.c_str());

        int j = 1;
        for(int i = 0; i < lParams.size(); i++) {
            GString lPattern = lParams.at(i);
            GString lName = lPatterns.getData(lPattern);
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            slog(eGOFF, "La requête sql a été analysée."
                        "|index=%d"
                        "|pattern=%s"
                        "|name=%s"
                        "|type=%s"
                        "|value=%s", i, lPattern.c_str(), lName.c_str(), lType.c_str(), lValue.c_str());

            if((lType == "b") || (lType == "bool")) {
                lStatement->setBoolean(j++, lValue.toBool());
            }
            else if((lType == "i") || (lType == "int")) {
                lStatement->setInt(j++, lValue.toInt());
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lStatement->setBigInt(j++, lValue.c_str());
            }
            else if((lType == "d") || (lType == "double")) {
                lStatement->setDouble(j++, lValue.toDouble());
            }
            else if((lType == "s") || (lType == "string")) {
                lStatement->setString(j++, lValue.c_str());
            }
            else if((lType == "bb") && (lType == "blob")) {
                std::string lData(lValue.c_str(), lValue.size());
                std::istringstream lBlob(lData);
                lStatement->setBlob(j++, &lBlob);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lStatement->setDateTime(j++, lValue.c_str());
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return false;
            }
        }

        lStatement->execute();
    }
    catch (sql::SQLException& e) {
        if(e.getErrorCode() == MYSQL_ERROR_DUPLICATION) {
            slog(eGWAR, "La donnée existe déjà."
                        "|error_code=%d"
                        "|error_state=%s"
                        "|error_msg=%s"
                        "|sql=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what(), _sql.c_str());
        }
        else {
            slog(eGERR, "L'exécution de la requête a échoué."
                    "|error_code=%d"
                    "|error_state=%s"
                    "|error_msg=%s"
                    "|sql=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what(), _sql.c_str());
        }
        m_logs.addProblem();
        m_errorCode = e.getErrorCode();
        return false;
    }
    return true;
}
//===============================================
bool GMySQL::insertQuery(const GString& _sql, ...) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::PreparedStatement> lStatement;
    std::shared_ptr<sql::Statement> lStatementId;
    std::shared_ptr<sql::ResultSet> lResultSet;

    try {
        if(!openDatabase(lConn)) {
            slog(eGERR, "L'ouverture de la base donnée a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return false;
        }

        GRegex lRegex = _sql;
        int lCount = lRegex.countMatch("#\\([A-Za-z]+\\)[a-z]");
        GMap lTypes, lPatterns, lValues;
        std::vector<GString> lParams;

        lTypes.createMap();
        lPatterns.createMap();
        lValues.createMap();

        for(int i = 0; i < lCount; i++) {
            GString lPattern = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 0);
            GString lName = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 1);
            GString lType = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 2);

            if((lType != "b") && (lType != "bool") &&
               (lType != "i") && (lType != "int") &&
               (lType != "ii") && (lType != "bigint") &&
               (lType != "s") && (lType != "string") &&
               (lType != "d") && (lType != "double") &&
               (lType != "bb") && (lType != "blob") &&
               (lType != "dt") && (lType != "datetime")) {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|pattern=%s"
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lPattern.c_str(), lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return false;
            }

            lTypes.addData(lName, lType);
            lPatterns.addData(lPattern, lName);
            lParams.push_back(lPattern);
        }

        if(lTypes.size() != lPatterns.size()) {
            slog(eGERR, "Les nombres de paramètres et de patterns sont différents."
                        "|pattern=%d"
                        "|name=%d"
                        "|sql=%s", lPatterns.size(), lTypes.size(), _sql.c_str());
            m_logs.addProblem();
            return false;
        }

        va_list lArgs;
        va_start(lArgs, _sql);

        for(int i = 0; i < lTypes.size(); i++) {
            GString lName = (const char*)va_arg(lArgs, const char*);
            if(!lTypes.isKey(lName)) {
                slog(eGERR, "Le nom de paramètre est inconnu."
                            "|name=%s"
                            "|sql=%s", lName.c_str(), _sql.c_str());
                m_logs.addProblem();
                return false;
            }
            GString lType = lTypes.getData(lName);
            GString lValue;

            if((lType == "b") || (lType == "bool")) {
                lValue = (bool)va_arg(lArgs, int);
            }
            else if((lType == "i") || (lType == "int")) {
                lValue = (int)va_arg(lArgs, int);
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lValue = (long)va_arg(lArgs, long);
            }
            else if((lType == "d") || (lType == "double")) {
                lValue = (double)va_arg(lArgs, double);
            }
            else if((lType == "s") || (lType == "string")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "bb") && (lType == "blob")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return false;
            }

            lValues.addData(lName, lValue);
        }

        va_end(lArgs);

        GString lSql = lRegex.replaceMatch("#\\([A-Za-z]+\\)[a-z]", "?");

        slog(eGOFF, "La requête sql a été transformée."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSql.c_str());

        lStatement.reset(lConn->prepareStatement(lSql.c_str()));
        lStatementId.reset(lConn->createStatement());

        GString lSqlText = lRegex;

        for(int i = 0; i < lPatterns.size(); i++) {
            GMapKV lMapKV = lPatterns.getData(i);
            GString lPattern = lMapKV.m_key;
            GString lName = lMapKV.m_value;
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            if((lType == "s") || (lType == "string")) {
                lValue = sformat("'%s'", lValue.c_str());
            }

            lSqlText = lSqlText.replaceAll(lPattern, lValue);
        }

        slog(eGOFF, "La requête sql a été traduite."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSqlText.c_str());

        int j = 1;
        for(int i = 0; i < lParams.size(); i++) {
            GString lPattern = lParams.at(i);
            GString lName = lPatterns.getData(lPattern);
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            slog(eGOFF, "La requête sql a été analysée."
                        "|index=%d"
                        "|pattern=%s"
                        "|name=%s"
                        "|type=%s"
                        "|value=%s", i, lPattern.c_str(), lName.c_str(), lType.c_str(), lValue.c_str());

            if((lType == "b") || (lType == "bool")) {
                lStatement->setBoolean(j++, lValue.toBool());
            }
            else if((lType == "i") || (lType == "int")) {
                lStatement->setInt(j++, lValue.toInt());
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lStatement->setBigInt(j++, lValue.c_str());
            }
            else if((lType == "d") || (lType == "double")) {
                lStatement->setDouble(j++, lValue.toDouble());
            }
            else if((lType == "s") || (lType == "string")) {
                lStatement->setString(j++, lValue.c_str());
            }
            else if((lType == "bb") && (lType == "blob")) {
                std::string lData(lValue.c_str(), lValue.size());
                std::istringstream lBlob(lData);
                lStatement->setBlob(j++, &lBlob);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lStatement->setDateTime(j++, lValue.c_str());
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return false;
            }
        }

        lStatement->execute();
        lResultSet.reset(lStatementId->executeQuery("SELECT LAST_INSERT_ID() as _id"));
        lResultSet->next();
        m_id = (int)lResultSet->getInt64("_id");
    }
    catch (sql::SQLException& e) {
        if(e.getErrorCode() == MYSQL_ERROR_DUPLICATION) {
            slog(eGERR, "La donnée existe déjà."
                        "|error_code=%d"
                        "|error_state=%s"
                        "|error_msg=%s"
                        "|sql=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what(), _sql.c_str());
        }
        else {
            slog(eGERR, "L'exécution de la requête a échoué."
                    "|error_code=%d"
                    "|error_state=%s"
                    "|error_msg=%s"
                    "|sql=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what(), _sql.c_str());
        }
        m_logs.addProblem();
        m_errorCode = e.getErrorCode();
        return false;
    }
    return true;
}
//===============================================
GString GMySQL::readData(const GString& _sql, ...) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::PreparedStatement> lStatement;
    std::shared_ptr<sql::ResultSet> lResultSet;
    GString lData;

    try {
        if(!openDatabase(lConn)) {
            slog(eGERR, "L'ouverture de la base données a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return lData;
        }

        GRegex lRegex = _sql;
        int lCount = lRegex.countMatch("#\\([A-Za-z]+\\)[a-z]");
        GMap lTypes, lPatterns, lValues;
        std::vector<GString> lParams;

        lTypes.createMap();
        lPatterns.createMap();
        lValues.createMap();

        for(int i = 0; i < lCount; i++) {
            GString lPattern = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 0);
            GString lName = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 1);
            GString lType = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 2);

            if((lType != "b") && (lType != "bool") &&
               (lType != "i") && (lType != "int") &&
               (lType != "ii") && (lType != "bigint") &&
               (lType != "s") && (lType != "string") &&
               (lType != "d") && (lType != "double") &&
               (lType != "bb") && (lType != "blob") &&
               (lType != "dt") && (lType != "datetime")) {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|pattern=%s"
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lPattern.c_str(), lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lData;
            }

            lTypes.addData(lName, lType);
            lPatterns.addData(lPattern, lName);
            lParams.push_back(lPattern);
        }

        if(lTypes.size() != lPatterns.size()) {
            slog(eGERR, "Les nombres de paramètres et de patterns sont différents."
                        "|pattern=%d"
                        "|name=%d"
                        "|sql=%s", lPatterns.size(), lTypes.size(), _sql.c_str());
            m_logs.addProblem();
            return lData;
        }

        va_list lArgs;
        va_start(lArgs, _sql);

        for(int i = 0; i < lTypes.size(); i++) {
            GString lName = (const char*)va_arg(lArgs, const char*);
            if(!lTypes.isKey(lName)) {
                slog(eGERR, "Le nom de paramètre est inconnu."
                            "|name=%s"
                            "|sql=%s", lName.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lData;
            }
            GString lType = lTypes.getData(lName);
            GString lValue;

            if((lType == "b") || (lType == "bool")) {
                lValue = (bool)va_arg(lArgs, int);
            }
            else if((lType == "i") || (lType == "int")) {
                lValue = (int)va_arg(lArgs, int);
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lValue = (long)va_arg(lArgs, long);
            }
            else if((lType == "d") || (lType == "double")) {
                lValue = (double)va_arg(lArgs, double);
            }
            else if((lType == "s") || (lType == "string")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "bb") && (lType == "blob")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lData;
            }

            lValues.addData(lName, lValue);
        }

        va_end(lArgs);

        GString lSql = lRegex.replaceMatch("#\\([A-Za-z]+\\)[a-z]", "?");

        slog(eGOFF, "La requête sql a été transformée."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSql.c_str());

        lStatement.reset(lConn->prepareStatement(lSql.c_str()));

        GString lSqlText = lRegex;

        for(int i = 0; i < lPatterns.size(); i++) {
            GMapKV lMapKV = lPatterns.getData(i);
            GString lPattern = lMapKV.m_key;
            GString lName = lMapKV.m_value;
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            if((lType == "s") || (lType == "string")) {
                lValue = sformat("'%s'", lValue.c_str());
            }

            lSqlText = lSqlText.replaceAll(lPattern, lValue);
        }

        slog(eGOFF, "La requête sql a été traduite."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSqlText.c_str());

        int j = 1;
        for(int i = 0; i < lParams.size(); i++) {
            GString lPattern = lParams.at(i);
            GString lName = lPatterns.getData(lPattern);
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            slog(eGOFF, "La requête sql a été analysée."
                        "|index=%d"
                        "|pattern=%s"
                        "|name=%s"
                        "|type=%s"
                        "|value=%s", i, lPattern.c_str(), lName.c_str(), lType.c_str(), lValue.c_str());

            if((lType == "b") || (lType == "bool")) {
                lStatement->setBoolean(j++, lValue.toBool());
            }
            else if((lType == "i") || (lType == "int")) {
                lStatement->setInt(j++, lValue.toInt());
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lStatement->setBigInt(j++, lValue.c_str());
            }
            else if((lType == "d") || (lType == "double")) {
                lStatement->setDouble(j++, lValue.toDouble());
            }
            else if((lType == "s") || (lType == "string")) {
                lStatement->setString(j++, lValue.c_str());
            }
            else if((lType == "bb") && (lType == "blob")) {
                std::string lData(lValue.c_str(), lValue.size());
                std::istringstream lBlob(lData);
                lStatement->setBlob(j++, &lBlob);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lStatement->setDateTime(j++, lValue.c_str());
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lData;
            }
        }

        lResultSet.reset(lStatement->executeQuery());
    }
    catch (sql::SQLException &e) {
        slog(eGERR, "L'exécution de la requête a échoué."
                "|error_code=%d"
                "|error_state=%s"
                "|error_msg=%s"
                "|sql=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what(), _sql.c_str());
        m_logs.addProblem();
        m_errorCode = e.getErrorCode();
        return lData;
    }


    while(lResultSet->next()) {
        lData = lResultSet->getString(1);
        break;
    }

    return lData;
}
//===============================================
GMySQLRow GMySQL::readCol(const GString& _sql, ...) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::PreparedStatement> lStatement;
    std::shared_ptr<sql::ResultSet> lResultSet;
    GMySQLRow lDataMap;

    try {
        if(!openDatabase(lConn)) {
            slog(eGERR, "L'ouverture de la base donnée a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
        }

        GRegex lRegex = _sql;
        int lCount = lRegex.countMatch("#\\([A-Za-z]+\\)[a-z]");
        GMap lTypes, lPatterns, lValues;
        std::vector<GString> lParams;

        lTypes.createMap();
        lPatterns.createMap();
        lValues.createMap();

        for(int i = 0; i < lCount; i++) {
            GString lPattern = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 0);
            GString lName = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 1);
            GString lType = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 2);

            if((lType != "b") && (lType != "bool") &&
               (lType != "i") && (lType != "int") &&
               (lType != "ii") && (lType != "bigint") &&
               (lType != "s") && (lType != "string") &&
               (lType != "d") && (lType != "double") &&
               (lType != "bb") && (lType != "blob") &&
               (lType != "dt") && (lType != "datetime")) {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|pattern=%s"
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lPattern.c_str(), lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }

            lTypes.addData(lName, lType);
            lPatterns.addData(lPattern, lName);
            lParams.push_back(lPattern);
        }

        if(lTypes.size() != lPatterns.size()) {
            slog(eGERR, "Les nombres de paramètres et de patterns sont différents."
                        "|pattern=%d"
                        "|name=%d"
                        "|sql=%s", lPatterns.size(), lTypes.size(), _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
        }

        va_list lArgs;
        va_start(lArgs, _sql);

        for(int i = 0; i < lTypes.size(); i++) {
            GString lName = (const char*)va_arg(lArgs, const char*);
            if(!lTypes.isKey(lName)) {
                slog(eGERR, "Le nom de paramètre est inconnu."
                            "|name=%s"
                            "|sql=%s", lName.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }
            GString lType = lTypes.getData(lName);
            GString lValue;

            if((lType == "b") || (lType == "bool")) {
                lValue = (bool)va_arg(lArgs, int);
            }
            else if((lType == "i") || (lType == "int")) {
                lValue = (int)va_arg(lArgs, int);
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lValue = (long)va_arg(lArgs, long);
            }
            else if((lType == "d") || (lType == "double")) {
                lValue = (double)va_arg(lArgs, double);
            }
            else if((lType == "s") || (lType == "string")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "bb") && (lType == "blob")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }

            lValues.addData(lName, lValue);
        }

        va_end(lArgs);

        GString lSql = lRegex.replaceMatch("#\\([A-Za-z]+\\)[a-z]", "?");

        slog(eGOFF, "La requête sql a été transformée."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSql.c_str());

        lStatement.reset(lConn->prepareStatement(lSql.c_str()));

        GString lSqlText = lRegex;

        for(int i = 0; i < lPatterns.size(); i++) {
            GMapKV lMapKV = lPatterns.getData(i);
            GString lPattern = lMapKV.m_key;
            GString lName = lMapKV.m_value;
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            if((lType == "s") || (lType == "string")) {
                lValue = sformat("'%s'", lValue.c_str());
            }

            lSqlText = lSqlText.replaceAll(lPattern, lValue);
        }

        slog(eGOFF, "La requête sql a été traduite."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSqlText.c_str());

        int j = 1;
        for(int i = 0; i < lParams.size(); i++) {
            GString lPattern = lParams.at(i);
            GString lName = lPatterns.getData(lPattern);
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            slog(eGOFF, "La requête sql a été analysée."
                        "|index=%d"
                        "|pattern=%s"
                        "|name=%s"
                        "|type=%s"
                        "|value=%s", i, lPattern.c_str(), lName.c_str(), lType.c_str(), lValue.c_str());

            if((lType == "b") || (lType == "bool")) {
                lStatement->setBoolean(j++, lValue.toBool());
            }
            else if((lType == "i") || (lType == "int")) {
                lStatement->setInt(j++, lValue.toInt());
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lStatement->setBigInt(j++, lValue.c_str());
            }
            else if((lType == "d") || (lType == "double")) {
                lStatement->setDouble(j++, lValue.toDouble());
            }
            else if((lType == "s") || (lType == "string")) {
                lStatement->setString(j++, lValue.c_str());
            }
            else if((lType == "bb") && (lType == "blob")) {
                std::string lData(lValue.c_str(), lValue.size());
                std::istringstream lBlob(lData);
                lStatement->setBlob(j++, &lBlob);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lStatement->setDateTime(j++, lValue.c_str());
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }
        }

        lResultSet.reset(lStatement->executeQuery());
    }
    catch (sql::SQLException &e) {
        slog(eGERR, "L'exécution de la requête a échoué."
                "|error_code=%d"
                "|error_state=%s"
                "|error_msg=%s"
                "|sql=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what(), _sql.c_str());
        m_logs.addProblem();
        m_errorCode = e.getErrorCode();
        return lDataMap;
    }

    while(lResultSet->next()) {
        GString lData = lResultSet->getString(1).c_str();
        lDataMap.push_back(lData);
    }

    return lDataMap;
}
//===============================================
GMySQLRow GMySQL::readRow(const GString& _sql, ...) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::PreparedStatement> lStatement;
    std::shared_ptr<sql::ResultSet> lResultSet;
    GMySQLRow lDataMap;

    try {
        if(!openDatabase(lConn)) {
            slog(eGERR, "L'ouverture de la base donnée a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
        }

        GRegex lRegex = _sql;
        int lCount = lRegex.countMatch("#\\([A-Za-z]+\\)[a-z]");
        GMap lTypes, lPatterns, lValues;
        std::vector<GString> lParams;

        lTypes.createMap();
        lPatterns.createMap();
        lValues.createMap();

        for(int i = 0; i < lCount; i++) {
            GString lPattern = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 0);
            GString lName = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 1);
            GString lType = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 2);

            if((lType != "b") && (lType != "bool") &&
               (lType != "i") && (lType != "int") &&
               (lType != "ii") && (lType != "bigint") &&
               (lType != "s") && (lType != "string") &&
               (lType != "d") && (lType != "double") &&
               (lType != "bb") && (lType != "blob") &&
               (lType != "dt") && (lType != "datetime")) {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|pattern=%s"
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lPattern.c_str(), lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }

            lTypes.addData(lName, lType);
            lPatterns.addData(lPattern, lName);
            lParams.push_back(lPattern);
        }

        if(lTypes.size() != lPatterns.size()) {
            slog(eGERR, "Les nombres de paramètres et de patterns sont différents."
                        "|pattern=%d"
                        "|name=%d"
                        "|sql=%s", lPatterns.size(), lTypes.size(), _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
        }

        va_list lArgs;
        va_start(lArgs, _sql);

        for(int i = 0; i < lTypes.size(); i++) {
            GString lName = (const char*)va_arg(lArgs, const char*);
            if(!lTypes.isKey(lName)) {
                slog(eGERR, "Le nom de paramètre est inconnu."
                            "|name=%s"
                            "|sql=%s", lName.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }
            GString lType = lTypes.getData(lName);
            GString lValue;

            if((lType == "b") || (lType == "bool")) {
                lValue = (bool)va_arg(lArgs, int);
            }
            else if((lType == "i") || (lType == "int")) {
                lValue = (int)va_arg(lArgs, int);
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lValue = (long)va_arg(lArgs, long);
            }
            else if((lType == "d") || (lType == "double")) {
                lValue = (double)va_arg(lArgs, double);
            }
            else if((lType == "s") || (lType == "string")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "bb") && (lType == "blob")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }

            lValues.addData(lName, lValue);
        }

        va_end(lArgs);

        GString lSql = lRegex.replaceMatch("#\\([A-Za-z]+\\)[a-z]", "?");

        slog(eGOFF, "La requête sql a été transformée."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSql.c_str());

        lStatement.reset(lConn->prepareStatement(lSql.c_str()));

        GString lSqlText = lRegex;

        for(int i = 0; i < lPatterns.size(); i++) {
            GMapKV lMapKV = lPatterns.getData(i);
            GString lPattern = lMapKV.m_key;
            GString lName = lMapKV.m_value;
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            if((lType == "s") || (lType == "string")) {
                lValue = sformat("'%s'", lValue.c_str());
            }

            lSqlText = lSqlText.replaceAll(lPattern, lValue);
        }

        slog(eGOFF, "La requête sql a été traduite."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSqlText.c_str());

        int j = 1;
        for(int i = 0; i < lParams.size(); i++) {
            GString lPattern = lParams.at(i);
            GString lName = lPatterns.getData(lPattern);
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            slog(eGOFF, "La requête sql a été analysée."
                        "|index=%d"
                        "|pattern=%s"
                        "|name=%s"
                        "|type=%s"
                        "|value=%s", i, lPattern.c_str(), lName.c_str(), lType.c_str(), lValue.c_str());

            if((lType == "b") || (lType == "bool")) {
                lStatement->setBoolean(j++, lValue.toBool());
            }
            else if((lType == "i") || (lType == "int")) {
                lStatement->setInt(j++, lValue.toInt());
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lStatement->setBigInt(j++, lValue.c_str());
            }
            else if((lType == "d") || (lType == "double")) {
                lStatement->setDouble(j++, lValue.toDouble());
            }
            else if((lType == "s") || (lType == "string")) {
                lStatement->setString(j++, lValue.c_str());
            }
            else if((lType == "bb") && (lType == "blob")) {
                std::string lData(lValue.c_str(), lValue.size());
                std::istringstream lBlob(lData);
                lStatement->setBlob(j++, &lBlob);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lStatement->setDateTime(j++, lValue.c_str());
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }
        }

        lResultSet.reset(lStatement->executeQuery());
    }
    catch (sql::SQLException &e) {
        slog(eGERR, "L'exécution de la requête a échoué."
                "|error_code=%d"
                "|error_state=%s"
                "|error_msg=%s"
                "|sql=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what(), _sql.c_str());
        m_logs.addProblem();
        m_errorCode = e.getErrorCode();
        return lDataMap;
    }

    int lColumns = getColumnCount(lResultSet);
    while(lResultSet->next()) {
        for(int i = 1; i <= lColumns; i++) {
            GString lData = lResultSet->getString(i).c_str();
            lDataMap.push_back(lData);
        }
        break;
    }
    return lDataMap;
}
//===============================================
GMySQLMap GMySQL::readMap(const GString& _sql, ...) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::PreparedStatement> lStatement;
    std::shared_ptr<sql::ResultSet> lResultSet;
    GMySQLMap lDataMap;

    try {
        if(!openDatabase(lConn)) {
            slog(eGERR, "L'ouverture de la base donnée a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
        }

        GRegex lRegex = _sql;
        int lCount = lRegex.countMatch("#\\([A-Za-z]+\\)[a-z]");
        GMap lTypes, lPatterns, lValues;
        std::vector<GString> lParams;

        lTypes.createMap();
        lPatterns.createMap();
        lValues.createMap();

        for(int i = 0; i < lCount; i++) {
            GString lPattern = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 0);
            GString lName = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 1);
            GString lType = lRegex.searchMatch("#\\(([A-Za-z]+)\\)([^ ]+)", i, 2);

            if((lType != "b") && (lType != "bool") &&
               (lType != "i") && (lType != "int") &&
               (lType != "ii") && (lType != "bigint") &&
               (lType != "s") && (lType != "string") &&
               (lType != "d") && (lType != "double") &&
               (lType != "bb") && (lType != "blob") &&
               (lType != "dt") && (lType != "datetime")) {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|pattern=%s"
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lPattern.c_str(), lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }

            lTypes.addData(lName, lType);
            lPatterns.addData(lPattern, lName);
            lParams.push_back(lPattern);
        }

        if(lTypes.size() != lPatterns.size()) {
            slog(eGERR, "Les nombres de paramètres et de patterns sont différents."
                        "|pattern=%d"
                        "|name=%d"
                        "|sql=%s", lPatterns.size(), lTypes.size(), _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
        }

        va_list lArgs;
        va_start(lArgs, _sql);

        for(int i = 0; i < lTypes.size(); i++) {
            GString lName = (const char*)va_arg(lArgs, const char*);
            if(!lTypes.isKey(lName)) {
                slog(eGERR, "Le nom de paramètre est inconnu."
                            "|name=%s"
                            "|sql=%s", lName.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }
            GString lType = lTypes.getData(lName);
            GString lValue;

            if((lType == "b") || (lType == "bool")) {
                lValue = (bool)va_arg(lArgs, int);
            }
            else if((lType == "i") || (lType == "int")) {
                lValue = (int)va_arg(lArgs, int);
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lValue = (long)va_arg(lArgs, long);
            }
            else if((lType == "d") || (lType == "double")) {
                lValue = (double)va_arg(lArgs, double);
            }
            else if((lType == "s") || (lType == "string")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "bb") && (lType == "blob")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lValue = (const char*)va_arg(lArgs, const char*);
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }

            lValues.addData(lName, lValue);
        }

        va_end(lArgs);

        GString lSql = lRegex.replaceMatch("#\\([A-Za-z]+\\)[a-z]", "?");

        slog(eGOFF, "La requête sql a été transformée."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSql.c_str());

        lStatement.reset(lConn->prepareStatement(lSql.c_str()));

        GString lSqlText = lRegex;

        for(int i = 0; i < lPatterns.size(); i++) {
            GMapKV lMapKV = lPatterns.getData(i);
            GString lPattern = lMapKV.m_key;
            GString lName = lMapKV.m_value;
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            if((lType == "s") || (lType == "string")) {
                lValue = sformat("'%s'", lValue.c_str());
            }

            lSqlText = lSqlText.replaceAll(lPattern, lValue);
        }

        slog(eGOFF, "La requête sql a été traduite."
                    "|size=%d"
                    "|sql=%s", lParams.size(), lSqlText.c_str());

        int j = 1;
        for(int i = 0; i < lParams.size(); i++) {
            GString lPattern = lParams.at(i);
            GString lName = lPatterns.getData(lPattern);
            GString lValue = lValues.getData(lName);
            GString lType = lTypes.getData(lName);

            slog(eGOFF, "La requête sql a été analysée."
                        "|index=%d"
                        "|pattern=%s"
                        "|name=%s"
                        "|type=%s"
                        "|value=%s", i, lPattern.c_str(), lName.c_str(), lType.c_str(), lValue.c_str());

            if((lType == "b") || (lType == "bool")) {
                lStatement->setBoolean(j++, lValue.toBool());
            }
            else if((lType == "i") || (lType == "int")) {
                lStatement->setInt(j++, lValue.toInt());
            }
            else if((lType == "ii") || (lType == "bigint")) {
                lStatement->setBigInt(j++, lValue.c_str());
            }
            else if((lType == "d") || (lType == "double")) {
                lStatement->setDouble(j++, lValue.toDouble());
            }
            else if((lType == "s") || (lType == "string")) {
                lStatement->setString(j++, lValue.c_str());
            }
            else if((lType == "bb") && (lType == "blob")) {
                std::string lData(lValue.c_str(), lValue.size());
                std::istringstream lBlob(lData);
                lStatement->setBlob(j++, &lBlob);
            }
            else if((lType == "dt") && (lType == "datetime")) {
                lStatement->setDateTime(j++, lValue.c_str());
            }
            else {
                slog(eGERR, "Le type de paramètre est inconnu."
                            "|name=%s"
                            "|type=%s"
                            "|sql=%s", lName.c_str(), lType.c_str(), _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }
        }

        lResultSet.reset(lStatement->executeQuery());
    }
    catch (sql::SQLException &e) {
        slog(eGERR, "L'exécution de la requête a échoué."
                "|error_code=%d"
                "|error_state=%s"
                "|error_msg=%s"
                "|sql=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what(), _sql.c_str());
        m_logs.addProblem();
        m_errorCode = e.getErrorCode();
        return lDataMap;
    }

    int lColumns = getColumnCount(lResultSet);
    while(lResultSet->next()) {
        GMySQLRow lDataRow;
        for(int i = 1; i <= lColumns; i++) {
            GString lData = lResultSet->getString(i).c_str();
            lDataRow.push_back(lData);
        }
        lDataMap.push_back(lDataRow);
    }
    return lDataMap;
}
//===============================================
