//===============================================
#include "GProcess.h"
#include "GTest.h"
#include "GSocket.h"
//===============================================
GProcess::GProcess()
: GObject() {

}
//===============================================
GProcess::~GProcess() {

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
    GProcess lProcess;
    lProcess.runExit();
}
//===============================================
void GProcess::runExit() {
    slog(eGEXT, "Fin du programme.");
}
//===============================================
void GProcess::run(int _argc, char** _argv) {
    GString lModule = "";
    if(_argc > 1) lModule = _argv[1];

    if(lModule == "") {
        slog(eGERR, "Le module est obligatoire.");
    }
    else if(lModule == "test") {
        runTest(_argc, _argv);
    }
    else if(lModule == "server") {
        runServer(_argc, _argv);
    }
    else {
        slog(eGERR, "Le module est inconnu."
                    "|module=%s", lModule.c_str());
    }
}
//===============================================
void GProcess::runTest(int _argc, char** _argv) {
    GTest lObj;
    lObj.run(_argc, _argv);
}
//===============================================
void GProcess::runServer(int _argc, char** _argv) {
    GSocket lObj;
    lObj.runServer();
}
//===============================================
