#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

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
    return mem_usage;
}

void foo() {
    sleep(1);
}

void bar() {
    sleep(2);
}

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        foo();
        bar();
        exit(0);
    } else if (pid > 0) {
        while (1) {
            int status;
            if (waitpid(pid, &status, WNOHANG) != 0) {
                break;
            }

            long mem_usage = get_memory_usage(pid);
            if (mem_usage >= 0) {
                printf("Memory usage: %ld kB\n", mem_usage);
            }

            sleep(1);
        }
    } else {
        perror("fork failed");
        return 1;
    }

    return 0;
}
