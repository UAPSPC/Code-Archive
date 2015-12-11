/* Search: Self Avoiding walk template
   =================================================================
   Description: A template for a self-avoiding walk search.  
                A self avoiding walk is one in which at each turn 
		one walks N, E, S or W, but never visits a place
		he/she has visited.

   Complexity:  O(exponential)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        March 12, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>
#include <string.h>

#define MAXN 100

int Sx[MAXN], Sy[MAXN], n, total;
char walk[MAXN];
char dir[5] = "NESW";
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

void Walk(int pos){
  int i, j;
  if(pos == n){
    total++;
    walk[pos] = 0;
    printf("%s%c", walk, total%10 ? ' ' : '\n');
    return;
  }
  for(i = 0; i < 4; i++){
    Sx[pos+1] = Sx[pos]+dx[i];
    Sy[pos+1] = Sy[pos]+dy[i];
    walk[pos] = dir[i];
    for(j = 0; j <= pos; j++)
      if(Sx[j] == Sx[pos+1] && Sy[j] == Sy[pos+1]) break;
    if(j == pos+1) Walk(pos+1);
  }
}

int main(){
  while(scanf("%d", &n) == 1){
    total = Sx[0] = Sy[0] = 0;
    Walk(0);   /* Start recursive call */
    printf("\nTotal # of self-avoiding walks of size %d = %d\n\n", n, total);
  }
  return 0;
}
