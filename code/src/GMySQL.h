//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GObject.h"
//===============================================
#define GMYSQL      GMySQL::Instance()
#define czton       GMYSQL->convertZeroToNull
#define cbtoc       GMYSQL->convertBooleanToChar
#define suuid       GMYSQL->getUUID
//===============================================
typedef std::vector<GString>    GMySQLRow;
typedef std::vector<GMySQLRow>  GMySQLMap;
//===============================================
class GMySQL : public GObject {
public:
    GMySQL();
    GMySQL(const GString& _database);
    ~GMySQL();
    static GMySQL* Instance();
    int getId() const;
    int getErrorCode() const;
    GString convertZeroToNull(int _data) const;
    GString convertBooleanToChar(bool _data) const;
    GString getUUID() const;
    int getColumnCount(std::shared_ptr<sql::ResultSet>& _resultSet) const;
    bool openDatabase(std::shared_ptr<sql::Connection>& _conn);
    bool execQuery(const GString& _sql, ...);
    bool insertQuery(const GString& _sql, ...);
    GString readData(const GString& _sql, ...);
    GMySQLRow readCol(const GString& _sql, ...);
    GMySQLRow readRow(const GString& _sql, ...);
    GMySQLMap readMap(const GString& _sql, ...);

private:
    static GMySQL* m_instance;
    GString m_protocol;
    GString m_hostname;
    GString m_database;
    GString m_username;
    GString m_password;
    int m_port;
    int m_id;
    int m_errorCode;
};
//==============================================
#endif
//==============================================
