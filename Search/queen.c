/* Search: N non-attacking Queens
   =================================================================
   Description: The following is a template for finding valid
                configurations for the N-Queens problem.

   Complexity:  O(exponential)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Mar 12, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 
   Notes:       rows/cols labelled 0..n-1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100

int S[MAXN], used[MAXN], n, total;

void nQueens(int pos){
  int i, j;
  if(pos == n){
    total++;
    for(i = 0; i < n; i++)
      printf("(%d,%d)%c", i, S[i], i == n-1 ? '\n' : ' ');
    return;
  } 
  for(i = 0; i < n; i++){
    if(used[i]) continue;
    for(j = 0; j < pos; j++)
      if(pos-j == abs(i-S[j])) break;
    if(j == pos){
      S[pos] = i;
      used[i] = 1;
      nQueens(pos+1);
      used[i] = 0;
    }
  }
}

int main(){
  while(scanf("%d", &n) == 1){
    memset(used, 0, sizeof(used));
    total = 0;
    nQueens(0);  /* Call this to start recursion */
    printf("Total valid configurations for n=%d: %d\n", n,total);
  }
  return 0;
}
