//===============================================
#include "GMySQL.h"
#include "GCode.h"
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
GString GMySQL::convertZeroToNull(int _data) {
    if(_data == 0) return "null";
    return _data;
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
        lStatement.reset(lConn->prepareStatement(_sql.c_str()));

        va_list lArgs;
        va_start(lArgs, _sql);
        int i = 0;
        int j = 1;
        for(; i < MYSQL_PREPA_VARS_MAX; i++) {
            int lType = (int)va_arg(lArgs, int);
            if(lType == MYSQL_TYPE_END) {
                break;
            }
            else if(lType == MYSQL_TYPE_INT) {
                int lValue = (int)va_arg(lArgs, int);
                lStatement->setInt(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_FLOAT) {
                double lValue = (double)va_arg(lArgs, double);
                lStatement->setDouble(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_STRING) {
                const char* lValue = (const char*)va_arg(lArgs, const char*);
                lStatement->setString(j++, lValue);
            }
            else {
                slog(eGERR, "Le type de la variable est inconnu."
                            "|type=%d"
                            "|sql=%s", lType, _sql.c_str());
                m_logs.addProblem();
                return false;
            }
        }
        va_end(lArgs);

        if(i == MYSQL_PREPA_VARS_MAX) {
            slog(eGERR, "Le nombre maximal de variables est atteint."
                        "|max=%d"
                        "|sql=%s", i, _sql.c_str());
            m_logs.addProblem();
            return false;
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
            m_logs.addError("La donnée existe déjà.");
        }
        else {
            slog(eGERR, "L'exécution de la requête a échoué."
                    "|error_code=%d"
                    "|error_state=%s"
                    "|error_msg=%s"
                    "|sql=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what(), _sql.c_str());
            m_logs.addProblem();
        }
        m_errorCode = e.getErrorCode();
        return false;
    }
    return true;
}
//===============================================
bool GMySQL::insertQuery(const GString& _sql, ...) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::PreparedStatement> lStatement;
    std::shared_ptr<sql::ResultSet> lResultSet;

    try {
        if(!openDatabase(lConn)) {
            slog(eGERR, "L'ouverture de la base donnée a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return false;
        }
        lStatement.reset(lConn->prepareStatement(_sql.c_str()));

        va_list lArgs;
        va_start(lArgs, _sql);
        int i = 0;
        int j = 1;
        for(; i < MYSQL_PREPA_VARS_MAX; i++) {
            int lType = (int)va_arg(lArgs, int);
            if(lType == MYSQL_TYPE_END) {
                break;
            }
            else if(lType == MYSQL_TYPE_INT) {
                int lValue = (int)va_arg(lArgs, int);
                lStatement->setInt(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_FLOAT) {
                double lValue = (double)va_arg(lArgs, double);
                lStatement->setDouble(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_STRING) {
                const char* lValue = (const char*)va_arg(lArgs, const char*);
                lStatement->setString(j++, lValue);
            }
            else {
                slog(eGERR, "Le type de la variable est inconnu."
                            "|type=%d"
                            "|sql=%s", lType, _sql.c_str());
                m_logs.addProblem();
                return false;
            }
        }
        va_end(lArgs);

        if(i == MYSQL_PREPA_VARS_MAX) {
            slog(eGERR, "Le nombre maximal de variables est atteint."
                        "|max=%d"
                        "|sql=%s", i, _sql.c_str());
            m_logs.addProblem();
            return false;
        }

        lStatement->execute();

        lResultSet.reset(lStatement->executeQuery("select @@identity as id"));
        lResultSet->next();
        m_id = (int)lResultSet->getInt64("id");
    }
    catch (sql::SQLException& e) {
        if(e.getErrorCode() == MYSQL_ERROR_DUPLICATION) {
            slog(eGWAR, "La donnée existe déjà."
                        "|error_code=%d"
                        "|error_state=%s"
                        "|error_msg=%s"
                        "|sql=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what(), _sql.c_str());
            m_logs.addInfo("La donnée existe déjà.");
        }
        else {
            slog(eGERR, "L'exécution de la requête a échoué."
                    "|error_code=%d"
                    "|error_state=%s"
                    "|error_msg=%s"
                    "|sql=%s", e.getErrorCode(), e.getSQLStateCStr(), e.what(), _sql.c_str());
            m_logs.addProblem();
        }
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
            slog(eGERR, "L'ouverture de la base donnée a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return lData;
        }
        lStatement.reset(lConn->prepareStatement(_sql.c_str()));

        va_list lArgs;
        va_start(lArgs, _sql);
        int i = 0;
        int j = 1;
        for(; i < MYSQL_PREPA_VARS_MAX; i++) {
            int lType = (int)va_arg(lArgs, int);
            if(lType == MYSQL_TYPE_END) {
                break;
            }
            else if(lType == MYSQL_TYPE_INT) {
                int lValue = (int)va_arg(lArgs, int);
                lStatement->setInt(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_FLOAT) {
                double lValue = (double)va_arg(lArgs, double);
                lStatement->setDouble(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_STRING) {
                const char* lValue = (const char*)va_arg(lArgs, const char*);
                lStatement->setString(j++, lValue);
            }
            else {
                slog(eGERR, "Le type de la variable est inconnu."
                            "|type=%d"
                            "|sql=%s", lType, _sql.c_str());
                m_logs.addProblem();
                return lData;
            }
        }
        va_end(lArgs);

        if(i == MYSQL_PREPA_VARS_MAX) {
            slog(eGERR, "Le nombre maximal de variables est atteint."
                        "|max=%d"
                        "|sql=%s", i, _sql.c_str());
            m_logs.addProblem();
            return lData;
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
GString GMySQL::readData2(const GString& _sql, ...) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::PreparedStatement> lStatement;
    std::shared_ptr<sql::ResultSet> lResultSet;
    GString lData;

    try {
        if(!openDatabase(lConn)) {
            slog(eGERR, "L'ouverture de la base donnée a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return lData;
        }
        lStatement.reset(lConn->prepareStatement(_sql.c_str()));

        va_list lArgs;
        va_start(lArgs, _sql);
        int i = 0;
        int j = 1;
        for(; i < MYSQL_PREPA_VARS_MAX; i++) {
            int lType = (int)va_arg(lArgs, int);
            if(lType == MYSQL_TYPE_END) {
                break;
            }
            else if(lType == MYSQL_TYPE_INT) {
                int lValue = (int)va_arg(lArgs, int);
                lStatement->setInt(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_FLOAT) {
                double lValue = (double)va_arg(lArgs, double);
                lStatement->setDouble(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_STRING) {
                const char* lValue = (const char*)va_arg(lArgs, const char*);
                lStatement->setString(j++, lValue);
            }
            else {
                slog(eGERR, "Le type de la variable est inconnu."
                            "|type=%d"
                            "|sql=%s", lType, _sql.c_str());
                m_logs.addProblem();
                return lData;
            }
        }
        va_end(lArgs);

        if(i == MYSQL_PREPA_VARS_MAX) {
            slog(eGERR, "Le nombre maximal de variables est atteint."
                        "|max=%d"
                        "|sql=%s", i, _sql.c_str());
            m_logs.addProblem();
            return lData;
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
GMySQL::GRows GMySQL::readCol(const GString& _sql, ...) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::PreparedStatement> lStatement;
    std::shared_ptr<sql::ResultSet> lResultSet;
    GMySQL::GRows lDataMap;

    try {
        if(!openDatabase(lConn)) {
            slog(eGERR, "L'ouverture de la base donnée a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
        }
        lStatement.reset(lConn->prepareStatement(_sql.c_str()));

        va_list lArgs;
        va_start(lArgs, _sql);
        int i = 0;
        int j = 1;
        for(; i < MYSQL_PREPA_VARS_MAX; i++) {
            int lType = (int)va_arg(lArgs, int);
            if(lType == MYSQL_TYPE_END) {
                break;
            }
            else if(lType == MYSQL_TYPE_INT) {
                int lValue = (int)va_arg(lArgs, int);
                lStatement->setInt(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_FLOAT) {
                double lValue = (double)va_arg(lArgs, double);
                lStatement->setDouble(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_STRING) {
                const char* lValue = (const char*)va_arg(lArgs, const char*);
                lStatement->setString(j++, lValue);
            }
            else {
                slog(eGERR, "Le type de la variable est inconnu."
                            "|type=%d"
                            "|sql=%s", lType, _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }
        }
        va_end(lArgs);

        if(i == MYSQL_PREPA_VARS_MAX) {
            slog(eGERR, "Le nombre maximal de variables est atteint."
                        "|max=%d"
                        "|sql=%s", i, _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
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
GMySQL::GRows GMySQL::readRow(const GString& _sql, ...) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::PreparedStatement> lStatement;
    std::shared_ptr<sql::ResultSet> lResultSet;
    GMySQL::GRows lDataMap;

    try {
        if(!openDatabase(lConn)) {
            slog(eGERR, "L'ouverture de la base donnée a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
        }
        lStatement.reset(lConn->prepareStatement(_sql.c_str()));

        va_list lArgs;
        va_start(lArgs, _sql);
        int i = 0;
        int j = 1;
        for(; i < MYSQL_PREPA_VARS_MAX; i++) {
            int lType = (int)va_arg(lArgs, int);
            if(lType == MYSQL_TYPE_END) {
                break;
            }
            else if(lType == MYSQL_TYPE_INT) {
                int lValue = (int)va_arg(lArgs, int);
                lStatement->setInt(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_FLOAT) {
                double lValue = (double)va_arg(lArgs, double);
                lStatement->setDouble(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_STRING) {
                const char* lValue = (const char*)va_arg(lArgs, const char*);
                lStatement->setString(j++, lValue);
            }
            else {
                slog(eGERR, "Le type de la variable est inconnu."
                            "|type=%d"
                            "|sql=%s", lType, _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }
        }
        va_end(lArgs);

        if(i == MYSQL_PREPA_VARS_MAX) {
            slog(eGERR, "Le nombre maximal de variables est atteint."
                        "|max=%d"
                        "|sql=%s", i, _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
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
GMySQL::GMaps GMySQL::readMap(const GString& _sql, ...) {
    std::shared_ptr<sql::Connection> lConn;
    std::shared_ptr<sql::PreparedStatement> lStatement;
    std::shared_ptr<sql::ResultSet> lResultSet;
    GMySQL::GMaps lDataMap;

    try {
        if(!openDatabase(lConn)) {
            slog(eGERR, "L'ouverture de la base donnée a échoué."
                        "|sql=%s", _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
        }
        lStatement.reset(lConn->prepareStatement(_sql.c_str()));

        va_list lArgs;
        va_start(lArgs, _sql);
        int i = 0;
        int j = 1;
        for(; i < MYSQL_PREPA_VARS_MAX; i++) {
            int lType = (int)va_arg(lArgs, int);
            if(lType == MYSQL_TYPE_END) {
                break;
            }
            else if(lType == MYSQL_TYPE_INT) {
                int lValue = (int)va_arg(lArgs, int);
                lStatement->setInt(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_FLOAT) {
                double lValue = (double)va_arg(lArgs, double);
                lStatement->setDouble(j++, lValue);
            }
            else if(lType == MYSQL_TYPE_STRING) {
                const char* lValue = (const char*)va_arg(lArgs, const char*);
                lStatement->setString(j++, lValue);
            }
            else {
                slog(eGERR, "Le type de la variable est inconnu."
                            "|type=%d"
                            "|sql=%s", lType, _sql.c_str());
                m_logs.addProblem();
                return lDataMap;
            }
        }
        va_end(lArgs);

        if(i == MYSQL_PREPA_VARS_MAX) {
            slog(eGERR, "Le nombre maximal de variables est atteint."
                        "|max=%d"
                        "|sql=%s", i, _sql.c_str());
            m_logs.addProblem();
            return lDataMap;
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
        GMySQL::GRows lDataRow;
        for(int i = 1; i <= lColumns; i++) {
            GString lData = lResultSet->getString(i).c_str();
            lDataRow.push_back(lData);
        }
        lDataMap.push_back(lDataRow);
    }
    return lDataMap;
}
//===============================================
