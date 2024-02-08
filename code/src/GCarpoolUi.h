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
    void createHome();
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
