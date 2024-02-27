//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GString.h"
//===============================================
class GLog {
public:
    GLog();
    ~GLog();
    GString serialize(const GString& _code = "logs") const;
    void deserialize(const GString& _data, const GString& _code = "logs");
    GLog* clone();
    void clearMap();
    void setObj(const GLog& _obj);
    void addProblem();
    void addSuccess();
    void addError(const GString& _msg);
    void addInfo(const GString& _msg);
    void addData(const GString& _msg);
    void addLogs(const GLog& _obj);
    void showLogs() const;
    bool hasErrors() const;
    int size() const;
    bool isEmpty() const;
    GString toJson() const;

private:
    GString m_type;
    GString m_side;
    GString m_msg;
    std::vector<GLog*> m_map;
};
//===============================================
#endif
//===============================================
