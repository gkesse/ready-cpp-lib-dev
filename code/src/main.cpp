//===============================================
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
    fprintf(stderr, "%s...\n", __PRETTY_FUNCTION__);
    toto();
    return 0;
}
//===============================================
