//===============================================
#include "GProcess.h"
//===============================================
int main(int _argc, char** _argv) {
    printf("%s...\n", __PRETTY_FUNCTION__);
    GProcess lProcess;
    lProcess.init();
    lProcess.run(_argc, _argv);
    lProcess.getLogs().showErrors();
    lProcess.clean();
    return 0;
}
//===============================================
