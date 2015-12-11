/* Graph Theory: Topological Sort
   =================================================================
   Description: Given a directed acyclic graph, fills an array 
                called top[] with the nodes in topological order.
   
   Complexity:  O(N) where N is the number of nodes
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Feb 20, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       A topological sort of a DAG is a linear ordering of 
                it's vertices such that for any edge u->v in the 
		the graph, u comes before v in the ordering.

		There may be more than one way to topological sort
		a DAG.  If the lexicographically first one is needed,
		it may be a good idea to use a priority queue instead
		and just pull off vertices with 0 in-degree

	        Vertices are numbered 0..N-1.
*/

#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

#define MAXN 1000

vector<int> g[MAXN];
int id, top[MAXN], seen[MAXN];

void DFS(int x){
  seen[x] = 1;
  for(size_t i = 0; i < g[x].size(); i++)
    if(!seen[g[x][i]]) DFS(g[x][i]);
  top[id--] = x;
}

void top_sort(int n){
  memset(seen, 0, sizeof(seen));
  id = n-1;
  for(int i = 0; i < n; i++)
    if(!seen[i]) DFS(i);
}

int main(){
  int n, m, i, x, y;
  
  /* n = # of vertices, m = # of edges */
  while(scanf("%d %d", &n, &m) == 2){  
    for(i = 0; i < n; i++) g[i].clear();     
    for(i = 0; i < m; i++){
      scanf("%d %d", &x, &y);
      g[x].push_back(y);
    }
    top_sort(n);
    for(i = 0; i < n; i++)
      printf("%d ", top[i]);
    printf("\n");
  }
  return 0;
}
