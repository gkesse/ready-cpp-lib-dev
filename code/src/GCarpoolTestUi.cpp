//===============================================
#include "GCarpoolTestUi.h"
//===============================================
GCarpoolTestUi::GCarpoolTestUi()
: GManager() {

}
//===============================================
GCarpoolTestUi::~GCarpoolTestUi() {

}
//===============================================
void GCarpoolTestUi::run() {
    deserialize(m_request);

    if(m_method == "hello_world") {
        runHelloWorld();
    }
    else {
        slog(eGERR, "La méthode est inconnue."
                    "|module=%s"
                    "|method=%s", m_module.c_str(), m_method.c_str());
    }
    createResponse();
}
//===============================================
void GCarpoolTestUi::runHelloWorld() {
    slog(eGINF, "Exécution de la méthode hello world.");
    m_logs.addSuccess();
}
//===============================================
