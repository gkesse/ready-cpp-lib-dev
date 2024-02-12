//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GCommon.h"
#include "GCode.h"
#include "GCode.h"
#include "GLog.h"
#include "GDebug.h"
#include "GException.h"
#include "GMap.h"
//===============================================
#define GOBJECT     GObject::Instance()
#define sres        GOBJECT->getResource
//===============================================
class GObject : public GCommon {
public:
    GObject();
    virtual ~GObject();
    static GObject* Instance();
    virtual GObject* clone() const;
    virtual void clearMap();
    virtual void init();
    virtual const GLog& getLogs() const;
    virtual GString getEnv(const GString& _env) const;
    virtual GString getResource(const GString& _path) const;
    virtual void print() const;
    virtual GString serialize(const GString& _code = "object") const;
    virtual void deserialize(const GString& _data, const GString& _code = "object");

private:
    static GObject* m_instance;
    GString m_webRoot;

protected:
    GLog m_logs;
    std::vector<GObject*> m_map;
};
//===============================================
#endif
//===============================================
