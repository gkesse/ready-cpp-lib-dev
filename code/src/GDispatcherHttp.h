//===============================================
#ifndef _GDispatcherHttp_
#define _GDispatcherHttp_
//===============================================
#include "GDispatcher.h"
//===============================================
class GDispatcherHttp : public GDispatcher {
public:
    typedef std::map<std::string, std::string> GForms;

public:
    GDispatcherHttp();
    ~GDispatcherHttp();
    void setDispatcher(const GDispatcher& _dispatcher);
    const GString& getMethod() const;
    const GString& getUri() const;
    const GString& getVersion() const;
    GForms& getForms();
    const GForms& getForms() const;

protected:
    GString m_method;
    GString m_uri;
    GString m_version;
    GForms m_forms;
};
//===============================================
#endif
//===============================================
