//===============================================
#include "GProcess.h"
#include "GBackTrace.h"
void toto();
void tata();
void titi();
//===============================================
void toto() {
    tata();
}
//===============================================
void tata() {
    titi();
}
//===============================================
void titi() {
    //GBackTrace::printStackTrace();
    //GBackTrace::printLogStack();
    //GBackTrace::printCallStack();
    GBackTrace::printBackStack();
}
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
