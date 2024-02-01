//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GInclude.h"
#include "GString.h"
#include "GLog.h"
#include "GCode.h"
#include "GDebug.h"
#include "GException.h"
//===============================================
#define GOBJECT     GObject::Instance()
#define spath       GOBJECT->getPath
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();
    static GObject* Instance();
    virtual GObject* clone() const;
    virtual void clearMap();
    virtual const GLog& getLogs() const;
    virtual const GLog& getDataLogs() const;
    virtual GString getEnv(const GString& _env) const;
    bool isTestEnv() const;
    void print() const;
    virtual GString serialize(const GString& _code = "object") const;
    virtual void deserialize(const GString& _data, const GString& _code = "object");

private:
    static GObject* m_instance;

protected:
    GLog m_logs;
    GLog m_dataLogs;
    GCode m_resp;
    std::vector<GObject*> m_map;
};
//===============================================
#endif
//===============================================
