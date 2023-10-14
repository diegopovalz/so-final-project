#include <stdio.h>
#include <unistd.h>
#include <time.h>

void foo() {
  sleep(1);
  for (int i = 0; i < 3; i++) {
    printf("%d\n", i);
  }
}

void bar() {
  sleep(2);
  for (int i = 0; i < 6; i++) {
    printf("%d\n", i);
  }
}

int main() {
  foo();
  bar();
  return 0;
}
