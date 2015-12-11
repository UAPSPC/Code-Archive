/* Dynamic Programming: Edit Distance (with path recovery)
   =================================================================
   Description: Computes the edit distance for two strings.  Namely 
                this involves certain costs for Replacement,
		Insertions and Deletions.  Given these costs, and
		two words, this program calculates the minimum cost
		way to transform the first string to the second.  An
		added bonus is the PathRecovery() subroutine, which
		prints out exactly what happens step by step.  
   
   Complexity:  O(N^2) where N is the size of the larger of the two
                strings
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        May 10, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 1 (Spain Problem 526)
              
   Notes:       Some modifications need to be made in order to fix
                path recovery.  
*/

#include <stdio.h>
#include <string.h>

#define MAXN 90

char move[MAXN][MAXN];  /* Type of command used */
int  g[MAXN][MAXN];      /* Cost of changes */

int editDistance(char *src, char *dst, int replace, int insert, int delete){
  int i, j, l1, l2;

  l1 = strlen(src);
  l2 = strlen(dst);

  for(j = 0; j <= l1; j++){
    g[0][j] = j;
    move[0][j] = 'D';
  }
  
  for(i = 1; i <= l2; i++){
    g[i][0] = i;
    move[i][0] = 'I';
    
    for(j = 1; j <= l1; j++){
      g[i][j] = g[i-1][j-1]+replace;
      move[i][j] = 'R';
      
      if(g[i-1][j]+insert < g[i][j]){
        g[i][j] = g[i-1][j]+insert;
        move[i][j] = 'I';
      }
      
      if(g[i][j-1]+delete < g[i][j]){
        g[i][j] = g[i][j-1]+delete;
        move[i][j] = 'D';
      }
      
      if(src[j-1] == dst[i-1] && g[i-1][j-1] < g[i][j]){
        g[i][j] = g[i-1][j-1];
        move[i][j] = 'N';
      }
    }
  }
  return g[l2][l1];
}

int counter;
void PathRecovery(int x, int y, int *delta, char *src, char *dst){
  int ndelta;
  
  if(x == 0 && y == 0){
    *delta = 0;
    return;
  }
  else {
    switch(move[x][y]){
    case 'R':
      PathRecovery(x-1,y-1,&ndelta,src,dst);
      *delta = ndelta;
      printf("%d Replace %d,%c\n", counter++, y+ndelta, dst[x-1]);
      break;
    case 'I':
      PathRecovery(x-1,y,&ndelta,src,dst);
      *delta = ndelta+1;
      printf("%d Insert %d,%c\n", counter++, y+ndelta+1, dst[x-1]);
      break;
    case 'D':
      PathRecovery(x,y-1,&ndelta,src,dst);
      *delta = ndelta-1;
      printf("%d Delete %d\n", counter++, y+ndelta);
      break;
    case 'N':
      PathRecovery(x-1,y-1,&ndelta,src,dst);
      *delta = ndelta;
      break;
    }
  }
}

int main(){
  int x, first = 1, delta;
  char s1[MAXN], s2[MAXN];
  
  while(fgets(s1, MAXN, stdin)){
    if(first) first = 0;
    else printf("\n");
    fgets(s2, MAXN, stdin);
    s1[strlen(s1)-1] = 0;
    s2[strlen(s2)-1] = 0;
    if(first) first = 0;
    else printf("\n");
    x = editDistance(s1, s2, 1,1,1);
    printf("%d\n", x);
    counter = 1;
    PathRecovery(strlen(s2), strlen(s1), &delta, s1, s2);
  }
  return 0;
}
