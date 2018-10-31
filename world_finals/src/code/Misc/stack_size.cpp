#include <sys/resource.h>
void remove_stack_size_limit() {
  struct rlimit rl;
  getrlimit(RLIMIT_STACK, &rl);
  rl.rlim_cur = RLIM_INFINITY;
  setrlimit(RLIMIT_STACK, &rl);
}
