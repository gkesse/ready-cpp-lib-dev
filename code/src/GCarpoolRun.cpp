//===============================================
#include "GCarpoolRun.h"
#include "GCarpoolEmail.h"
//===============================================
GCarpoolRun::GCarpoolRun()
: GManager() {

}
//===============================================
GCarpoolRun::~GCarpoolRun() {

}
//===============================================
void GCarpoolRun::run() {
    deserialize(m_request);

    if(m_module == "email") {
        runEmail();
    }
    else {
        slog(eGERR, "Le module est inconnu."
                    "|module=%s", m_module.c_str());
        createUnknown();
    }
    createResponse();
}
//===============================================
void GCarpoolRun::runEmail() {
    GCarpoolEmail lObj;
    lObj.setCommon(*this);
    lObj.setManager(*this);
    lObj.run();
    m_response += lObj.toResponse();
}
//===============================================
