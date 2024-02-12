//===============================================
#ifndef _GCarpoolCB_
#define _GCarpoolCB_
//===============================================
#include "GPage.h"
//===============================================
class GCarpoolCB : public GPage {
public:
    GCarpoolCB();
    ~GCarpoolCB();
    void init();
    void create();
    bool isRedirectUrl();
    void redirectUrl(const GString& _url);
    void createHome();
    void createLog();
    void createTest();
    void createTestJs();
    void createTestGet();
    bool redirectTestPost();
    void createTestPost();
    void createProfil();
    void createConnexion();
    void createInscription();
    void createInscriptionEmail();

private:
    GString m_content;
};
//===============================================
#endif
//===============================================
