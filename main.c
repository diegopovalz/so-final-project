#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define DUMP(func, call, time) \
  printf("%s: func = %p, called by = %p, time = %.2f seconds\n", __FUNCTION__, func, call, (double)time)

clock_t start_time;

void __attribute__((no_instrument_function))
__cyg_profile_func_enter(void *this_func, void *call_site)
{
    start_time = clock();
    DUMP(this_func, call_site, 0);  // time is 0 at function entry
}

void __attribute__((no_instrument_function))
__cyg_profile_func_exit(void *this_func, void *call_site)
{
    double elapsed_time = ((double)(clock() - start_time)) / CLOCKS_PER_SEC;
    DUMP(this_func, call_site, elapsed_time);
}

void sleepy_function(int seconds)
{
    printf("\nInside %s()\n", __FUNCTION__);
    printf("Sleeping for %d seconds...\n", seconds);
    sleep(seconds);
}

void another_sleepy_function(int seconds)
{
    printf("\nInside %s()\n", __FUNCTION__);
    printf("Sleeping for %d seconds...\n", seconds);
    sleep(seconds);
}

int main(void)
{
    printf("\nInside %s()\n", __FUNCTION__);

    sleepy_function(2);
    another_sleepy_function(3);

    return 0;
}
