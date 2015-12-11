/* Search: Orthogonal-Latin Squares
   =================================================================
   Description: This is a template for finding orthogonal Latin
                Squares.
		
		A latin square is a N by N matrix which uses the 
		numbers 0..N-1, such that each number occurs exactly
		once in each column, and each row.
		
		Two Latin squares are orthogonal if the square
		resulting from the overlapping of the two squares 
		has no pair of elements that occurs twice.
		
		e.g.
		1 2 3  1 2 3      [1,1] [2,2] [3,3]
		2 3 1  3 1 2  ->  [2,3] [3,1] [1,2]
		3 1 2  2 3 1      [3,2] [1,3] [2,1]
		
		An k-set of orthogonal Latin squares is a set of 
		k Latin squares such that every pair is orthogonal.

   Complexity:  O(exponential)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Mar 19, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       - The number of subsets of orthogonal Latin squares
                  can be enormous.  
		- If the order is N, there is at most a N-1 set of
		  orthogonal Latin squares
		- This program finds a maximum set quickly for 3,4,5
		  but not for any larger.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 10    /* Maximum order */
#define MAXK 10    /* Maximum set size */

int n, setsize;

int curr[MAXK][MAXN][MAXN];         /* Stores the Latin squares */
char row[MAXK][MAXN][MAXN];         /* Used to mark used elements */
char col[MAXK][MAXN][MAXN];         /* Used to mark used elements */
char ort[MAXK][MAXK][MAXN][MAXN];   /* Used to mark used elements */

/* Print procedure.  Modify as necessary */
void PrintLatin(int size){
  int i, j, k;
  for(i = 0; i < n; i++) for(k = 0; k < size; k++){
    printf("[");
    for(j = 0; j < n; j++)
      printf("%d%c", curr[k][i][j], j == n-1 ? ']' : ',');
    printf("%c", k == size-1 ? '\n' : ' ');
  }
}

/* The search goes through the kth square, xth row, yth column, 
   with a special flag called "same" which forces an ordering on
   the Latin squares, such that permutations are not considered
*/
void Search(int k, int x, int y, int same){
  int i, j;

  if(!x && !y){
    if(k >= 2){
      /* Completed another square */
      printf("[Subset %d] %d-set:\n", ++setsize, k);
      PrintLatin(k);
    } 
    same = k;
  }
  for(i = same ? curr[k-1][x][y] : 0; i < n; same = 0, i++){
    if(row[k][x][i] || col[k][y][i]) continue;
    for(j = 0; j < k && !ort[k][j][i][curr[j][x][y]]; j++);
    if(j != k) continue;
    row[k][x][i] = col[j][y][i] = 1;
    for(j = 0; j < k; j++) ort[k][j][i][curr[j][x][y]] = 1;
    curr[k][x][y] = i;
    if(y == n-1){
      if(x == n-1) Search(k+1, 0, 0, same);
      else Search(k, x+1, 0, same);
    } else {
      Search(k, x, y+1, same);
    }
    row[k][x][i] = col[j][y][i] = 0;
    for(j = 0; j < k; j++) ort[k][j][i][curr[j][x][y]] = 0;
  }
}

int main(){
  while(scanf("%d", &n) == 1){
    setsize = 0;
    Search(0,0,0,0);
    printf("Total # of orthogonal squares of order %d: %d\n",
	   n, setsize);
  }
  return 0;
}





