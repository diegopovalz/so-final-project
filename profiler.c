#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

// === Memory Usage Profiling ===

long get_memory_usage(pid_t pid) {
    char proc_path[256];
    snprintf(proc_path, sizeof(proc_path), "/proc/%d/status", pid);

    FILE *file = fopen(proc_path, "r");
    if (!file) {
        perror("Failed to open /proc file");
        return -1;
    }

    char line[256];
    long mem_usage = -1;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            sscanf(line, "VmRSS: %ld", &mem_usage);
            break;
        }
    }

    fclose(file);
    return mem_usage; // Returns memory usage in kB
}

// === Manual CPU Time Profiling ===

/* typedef struct {
    clock_t start;
} Timer;

void timer_start(Timer* timer) {
    timer->start = clock();
}

double timer_elapsed(Timer* timer) {
    return (double)(clock() - timer->start) / CLOCKS_PER_SEC;
} */

// === Test Functions ===

void foo() {
    // Timer t;
    // timer_start(&t);
    
    sleep(1);
    
    // printf("Function foo took %f seconds\n", timer_elapsed(&t));
}

void bar() {
    // Timer t;
    // timer_start(&t);
    
    sleep(2);
    
    // printf("Function bar took %f seconds\n", timer_elapsed(&t));
}

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        foo();
        bar();
        exit(0);
    } else if (pid > 0) {
        // Parent process
        while (1) {
            int status;
            if (waitpid(pid, &status, WNOHANG) != 0) {
                // Child process has terminated
                break;
            }

            long mem_usage = get_memory_usage(pid);
            if (mem_usage >= 0) {
                printf("Memory usage: %ld kB\n", mem_usage);
            }

            sleep(1); // Check every second
        }
    } else {
        perror("fork failed");
        return 1;
    }

    return 0;
}
