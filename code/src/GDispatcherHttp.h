//===============================================
#ifndef _GDispatcherHttp_
#define _GDispatcherHttp_
//===============================================
#include "GDispatcher.h"
//===============================================
class GDispatcherHttp : public GDispatcher {
public:
    GDispatcherHttp();
    ~GDispatcherHttp();
    void setDispatcher(const GDispatcher& _dispatcher);
    const GString& getMethod() const;
    const GString& getUri() const;
    const GString& getVersion() const;
    const GMap& getForms() const;

protected:
    GString m_method;
    GString m_uri;
    GString m_version;
    GMap m_forms;
};
//===============================================
#endif
//===============================================
