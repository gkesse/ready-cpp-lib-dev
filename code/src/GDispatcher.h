//===============================================
#ifndef _GDispatcher_
#define _GDispatcher_
//===============================================
#include "GRequest.h"
#include "GResponse.h"
//===============================================
class GDispatcher : public GRequest {
public:
    GDispatcher();
    ~GDispatcher();
    const GResponse& getResp() const;
    void run();
    void runGet();

protected:
    GResponse m_response;
};
//===============================================
#endif
//===============================================
