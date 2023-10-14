#include <stdio.h>
#include <time.h>

typedef struct {
    void *func_address;
    double entry_time;
} FuncProfile;

#define MAX_FUNCTIONS 1000
FuncProfile profiles[MAX_FUNCTIONS];
int profile_count = 0;

void __cyg_profile_func_enter(void *func, void *caller) {
    double current_time = (double)clock() / CLOCKS_PER_SEC;

    for (int i = 0; i < profile_count; i++) {
        if (profiles[i].func_address == func) {
            profiles[i].entry_time = current_time;
            return;
        }
    }

    if (profile_count < MAX_FUNCTIONS) {
        profiles[profile_count].func_address = func;
        profiles[profile_count].entry_time = current_time;
        profile_count++;
    }
}

void __cyg_profile_func_exit(void *func, void *caller) {
    double current_time = (double)clock() / CLOCKS_PER_SEC;

    for (int i = 0; i < profile_count; i++) {
        if (profiles[i].func_address == func) {
            double duration = current_time - profiles[i].entry_time;
            printf("Function at %p took %f seconds\n", func, duration);
            fflush(stdout);  // Flush the output buffer immediately
            return;
        }
    }
    fflush(stdout);  // Ensure the buffer is flushed
}
