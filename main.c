 
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "life.h"

/* Be sure to read life.h and the other given source files to understand
 * what they provide and how they fit together.  You don't have to
 * understand all of the code, but you should understand how to call
 * parse_life() and clearterm().
 */

/* This is where your program will start.  You should make sure that it
 * is capable of accepting either one or two arguments; the first
 * argument (which is required) is a starting state in one of the Life
 * formats supported by parse_life(), and the second (which is optional)
 * is a number of generations to run before printing output and stopping.
 *
 * The autograder will always call your program with two arguments.  The
 * one-argument format (as described in the handout) is for your own
 * benefit!
 */

char **parse_life(const char *filename);
int atoi(const char *str);
int generation;
int current = 1;
int y = GRIDY + 2; // = 26 actual size of gameBoard w/ border
int x = GRIDX + 2; // = 82 actual size of gameBoard w/ border
void createGameBoard(char gameBoard[2][y][x]);
void fillGameBoard(char gameBoard[2][y][x], char **arr);
void gameTime(char arr[2][y][x], int gen);
void printArray(char arr[2][y][x], int g);

int main(int argc, char *argv[])
{
  if (argc == 1 || argc > 3) {
    printf("Error: invalid number of arguments\n");
    return 1;
  }
  generation = atoi(argv[2]);
  char **arr = parse_life(argv[1]); //the starting position
  char gameBoard[2][y][x]; //the 3D array with border
  createGameBoard(gameBoard); //filling initial game board with dead cells
  fillGameBoard(gameBoard, arr); //filling first generation 0 with starting position
  gameTime(gameBoard, generation);
  printArray(gameBoard, generation);
  return 0;
}

void createGameBoard(char gameBoard[2][y][x]) { //gameBoard is a larger array then char **arr so loops must reflect
  int m, i, j;
  for (m = 0; m < 2; m++) { 
    for (i = 0; i < y; i++) { //goes from index 0 to 25
      for (j = 0; j < x; j++) { //goes from index 0 to 81
	gameBoard[m][i][j] = DEAD;
      }  
    }
  }
}

void fillGameBoard(char gameBoard[2][y][x], char **arr) {
  int i, j;
  for (i = 1; i < 25; i++) { //indexes 1 to 24 need to be filled, 0 and 25 are border cells and DEAD
    for (j = 1; j < 81; j++) { //indexes 2 to 80 need to be filled, 0 and 81 are border cells and DEAD
      gameBoard[0][i][j] = arr[i - 1][j - 1]; //parse_life has indexes 0 to 23
    }
  }
}

void gameTime(char arr[2][y][x], int gen) { //this happens WITHIN the border
  int use = 1;
  while (current <= gen) { // if on generation 0 this DOES NOT happen
    int search;
    if (current == 1 || use == 1) {
      search = 0;
    } else {
      search = 1;
    }
    int i, j;
    for (i = 1; i < 25; i++) {
      for (j = 1; j < 81; j++) {
	int neighbors = 0;
	if (arr[search][i-1][j-1] == LIVE) {
	  neighbors++;
	}
	if (arr[search][i-1][j] == LIVE) {
	  neighbors++;
	}
	if (arr[search][i-1][j+1] == LIVE) { //searching large matrix
	  neighbors++;
	}
	if (arr[search][i][j-1] == LIVE) {
	  neighbors++;
	}
	if (arr[search][i][j+1] == LIVE) {
	  neighbors++;
	}
	if (arr[search][i+1][j-1] == LIVE) {
	  neighbors++;
	}
	if (arr[search][i+1][j] == LIVE) {
	  neighbors++;
	}
	if (arr[search][i+1][j+1] == LIVE) {
	  neighbors++;
	}
	if (arr[search][i][j] == DEAD && neighbors == 3) {
	  arr[use][i][j] = LIVE;
	}
	if (arr[search][i][j] == DEAD && neighbors != 3) { //editing same indexes as same size matrix
	  arr[use][i][j] = DEAD;
	}
	if (arr[search][i][j] == LIVE && (neighbors < 2 || neighbors > 3)) {
	  arr[use][i][j] = DEAD; 
	}
	if (arr[search][i][j] == LIVE && (neighbors == 2 || neighbors == 3)) {
	  arr[use][i][j] = LIVE; 
	}
      }
    }
    current++; //increases after a generation is complete
    use = (current % 2); //use must now change first time through it is 1, second 0, third 2, and so on.
  }
}
  
void printArray(char arr[2][y][x], int g) {
  int i, j;
  int whichOne = g % 2; //generation 0 prints 0, generation of odd prints 1, even 0
  for (i = 1; i < 25; i++) { //start INSIDE the border 
	for (j = 1; j < 81; j++) {
	  printf("%c", arr[whichOne][i][j]);
	  if (j == 80) { 
	    printf("\n");
	  }	  
	}
      }
}
