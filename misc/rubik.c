/* Miscellaneous: Rubik's Cube simulator
   =================================================================
   Description: Given a flattened Rubik's cube, provides utilities
                for clockwise rotation of each face
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Jan 27, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 1 Problem A: Grandapa's Rubik Cube
                             (ACM South America 2002) Jan 26, 2003
   Notes:       Each cube must be represented by a 9 by 12 character
                array, with the faces numbered as follows.

		 0123456789AB   Rotate(Cube c, int f) rotates face f
		0...+-+......   90 degrees clockwise.
		1...|4|......
		2...+-+......     +-----+          +-----+
		3+-++-++-++-+     |  ^  |  rotate  |     |
		4|0||1||2||3|     |  |  |  ----->  | *-->|
		5+-++-++-++-+     |  *  |   cw 90  |     |
		6...+-+......     +-----+          +-----+
		7...|5|......   Rotating 90 degrees counter-clockwise
		8...+-+......   may be done by calling Rotate 3 times

		isSolved(Cube c) returns 1 if each face contains the
		same characters, and 0 otherwise

		printCube(Cube c) is provided to see cube c.
*/

#include <stdio.h>
#include <string.h>

typedef struct{
  char g[9][12];
} Cube;

int cx[6] = {4,4,4,4,1,7};
int cy[6] = {1,4,7,10,4,4};

int rx[6][4][3] = {{{0,1,2}, {5,4,3}, {6,7,8}, {3,4,5}},
		   {{2,2,2}, {5,4,3}, {6,6,6}, {3,4,5}},
		   {{2,1,0}, {5,4,3}, {8,7,6}, {3,4,5}},
		   {{5,4,3}, {8,8,8}, {3,4,5}, {0,0,0}},
		   {{3,3,3}, {3,3,3}, {3,3,3}, {3,3,3}},
		   {{5,5,5}, {5,5,5}, {5,5,5}, {5,5,5}}};

int ry[6][4][3] = {{{3,3,3}, {11,11,11}, {3,3,3}, {3,3,3}},
		   {{3,4,5}, {2,2,2}, {5,4,3}, {6,6,6}},
		   {{5,5,5}, {5,5,5}, {5,5,5}, {9,9,9}},
		   {{8,8,8}, {3,4,5}, {0,0,0}, {5,4,3}},
		   {{0,1,2}, {3,4,5}, {6,7,8}, {9,10,11}},
		   {{11,10,9}, {8,7,6}, {5,4,3}, {2,1,0}}};

int isSolved(Cube c){
  int i, x, y;
  
  for(i = 0; i < 6; i++)
    for(x = cx[i]-1; x <= cx[i]+1; x++)
    for(y = cy[i]-1; y <= cy[i]+1; y++)
      if(c.g[x][y] != c.g[cx[i]][cy[i]]) return 0;
  return 1;
}

Cube Rotate(Cube c, int f){
  char t[3][3]; int i, j, x = cx[f], y = cy[f];

  for(i = 0; i < 3; i++) for(j = 0; j < 3; j++) 
    t[i][j] = c.g[x+i-1][y+j-1];

  for(i = 0; i < 3; i++) for(j = 0; j < 3; j++)
    c.g[x+i-1][y+j-1] = t[2-j][i];

  for(i = 0; i < 3; i++)
    t[0][i] = c.g[rx[f][0][i]][ry[f][0][i]];
  
  for(j = 0; j < 3; j++) for(i = 0; i < 3; i++)
      c.g[rx[f][j  ][i]][ry[f][j  ][i]] =
      c.g[rx[f][j+1][i]][ry[f][j+1][i]];
  
  for(i = 0; i < 3; i++)
    c.g[rx[f][j][i]][ry[f][j][i]] = t[0][i];
  
  return c;
}

void printCube(Cube c){
  int i, j;

  for(i = 0; i < 9; i++){
    for(j = 0; j < 12; j++)
      printf("%c", c.g[i][j] ? c.g[i][j] : ' ');
    printf("\n");
  }
}

int main(){
  int i, j, d; Cube c;

  memset(c.g, 0, sizeof(c.g));
  for(i = 0; i < 3; i++) for(j = 3; j < 6; j++)
    scanf(" %c", &c.g[i][j]);
  
  for(i = 3; i < 6; i++) for(j = 0; j < 12; j++)
    scanf(" %c", &c.g[i][j]);

  for(i = 6; i < 9; i++) for(j = 3; j < 6; j++)
    scanf(" %c", &c.g[i][j]);
  
  printCube(c);
  while(scanf(" %d", &d) == 1){
    c = Rotate(c, d);
    printf("\n");
    printCube(c);
  }
  return 0;
}
