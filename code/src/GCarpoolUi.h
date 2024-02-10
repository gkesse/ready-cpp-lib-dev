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
    void create();
    bool isRedirectUrl();
    void redirectUrl(const GString& _url);
    void createHome();
    void createLog();
    void createTest();
    void createTestJs();
    void createProfil();
    void createConnexion();
    void createInscription();
    bool redirectInscriptionEmail();
    void createInscriptionEmail();

private:
    GString m_content;
};
//===============================================
#endif
//===============================================
