//===============================================
#include "GCarpoolCB.h"
#include "GCarpoolTest.h"
#include "GCarpoolRun.h"
//===============================================
GCarpoolCB::GCarpoolCB()
: GCallbackXml() {

}
//===============================================
GCarpoolCB::~GCarpoolCB() {

}
//===============================================
void GCarpoolCB::run() {
    if(m_uri == "/callback/carpool/test") {
        runTest();
    }
    else if(m_uri == "/callback/carpool") {
        runCarpool();
    }
    else {
        slog(eGERR, "Le callback n'est pas géré."
                    "|uri=%s"
                    "|contentTypeRequest=%s"
                    "|request=%s", m_uri.c_str(), m_contentTypeReq.c_str(), m_request.c_str());
        createUnknown();
    }
}
//===============================================
void GCarpoolCB::runTest() {
    GCarpoolTest lObj;
    lObj.setCommon(*this);
    lObj.setPage(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponse(lObj);
}
//===============================================
void GCarpoolCB::runCarpool() {
    GCarpoolRun lObj;
    lObj.setCommon(*this);
    lObj.setPage(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponse(lObj);
}
//===============================================
