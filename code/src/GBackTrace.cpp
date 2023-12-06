//===============================================
#include "GBackTrace.h"
//===============================================
GBackTrace::GBackTrace() {

}
//===============================================
GBackTrace::~GBackTrace() {

}
//===============================================
void GBackTrace::log_stack() {
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
                "\t% 2d: %s %s\n",++f,strings[i],buf);
        else
            size += snprintf(ptr,MAX_LOG_SIZE-size,
                "\t% 2d: %s\n",++f,strings[i]);
    }
    fprintf(stderr, "%s", logbuf);
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
