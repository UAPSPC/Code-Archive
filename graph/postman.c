/* Graph Theory: Chinese Postman Problem
   =================================================================
   Description: Given a graph, this problem returns the shortest
                cost such that every edge is visited at least once.
		(no path is returned)

   Complexity:  O(1*3*5*7*...*(# of odd vertices - 1))
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        March 21, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 1 (Problem B: Jogging Trails  2002 Jun 01)
   Notes:       - vertices are numbered [0..n-1]
                - multiple edges are allowed between vertices,
		  however the graph g only stored the least cost
		  (making the path hard to get back)
		- The maximum # of vertices solvable is roughly 20
		- How it works: Need to generate a Euler tour, so
		  try pairing off any remaining odd vertices with
		  the shortest path between them.  Try all 
		  perfect matchings to find the best such matching
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN  20
#define DISCONNECT -1

int g[MAXN][MAXN];     /* Adj matrix (keep lowest cost multiedge)*/
int deg[MAXN];         /* Degree count */
int A[MAXN+1];         /* Used by perfect matching generator */
int sum;               /* Sum of costs */
int odd;
int best;
  
void floyd(int n){
  int i, j, k;

  for(k = 0; k < n; k++) for(i = 0; i < n; i++) for(j = 0; j < n; j++)
    if(g[i][k] != -1 && g[k][j] != -1){
      int temp = g[i][k] + g[k][j];
      if(g[i][j] == -1 || g[i][j] > temp)
	g[i][j] = temp;
    }
  for(i = 0; i < n; i++) g[i][i] = 0;
}

void checkSum(){
  int i, temp;

  for(i = temp = 0; i < odd/2; i++)
    temp += g[A[2*i]][A[2*i+1]];
  if(best == -1 || best > temp) best = temp;
}    
  
void perfmatch(int x){
  int i, t;
  if(x == 2) checkSum();
  else {
    perfmatch(x-2);
    for(i = x-3; i >= 0; i--){
      t = A[i];
      A[i] = A[x-2];
      A[x-2] = t;
      perfmatch(x-2);
    }
    t = A[x-2];
    for(i = x-2; i >= 1; i--)  A[i] = A[i-1];
    A[0] = t;
  }
}

int postman(int n){
  int i;

  floyd(n);
  for(odd = i = 0; i < n; i++)
    if(deg[i]%2) A[odd++] = i;
  if(!odd) return sum;
  best = -1;
  perfmatch(odd);
  return sum+best;
}

int main(){
  int i, u, v, c, n, m;
  
  while(scanf("%d %d", &n, &m) == 2){

    /* Clear graph and degree count */
    memset(g, -1, sizeof(g));    
    memset(deg, 0, sizeof(deg));

    for(sum = i = 0; i < m; i++){
      scanf("%d %d %d", &u, &v, &c);
      u--; v--;
      deg[u]++; deg[v]++;
      if(g[u][v] == -1 || g[u][v] > c) g[u][v] = c;
      if(g[v][u] == -1 || g[v][u] > c) g[v][u] = c;
      sum += c;
    }
    printf("Best cost: %d\n", postman(n));
  }
  return 0;
}
