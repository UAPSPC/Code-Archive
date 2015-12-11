/* Graph Theory: Strongly Connected Components
   =================================================================
   Description: Given a directed graph, decomposes the graph into
                its strongly connected components.
		
		The components are returned in the vector of
		vector of ints scc.  
   
   Complexity:  O(V+E)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Feb 20, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       Nodes are assumed to be labelled 0..n-1
                - This routine works by finding the earliest node
		  reachable in the DFS tree.  If the earliest such
		  node is itself, then everything after it in the
		  DFS tree is a strongly connected component.
*/

#include <stdio.h>
#include <vector>
using namespace std;

#define VI vector<int>
#define MAXN 1000

VI g[MAXN], curr;
vector< VI > scc;
int dfsnum[MAXN], low[MAXN], id;
char done[MAXN];

void visit(int x){
  curr.push_back(x);
  dfsnum[x] = low[x] = id++;
  for(size_t i = 0; i < g[x].size(); i++)
    if(dfsnum[g[x][i]] == -1){
      visit(g[x][i]);
      low[x] <?= low[g[x][i]];
    } else if(!done[g[x][i]])
      low[x] <?= dfsnum[g[x][i]];

  if(low[x] == dfsnum[x]){
    VI c; int y;
    do{
      done[y = curr[curr.size()-1]] = 1;
      c.push_back(y);
      curr.pop_back();
    } while(y != x);
    scc.push_back(c);
  }
}

void strong_conn(int n){
  memset(dfsnum, -1, n*sizeof(int));
  memset(done, 0, sizeof(done));
  scc.clear(); curr.clear();
  for(int i = id = 0; i < n; i++)
    if(dfsnum[i] == -1) visit(i);
}

int main(){
  int n, m, i, x, y;
  
  while(scanf("%d %d", &n, &m) == 2){
    for(i = 0; i < n; i++) g[i].clear();
    for(i = 0; i < m; i++){
      scanf("%d %d", &x, &y);
      g[x].push_back(y);
    }
    strong_conn(n);
    for(size_t i = 0; i < scc.size(); i++){
      printf("Component %d:", i+1);
      for(size_t j = 0; j < scc[i].size(); j++)
	printf(" %d", scc[i][j]);
      printf("\n");
    }
  }
  return 0;
}
