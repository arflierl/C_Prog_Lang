#include <stdio.h>

int main() {
  
  char *string[4];
  int nstrings = 0;

  void setstring(char *str) {
    while (nstrings < 4) {
      printf("nstrings before: %d\n", nstrings);
      string[nstrings++] = "str";
      printf("nstrings after: %d\n", nstrings);
    }
  }

  setstring(*string);
  
  for (int i = 0; i < 4; i++) {
    printf("string[%d]: %s\n", i, string[i]);
  }
  
}
