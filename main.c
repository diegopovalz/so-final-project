#include <stdio.h>
#include <unistd.h>  // Include for sleep()

#define DUMP(func, call) \
  printf("%s: func = %p, called by = %p\n", __FUNCTION__, func, call)

void __attribute__((no_instrument_function))
__cyg_profile_func_enter(void *this_func, void *call_site)
{
  DUMP(this_func, call_site);
}

void __attribute__((no_instrument_function))
__cyg_profile_func_exit(void *this_func, void *call_site)
{
  DUMP(this_func, call_site);
}

void sleepy_function(int seconds)
{
  printf("Sleeping for %d seconds...\n", seconds);
  sleep(seconds);
}

void another_sleepy_function(int seconds)
{
  printf("Sleeping for %d seconds...\n", seconds);
  sleep(seconds);
}

int main(void)
{
  printf("In function: %s\n", __FUNCTION__);

  sleepy_function(2);
  another_sleepy_function(3);

  return 0;
}
