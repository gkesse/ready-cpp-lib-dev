//===============================================
#include "GProcess.h"
#include "GTest.h"
#include "GSocket.h"
//===============================================
GProcess* GProcess::m_instance = 0;
//===============================================
GProcess::GProcess()
: GObject() {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
GProcess* GProcess::Instance() {
    if(m_instance == 0) {
        m_instance = new GProcess;
    }
    return m_instance;
}
//===============================================
void GProcess::init() {
    // system
    atexit(onExit);
    // libxml2
    xmlInitParser();
    xmlKeepBlanksDefault(0);
}
//===============================================
void GProcess::clean() {
    // libxml2
    xmlCleanupParser();
    xmlMemoryDump();
}
//===============================================
void GProcess::onExit() {
    GPROCESS->runExit();
}
//===============================================
void GProcess::runExit() {
    slog(eGINF, "Fin du programme...");
}
//===============================================
void GProcess::run(int _argc, char** _argv) {
    GString lModule = "";
    if(_argc > 1) lModule = _argv[1];

    if(lModule == "") {
        slog(eGERR, "Erreur, on ne peut exécuter un process associé à aucun module.");
        m_logs.addError("Un problème a été rencontré.");
    }
    else if(lModule == "test") {
        runTest(_argc, _argv);
    }
    else if(lModule == "server") {
        runServer(_argc, _argv);
    }
    else {
        slog(eGERR, "Erreur, on ne peut exécuter un process associé à un module inconnu."
                    "|module=%s", lModule.c_str());
        m_logs.addError("Un problème a été rencontré.");
    }
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
    GTest lObj;
    lObj.run(_argc, _argv);
    m_logs.addLogs(lObj.getLogs());
}
//===============================================
void GProcess::runServer(int _argc, char** _argv) {
    GSocket lServer;
    lServer.runServer();
}
//===============================================
