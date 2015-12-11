/* Graph Theory: Floyd's Algorithm - All pairs shortest path
   =================================================================
   Description: Given a graph stored in an adjacency matrix, returns
                the shortest distance from node i to node j in
		d[i][j].  Weights of each edge must be nonnegative,
		and -1 is used to indicate an empty edge
   
   Complexity:  O(N^3)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 17, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 1 Successful use (Sept 2002)
                 (Spain Problem 10354)
   Notes:       Costs may be changed to doubles, but then elements
                need to be initialized individually (commented out
		below).
*/

#include <stdio.h>
#include <string.h>

#define MAXN 101
#define CType int

CType g[MAXN][MAXN], dist[MAXN][MAXN];

void floyd(int n){
  int i, j, k;

  memcpy(dist, g, sizeof(g));
  for(k = 0; k < n; k++) for(i = 0; i < n; i++) for(j = 0; j < n; j++){
    if(dist[i][k] != -1 && dist[k][j] != -1){
      CType temp = dist[i][k] + dist[k][j];
      if(dist[i][j] == -1 || dist[i][j] > temp)
	dist[i][j] = temp;
    }
  }
  for(i = 0; i < n; i++) dist[i][i] = 0;
}

int main(){
  int i, j, n;
  CType w;
  
  scanf("%d", &n);  

  /* Clear graph */
  memset(g, -1, sizeof(g));
  
  /* If using doubles: 
     for(i = 0; i < n; i++) for(j = 0; j < n; j++) g[i][j] = -1;
   */
  
  /* Read graph */
  while(scanf("%d %d %d", &i, &j, &w) == 3){
    g[i][j] = g[j][i] = w;
  }
  
  floyd(n);

  while(scanf("%d %d", &i, &j) == 2){
    printf("%d %d: %d\n", i, j, dist[i][j]);
  }

  return 0;
}
