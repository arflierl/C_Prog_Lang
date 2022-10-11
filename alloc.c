#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

//int a; ----> static memory (fixed size)
//int arr[5] ----> static
//Struct payroll e[4] ----> also static

void main() {

  printf("P\n");
  float *P = (float*) malloc(3*sizeof(float));//should this be declared outside of main?

  *P = 2.3;
  *(P+1) = 3.4;
  *(P+2) = 4.1;
  for (int i = 0; i < 3; i++) {
    printf("%.2f\n", *(P+i));
  }

  printf("\n");

  
  //now using calloc
  printf("Q\n");
  float *Q = (float*) calloc(3, sizeof(float));
  printf("*Q memory address: %d\n", Q);//get warning
  Q[0] = 3.21;
  Q[1] = 2.12;
  Q[2] = 3.31;
  for (int i = 0; i < 3; i++) {
    printf("%.3f\n", Q[i]);
  }
  printf("\n");

  
  //use realloc to change memory block size of Q
  printf("M\n");
  float *M = (float*) realloc(Q, 6*sizeof(float));//NULL -> malloc
  printf("*M memory address: %d\n", M);//same as Q
  M[3] = 9.92;
  M[4] = 2.12;
  M[5] = 2.31;
  for (int i = 0; i < 6; i++) {
    printf("%.3f\n", M[i]);
  }
  
  free(P);
  free(Q);
  free(M);

  
  struct Emp
  {
    int enumber;
    char ename[20];
    float esal;
  };

  struct Emp *ptr;//ptr gets memory allocation
  
  ptr = (struct Emp*) malloc(sizeof(struct Emp));
  if (ptr == NULL){
    printf("out of memory error\n");
  }
  else {
    printf("Enter Employee details: enum ename esal ");
    scanf("%d %s %f", &ptr->enumber, ptr->ename, &ptr->esal);
    printf("%d %s %.2f\n", ptr->enumber, ptr->ename, ptr->esal);
  }

  free(ptr);
}
