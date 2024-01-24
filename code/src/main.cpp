//===============================================
#include "GProcess.h"
#include "GBackTrace.h"
//===============================================
int main(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);
    GBACKTRACE->init();
    GProcess* lProcess = GPROCESS;
    lProcess->init();
    lProcess->run(_argc, _argv);
    lProcess->getLogs().showErrors();
    lProcess->clean();
    return 0;
}
//===============================================
