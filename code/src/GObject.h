//===============================================
#ifndef _GObject_
#define _GObject_
//===============================================
#include "GLog.h"
#include "GDebug.h"
#include "GException.h"
//===============================================
#define GOBJECT     GObject::Instance()
#define spath       GOBJECT->getPath
//===============================================
class GSocket;
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();
    static GObject* Instance();
    virtual GObject* clone() const;
    virtual void clearMap();
    virtual void init();
    virtual void setObject(const GObject& _obj);
    virtual void setSocket(const GSocket& _socket);
    virtual const GLog& getLogs() const;
    virtual GString getEnv(const GString& _env) const;
    virtual GString getPath(const GString& _path) const;
    virtual void print() const;
    virtual GString serialize(const GString& _code = "object") const;
    virtual void deserialize(const GString& _data, const GString& _code = "object");

private:
    static GObject* m_instance;
    GString m_dataPath;

protected:
    GLog m_logs;
    std::vector<GObject*> m_map;

    GString m_addressIP;
    int m_port;
    pid_t m_pid;
};
//===============================================
#endif
//===============================================
