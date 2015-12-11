/* Search: Graph coloring template
   =================================================================
   Description: Given a graph, this is a template for k-coloring
                it.
   
   Complexity:  O(exponential)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Mar 14, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       -The graph is given by the adjacency matrix adj[][].
                -The coloring of the graph is stored in color[];
		-Colors run from 0...k-1
*/

#include <stdio.h>
#include <string.h>

#define MAXN 50

int adj[MAXN][MAXN], n, k, total;
int color[MAXN];

void BackTrack(int pos){
  int i, c;
  if(pos == n){
    total++;
    printf("{");
    for(i = 0; i < n; i++)
      printf("%d%c", color[i],  i == n-1 ? '}' : ',');
    printf("%c", total % 5 ? ' ' : '\n');
    return;
  }
  for(c = 0; c < k; c++){
    for(i = 0; i < pos; i++)
      if(adj[i][pos] && color[i] == c) break;
    if(i == pos){
      color[pos] = c;
      BackTrack(pos+1);
    }
  }
}

int main(){
  int i, j;
  
  while(scanf("%d %d", &n, &k) == 2){
    for(i = 0; i < n; i++) for(j = 0; j < n; j++)
      scanf("%d", &adj[i][j]);
    total = 0;
    BackTrack(0);
    printf("Total %d-colorings: %d\n", k, total);
  }
  return 0;
}
