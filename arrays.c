#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void printArray(char arr[5][12]);
void neighborCount(char arr[5][12]);

char myArray[5][12] = {
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  {' ',' ', 'X', 'X', ' ','X', 'X', ' ', ' ', 'X', ' ', ' '} ,
  {' ', 'X', 'X', ' ', ' ', 'X', 'X', ' ', ' ', ' ', 'X',' '},
  {' ',' ', 'X', ' ', 'X', 'X', ' ', ' ', 'X', 'X', ' ',' '},
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
};
char nextArray[5][12];

int main() {

  printArray(myArray);
  neighborCount(myArray);
  printArray(nextArray);

  return 0;
}

void printArray(char arr[5][12]) { //function to output state of grid to terminal
  int i, j;

  for (i = 0; i < 5; i++) {

    for (j = 0; j < 12; j++) {
      printf("%c", arr[i][j]);

      if (j == 11) {
	printf("\n");
      }

    }
    
  }
  
}

void neighborCount(char arr[5][12]) {
  int i, j;
  char alive = 'X';
  char dead = ' ';

  for (i = 1; i < 4; i++) {

    for (j = 1; j < 11; j++) {
      int neighbors = 0;
      if (arr[i-1][j-1] == alive) {
	neighbors++;
      }
      if (arr[i-1][j] == alive) {
	neighbors++;
      }
      if (arr[i-1][j+1] == alive) {
	neighbors++;
      }
      if (arr[i][j-1] == alive) {
	neighbors++;
      }
      if (arr[i][j+1] == alive) {
	neighbors++;
      }
      if (arr[i+1][j-1] == alive) {
	neighbors++;
      }
      if (arr[i+1][j] == alive) {
	neighbors++;
      }
      if (arr[i+1][j+1] == alive) {
	neighbors++;
      }
      if (arr[i][j] == dead && neighbors == 3) {
	printf("element [%d][%d] was dead but is now alive!\n", i, j);
	nextArray[i][j] = 'X';
      }
      if (arr[i][j] == dead && neighbors != 3) {
	printf("element [%d][%d] was dead and is still dead\n", i, j);
	nextArray[i][j] = ' ';
      }
      if (arr[i][j] == alive && neighbors < 2) {
	printf("element [%d][%d] was alive but is now dead\n", i, j);
	nextArray[i][j] = ' ';
      }
      if (arr[i][j] == alive && neighbors > 3) {
	printf("element [%d][%d] was alive but is now dead\n", i, j);
	nextArray[i][j] = ' ';
      }
      if (arr[i][j] == alive && (neighbors == 2 || neighbors == 3)) {
	printf("element [%d][%d] was alive and is still alive!\n", i, j);
	nextArray[i][j] = 'X';
      }
	
    }
  }

}  




