#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void parse(char *str);
void printString(char *str);

void main(int argc, char *argv[]) {
  char a = *argv[1]; //pointer to the first character of argv[1]
  int b = *argv[1];  // pointer to the first chracter of argv[1], integer char value
  char *hello = argv[1]; 
  printf("%c\n", a);
  printf("%d\n", b);
  printf("%d\n", 'h');
  printf("%s\n",  hello);
  printString(argv[1]);

//this is how you can access the entire array of chars of argv[1], the "string"
  for (int i = 0; hello[i] != '\0'; i++) {
    printf("%c\n", hello[i]);
  }
  parse(argv[1]);
  char num[] = "1234";
  printf("%d\n", atoi(num) - 1);
}

void printString(char *str) {
  printf("%s\n", str);  // this function(char *str) --> char *str is from argv[i] in main from command line and is the array of chars, or "string".  See *hello in mian.
}  

void parse(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    printf("%c\n", str[i]);
  }
  for (int j = 0; str[j] != '\0'; j++) {
    printf("%d\n", str[j]);
  }  
}  


