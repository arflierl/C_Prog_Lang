#include <stdio.h>
#include <stdlib.h>

int main() {
  void *buffer = malloc(3000);//the memory I am going to fill
  
  short arr[3] = {4, 10, 7};
  char *words[7];//could also initialize like arr
  words[0] = "first";
  words[1] = "second";
  words[2] = "baseball";
  words[3] = "Buffalo, NY";
  words[4] = "Texas Rangers";
  words[5] = "Buffalo Bills";
  words[6] = "Buffalo Sabres";


  
  void *checker = buffer;//points to the "output" I will use to check validity of data entered later

  
  for (int i = 0; i < 7; i++) {//for each index in this array
    void *get = words[i];//void pointer, the "reader"
    while (*(char *)get != '\0') {
      printf("%c", *(char *)get);
      *(char *)buffer = *(char *)get;//add these chars to the buffer
      buffer++;//move the buffer by one byte
      get++;//move the "reader" by one byte
    }
    *(char *)buffer = '\0'; //add a NULL char to end of each input string
    buffer++;//move the buffer by one byte
    printf("\n");//print a new line after each individual string, indicated by '\0'
  }
  
  printf("\n");
  
  for (int j = 0; j < 3; j++) {//for each index in the array of short integers
    printf("%d ", arr[j]);
    *(short *)buffer = arr[j];//add this short to the buffer
    buffer += sizeof(short);//move the buffer by sizeof(short) bytes (2 for x86-64)
  }


  
  printf("\n");
  printf("\n");


  
  buffer -= 6;//move the buffer backwards by magic number of 3 shorts (use arraylength*sizeof(short))
  for (int b = 0; b < 3; b++) {
    //since we know how many short integers there are use short*b
    printf("%d ", *(short *)(buffer + (sizeof(short)*b)));
  }
  printf("\n");
  printf("\n");

  
  for (int u = 0; u < 77; u++) {//there are 77 chars counting '\0' chars for end of strings
    if (*(char *)checker != '\0') {    
      printf("%c", *(char *)checker);//dereferenced pointer of type char * at address pointed to by checker
    }else {
      printf("\n");//new line after each string
    }
    checker++;//advance checker by one byte (sizeof(char))
    
  }
  
}
