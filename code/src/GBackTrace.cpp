//===============================================
#include "GBackTrace.h"
//===============================================
#define DEFINE_SIGNAL(x, y) {x, #x, y}
#define DEFINE_SIGNAL_LAST {-1, "Unknown", "Inconnu"}
//===============================================
sGBackTraceSignal SIGNAL_MAP[] = {
    DEFINE_SIGNAL(SIGABRT, "Arrêt anormal du programme."),
    DEFINE_SIGNAL(SIGFPE,  "Opération arithmétique erronée."),
    DEFINE_SIGNAL(SIGINT,  "Réception d'un signal d'attention interactif."),
    DEFINE_SIGNAL(SIGTERM, "Une demande de résiliation envoyée au programme."),
    DEFINE_SIGNAL_LAST
};
//===============================================
GBackTrace::GBackTrace()
: GObject() {

}
//===============================================
GBackTrace::~GBackTrace() {

}
//===============================================
void GBackTrace::init() {
    // Arrêt anormal du programme, tel qu'un appel à l'abandon.
    signal(SIGABRT, onSignal);
    // Opération arithmétique erronée, telle qu'une division par zéro
    // ou une opération entraînant un débordement.
    signal(SIGFPE, onSignal);
    // Réception d'un signal d'attention interactif.
    signal(SIGINT, onSignal);
    // Une demande de résiliation envoyée au programme.
    signal(SIGTERM, onSignal);
}
//===============================================
size_t GBackTrace::convertToVMA(size_t addr) {
    Dl_info info;
    link_map* link_map;
    dladdr1((void*)addr,&info,(void**)&link_map, RTLD_DL_LINKMAP);
    return addr-link_map->l_addr;
}
//===============================================
sGBackTraceSignal GBackTrace::getSignal(int _signo) {
    int i = 0;
    while(1) {
        sGBackTraceSignal lSignal = SIGNAL_MAP[i++];
        if(lSignal.m_signo == _signo) return lSignal;
    }
    return DEFINE_SIGNAL_LAST;
}
//===============================================
void GBackTrace::print() {
    void* callstack[64];
    std::string buffer;

    int frame_count = backtrace(callstack, sizeof(callstack)/sizeof(callstack[0]));

    for (int i = 0; i < frame_count - 3; i++) {
        char location[1024];
        Dl_info info;

        if(dladdr(callstack[i],&info)) {
            size_t VMA_addr = convertToVMA((size_t)callstack[i]);
            VMA_addr -= 1;

            char command[256] = {0};
            snprintf(command, sizeof(command),"addr2line -fCapse %s %zx", info.dli_fname, VMA_addr);

            FILE* pipe = popen(command, "r");
            if(!pipe) return;

            char output[256];
            int bytes = fread(output, 1, sizeof(output) - 1, pipe);
            pclose(pipe);
            output[bytes] = '\0';

            char line[266];
            snprintf(line, sizeof(line), "#%2d: %s", i, output);

            buffer += line;
        }
    }

    fprintf(stderr, "%s\n", buffer.c_str());
}
//===============================================
void GBackTrace::runSignal(int _signo) {
    sGBackTraceSignal lSignal = getSignal(_signo);

    slog(eGWAR, "Le programme a été interrompu par le signal."
                "|signo=%d"
                "|signal=%s"
                "|description=%s", _signo, lSignal.m_name, lSignal.m_desc);

    print();
    exit(0);
}
//===============================================
void GBackTrace::onSignal(int _signo) {
    GBackTrace lBackTrace;
    lBackTrace.runSignal(_signo);
}
//===============================================
