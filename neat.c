#include <stdio.h>

int *p1, *p2;
int swap_and_add(void *a, void *b);

int main() {
  int x = 2, y = 3;
  p1 = &x;
  p2 = &y;
  swap_and_add(p1, p2);
  printf("x: %d, y: %d\n", x, y);
}

int swap_and_add(void *a, void*b) {
  int x = *(int *)a;
  int y = *(int *)b;
  int sum = x + y;
  int temp;
  temp = *(int *)a;
  *(int *)a = *(int *)b;
  *(int *)b = temp;
  printf("sum: %d\n", sum);

  return sum;
}
  
  
