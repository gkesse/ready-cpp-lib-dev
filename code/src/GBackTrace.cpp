//===============================================
#include "GBackTrace.h"
//===============================================
#define MAX_LOG_SIZE 2048
//===============================================
#define MAX_STACK_FRAMES 64
static void *stack_traces[MAX_STACK_FRAMES];
//===============================================
GBackTrace::GBackTrace() {

}
//===============================================
GBackTrace::~GBackTrace() {

}
//===============================================
// backtrace : printLogStack
//===============================================
void GBackTrace::printLogStack() {
    void*                   bt[64];
    char**                  strings;
    size_t                  sz;
    int32_t                 i,f;
    int32_t                 size = 0;
    char                    logbuf[MAX_LOG_SIZE];
    char                    addr[32],buf[1024];
    char                   *ptr;
    sz      = backtrace(bt, 64);
    strings = backtrace_symbols(bt, sz);
    for(i = 0,f = 0; i < sz; ++i) {
        if(strstr(strings[i],"main+")) break;
        ptr  = logbuf + size;
        if(getaddr(strings[i],addr,32) && !addr2line(addr,buf,1024))
            size += snprintf(ptr,MAX_LOG_SIZE-size,
                    "%2d: %s %s\n",++f,strings[i],buf);
        else
            size += snprintf(ptr,MAX_LOG_SIZE-size,
                    "%2d: %s\n",++f,strings[i]);
    }
    fprintf(stderr, "%s\n", logbuf);
    free(strings);
}
//===============================================
int32_t GBackTrace::getaddr(char *in,char *out,size_t size) {
    int32_t b,i;
    for(i = b = 0;i < size - 1;in++) switch(*in) {
    case '[':{if(!b){b = 1; break;} else return 0;}
    case ']':{if(b){*out++ = 0;return 1;}return 0;}
    default:{if(b){*out++ = *in;++i;}break;}
    }
    return 0;
}
//===============================================
int32_t GBackTrace::addr2line(char *addr,char *output,int32_t size) {
    char path[256]={0};
    char cmd[1024]={0};
    FILE *pipe;
    int  i,j;
    if(0 >= readlink("/proc/self/exe", path, 256))
        return -1;
    snprintf(cmd,1024,"addr2line -fCse %s %s", path, addr);
    pipe = popen(cmd, "r");
    if(!pipe) return -1;
    i = fread(output,1,size-1,pipe);
    pclose(pipe);
    output[i] = '\0';
    for(j=0; j<=i; ++j) if(output[j] == '\n') output[j] = ' ';
    return 0;
}
//===============================================
// backtrace : printCallStack
//===============================================
size_t GBackTrace::convertToVMA(size_t addr) {
    Dl_info info;
    link_map* link_map;
    dladdr1((void*)addr,&info,(void**)&link_map,RTLD_DL_LINKMAP);
    return addr-link_map->l_addr;
}
//===============================================
void GBackTrace::printCallStack() {
    void* callstack[128];
    int frame_count = backtrace(callstack, sizeof(callstack)/sizeof(callstack[0]));
    for (int i = 0; i < frame_count - 3; i++) {
        char location[1024];
        Dl_info info;
        if(dladdr(callstack[i],&info)) {
            char command[256];
            size_t VMA_addr=convertToVMA((size_t)callstack[i]);
            VMA_addr-=1;
            snprintf(command,sizeof(command),"addr2line -e %s -fCi %zx",info.dli_fname,VMA_addr);
            system(command);
        }
    }
}
//===============================================
// backtrace : printBackStack
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
// backtrace : printStackTrace
//===============================================
void GBackTrace::printStackTrace() {
    int i, trace_size = 0;
    char **messages = (char **)NULL;
    char path[256]={0};

    if(0 >= readlink("/proc/self/exe", path, 256))
        return;

    trace_size = backtrace(stack_traces, MAX_STACK_FRAMES);
    messages = backtrace_symbols(stack_traces, trace_size);

    for (i = 0; i < trace_size; ++i) {
        if (addr2line(path, stack_traces[i]) != 0) {
            fprintf(stderr, "error determining line # for: %s\n", messages[i]);
        }
    }
    if (messages) { free(messages); }
}
//===============================================
int GBackTrace::addr2line(char const * const program_name, void const * const addr) {
    char addr2line_cmd[512] = {0};

#ifdef OSX
    sprintf(addr2line_cmd,"atos -o %.256s %p >> stacktrace.out 2>&1", program_name, addr);
#else
    sprintf(addr2line_cmd,"addr2line -f -p -e \"%.256s\" %p >> stacktrace.out 2>&1", program_name, addr);
#endif

    return system(addr2line_cmd);
}
//===============================================
