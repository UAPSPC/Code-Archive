/* Sometimes you want to recurse very deeply or
   allocate massive arrays on the stack. This code removes the limit
   on maximum stack size so that you can.
   Disclaimer:  This is usually not a good idea. You can solve any
   problem without increasing the max stack size. However, doing so
   can save you some time in a few cases. */
#include <sys/resource.h>
void remove_stack_limit() {
  struct rlimit rl;
  getrlimit(RLIMIT_STACK, &rl);
  rl.rlim_cur = RLIM_INFINITY;
  setrlimit(RLIMIT_STACK, &rl);
}
