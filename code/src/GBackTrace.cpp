//===============================================
#include "GBackTrace.h"
//===============================================
GBackTrace* GBackTrace::m_instance = 0;
//===============================================
GBackTrace::GBackTrace() {

}
//===============================================
GBackTrace::~GBackTrace() {

}
//===============================================
GBackTrace* GBackTrace::Instance() {
    if(m_instance == 0) {
        m_instance = new GBackTrace;
    }
    return m_instance;
}
//===============================================
void GBackTrace::printBackStack() {
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
size_t GBackTrace::convertToVMA(size_t addr) {
    Dl_info info;
    link_map* link_map;
    dladdr1((void*)addr,&info,(void**)&link_map, RTLD_DL_LINKMAP);
    return addr-link_map->l_addr;
}
//===============================================
