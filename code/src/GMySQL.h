//===============================================
#ifndef _GMySQL_
#define _GMySQL_
//===============================================
#include "GObject.h"
//===============================================
#define GMYSQL      GMySQL::Instance()
#define czton       GMYSQL->convertZeroToNull
//===============================================
class GMySQL : public GObject {
public:
    typedef std::vector<GString> GRows;
    typedef std::vector<GRows> GMaps;

public:
    GMySQL();
    ~GMySQL();
    static GMySQL* Instance();
    int getId() const;
    int getErrorCode() const;
    GString convertZeroToNull(int _data);
    int getColumnCount(std::shared_ptr<sql::ResultSet>& _resultSet) const;
    bool openDatabase(std::shared_ptr<sql::Connection>& _conn);
    bool execQuery(const GString& _sql, ...);
    bool insertQuery(const GString& _sql, ...);
    GString readData(const GString& _sql, ...);
    GRows readCol(const GString& _sql, ...);
    GRows readRow(const GString& _sql, ...);
    GMaps readMap(const GString& _sql, ...);

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
