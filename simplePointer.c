#include <stdio.h>

int main() {
  char *msg = "hello";

  for (int i = 0; i < 5; i++) {
    void *ptr = msg;
    printf("%c", *(char *)(ptr + i));
  }

  printf("\n");
}
