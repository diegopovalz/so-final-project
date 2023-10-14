#include <stdio.h>
#include <sys/time.h>

struct timeval start_time;

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1e6;
}

void __cyg_profile_func_enter(void *this_func, void *call_site) __attribute__((no_instrument_function));
void __cyg_profile_func_exit(void *this_func, void *call_site) __attribute__((no_instrument_function));

void __cyg_profile_func_enter(void *this_func, void *call_site)
{
    gettimeofday(&start_time, NULL);
}

void __cyg_profile_func_exit(void *this_func, void *call_site)
{
    double elapsed_time = get_time() - (start_time.tv_sec + start_time.tv_usec / 1e6);
    printf("%s: func = %p, called by = %p, time = %.2f seconds\n", __FUNCTION__, this_func, call_site, elapsed_time);
}
