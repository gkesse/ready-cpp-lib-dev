//===============================================
#ifndef _GDispatcherGet_
#define _GDispatcherGet_
//===============================================
#include "GDispatcher.h"
//===============================================
class GDispatcherGet : public GDispatcher {
public:
    GDispatcherGet();
    ~GDispatcherGet();
    void setDispatcher(const GDispatcher& _dispatcher);
    void run();

private:
    GString m_method;
    GString m_uri;
    GString m_version;
};
//===============================================
#endif
//===============================================
