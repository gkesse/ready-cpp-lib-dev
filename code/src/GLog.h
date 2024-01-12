//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GInclude.h"
#include "GString.h"
//===============================================
class GLog {
public:
    GLog();
    ~GLog();
    GString serialize(const GString& _code = "logs");
    void deserialize(const GString& _data, const GString& _code = "logs");
    GLog* clone();
    void clearMap();
    void setLog(const GLog& _log);
    void addError(const GString& _msg);
    void addTechError(const GString& _msg);
    void addLog(const GString& _msg);
    void addData(const GString& _msg);
    void addLogs(const GLog& _obj);
    void showErrors();
    bool hasErrors() const;
    bool hasTechErrors() const;
    int size() const;
    bool isEmpty() const;
    GString toJson();

private:
    GString m_type;
    GString m_side;
    GString m_msg;
    std::vector<GLog*> m_map;
};
//===============================================
#endif
//===============================================
