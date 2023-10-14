#include <stdio.h>
#include <unistd.h>

void sleepy_function(int seconds);
void another_sleepy_function(int seconds);

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
