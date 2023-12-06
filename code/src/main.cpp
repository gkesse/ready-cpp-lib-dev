//===============================================
#include "GBackTrace.h"
//===============================================
#define MAX_STACK_FRAMES 64
static void *stack_traces[MAX_STACK_FRAMES];
static char const * icky_global_program_name;

void toto();
void tata();
void titi();
void posix_print_stack_trace();
int addr2line(char const * const program_name, void const * const addr);
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
    posix_print_stack_trace();
}
//===============================================
int main(int _argc, char** _argv) {
    icky_global_program_name = _argv[0];
    fprintf(stderr, "%s...\n", __PRETTY_FUNCTION__);
    toto();
    return 0;
}
//===============================================
void posix_print_stack_trace()
{
  int i, trace_size = 0;
  char **messages = (char **)NULL;

  trace_size = backtrace(stack_traces, MAX_STACK_FRAMES);
  messages = backtrace_symbols(stack_traces, trace_size);

  /* skip the first couple stack frames (as they are this function and
   our handler) and also skip the last frame as it's (always?) junk. */
  // for (i = 3; i < (trace_size - 1); ++i)
  for (i = 0; i < trace_size; ++i) // we'll use this for now so you can see what's going on
  {
    if (addr2line(icky_global_program_name, stack_traces[i]) != 0)
    {
      printf("  error determining line # for: %s\n", messages[i]);
    }

  }
  if (messages) { free(messages); }
}

int addr2line(char const * const program_name, void const * const addr)
{
  char addr2line_cmd[512] = {0};

  /* have addr2line map the address to the relent line in the code */
  #ifdef OSX
    /* apple does things differently... */
    sprintf(addr2line_cmd,"atos -o %.256s %p >> stacktrace.out 2>&1", program_name, addr);
  #else
    sprintf(addr2line_cmd,"addr2line -f -p -e \"%.256s\" %p >> stacktrace.out 2>&1", program_name, addr);
  #endif

  return system(addr2line_cmd);
}
