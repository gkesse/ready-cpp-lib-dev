//===============================================
#include "GCarpoolTest.h"
#include "GCarpoolTestUi.h"
#include "GCarpoolEmail.h"
//===============================================
GCarpoolTest::GCarpoolTest()
: GManager() {

}
//===============================================
GCarpoolTest::~GCarpoolTest() {

}
//===============================================
void GCarpoolTest::run() {
    deserialize(m_request);

    if(m_module == "test") {
        runTest();
    }
    else if(m_module == "email") {
        runEmail();
    }
    else {
        slog(eGERR, "Le module est inconnu."
                    "|module=%s", m_module.c_str());
        createUnknown();
    }
}
//===============================================
void GCarpoolTest::runTest() {
    GCarpoolTestUi lObj;
    lObj.setCommon(*this);
    lObj.setManager(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponse(lObj);
}
//===============================================
void GCarpoolTest::runEmail() {
    GCarpoolEmail lObj;
    lObj.setCommon(*this);
    lObj.setManager(*this);
    lObj.run();
    m_logs.addLogs(lObj.getLogs());
    setResponse(lObj);
}
//===============================================
