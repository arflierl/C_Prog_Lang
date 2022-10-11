#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void swap(int *pa, int *pb);
int strlengtg(char *s);

void main() {
  int x = 1, y = 2;
  int *ip;  //ip is a pointer to int
  ip = &x;  //ip now points to x
  y = *ip;  //y is now 1
  *ip = 0;  //x is now 0

  
  int a = 40, b = 30, *pa, *pb;
  pa = &a;
  pb = &b;
  printf("a: %d, b: %d \n", *pa, *pb);
  
  void swap(int *pa, int *pb) {
    int temp;

    temp = *pa;
    *pa = *pb;
    *pb = temp;
  }
  
  swap(pa, pb);
  
  printf("a: %d, b: %d \n", *pa, *pb);

  
  int arr[10] = {33, 22, 11, 1, 44, 55, 66, 77, 88, 99};
  int *pElement;

  pElement = &arr[0]; //pElement + 1 = &arr[1] ---> pElement + i  ---> also - 1/i
  
  for (int i = 0; i < 10; i++) { //iterate through the array using a pointer
    printf("%d\n", *(pElement+i)); //doesn't work if not in parenthesis
  }
  printf("%d\n", *(pElement+9));//access any desired element this way
  
  int strlength(char *s)
  {
    int n;
    char *string = s;
    for (n = 0; *s != '\0'; s++) {
      n++;
    }
    printf("String length of %s: %d\n", string , n);
  }
  
  strlength("hello");
  
  int *tail = (&arr[1]);
  
  for (int i = 0; i < 9; i++) {
    printf("tail of arr: %d\n", *(tail+i));
  }
  
  
}
