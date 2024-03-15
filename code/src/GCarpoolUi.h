//===============================================
#ifndef _GCarpoolUi_
#define _GCarpoolUi_
//===============================================
#include "GPage.h"
//===============================================
class GCarpoolUi : public GPage {
public:
    GCarpoolUi();
    ~GCarpoolUi();
    void init();
    void run();
    bool isRedirectUrl();
    void redirectUrl(const GString& _url);
    void createPage();
    void createHome();
    void createLog();
    void createTest();
    void createTestJs();
    void createTestGet();
    bool redirectTestPost();
    void createTestPost();
    void createTestServer();
    void createProfil();
    void createConnexion();
    void createInscription();
    void createInscriptionEmail();
    void createUnknown();
};
//===============================================
#endif
//===============================================
