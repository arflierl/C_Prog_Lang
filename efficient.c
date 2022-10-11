#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Sum rows of n X n matrix a and store in vecotr b

void sum_rows_bad(double *a, double *b, long n) {
  long i, j;
  for (i = 0; i < n; i++) {
    b[i] = 0;
    for (j = 0; j < n; j++) {
      b[i] += a[i*n + j]; //access memory every iteration, registers much more efficient
    }
  }
}

void sum_rows_good(double *a, double *b, long n) {
  long i, j;
  for (i = 0; i < n; i++) {
    double val = 0; //remove aliasing
    for (j=0; j < n; j++) {
      val += a[i*n + j]; //no longer needs to access memory within loop
    }
    b[i] = val;
  }
}

double A[9] = {0, 1, 2,
	       4, 8, 16,
	       32, 64, 128};

double B[3];

int main () {
  sum_rows_bad(A, B, 3);
  sum_rows_good(A, B, 3);
  printf("b[%d]: %f\n", 0, B[0]);
  printf("b[%d]: %f\n", 1, B[1]);
  printf("b[%d]: %f\n", 2, B[2]);
}
	    
	     
