//===============================================
#include "GProcess.h"
#include "GBackTrace.h"
//===============================================
int main(int _argc, char** _argv) {
    GBackTrace lBackTrace;
    GProcess lProcess;
    GDebug slog;

    slog(eGMAN, "Démarrage du programme.");

    lBackTrace.init();
    lProcess.init();
    lProcess.run(_argc, _argv);
    lProcess.clean();

    return 0;
}
//===============================================
