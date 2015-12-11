/* Graph Theory: K-cycle in a directed tournament graph
   =================================================================
   Description: Given a tournament graph, and a value k, finds a
                k-cycle if one exists

   Complexity:  O(N^2 ??) Approximate
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        March 20, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 1 (Problem B: Tour from 2003 Jan 21)
   Notes:       -A strongly connected tournament of size n is 
                 pancyclic - it contains all cycles from 3 to n
		 in it.
*/

#include <stdio.h>
#include <vector>
using namespace std;

#define VI vector<int>
#define MAXN 1000

VI g[MAXN], curr;
vector< VI > scc;
VI kcycle;
int dfsnum[MAXN], low[MAXN], id;
char done[MAXN], adj[MAXN][MAXN];

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

int FindCycle(VI v, int csize){
  VI cycle; int i, j, k, n = v.size();

  memset(low, -1, sizeof(low));
  memset(done, 0, sizeof(done));
  for(i = 0; i < n; i++) low[v[i]] = i;
  for(i = 0; i < n; i++)
    for(size_t j = 0; j < g[v[i]].size(); j++)
      if(low[g[v[i]][j]] != -1)
	adj[i][low[g[v[i]][j]]] = 1;
  
  for(i = 0; i < n; i++)  for(j = 0; j < n; j++){
    if(!adj[i][j]) continue;
    for(k = 0; k < n; k++)
      if(adj[j][k] && adj[k][i]){
	cycle.push_back(i); done[i] = 1;
	cycle.push_back(j); done[j] = 1;
	cycle.push_back(k); done[k] = 1;
	goto found;
      }
  }
 found:
  while((int)cycle.size() < csize){
    vector<int> in, out;
    for(i = 0; i < n; i++){
      if(done[i]) continue;
      if(adj[cycle[cycle.size()-1]][i] && adj[i][cycle[0]]){
	cycle.push_back(i);
	done[i] = 1;
	goto next;
      }
      for(size_t j = cycle.size()-2; j >= 0; j--){
	if(adj[cycle[j]][i] && adj[i][cycle[(j+1)%cycle.size()]]){
	  cycle.insert(&cycle[j+1], i);
	  done[i] = 1;
	  goto next;
	}
      }
      if(adj[cycle[0]][i]) out.push_back(i);
      else in.push_back(i);
    }
    for(size_t i = 0; i < out.size(); i++){
      if(done[i]) continue;
      for(size_t j = 0; j < in.size(); j++){
	if(done[j]) continue;
	if(adj[i][j]){
	  done[cycle[cycle.size()-1]] = 0;
	  done[i] = done[j] = 1;
	  cycle[cycle.size()-1] = i;
	  cycle.push_back(j);
	  goto next;
	}
      }
    }
  next:  
    ;
  }
  kcycle.clear();
  for(size_t i = 0; i < cycle.size(); i++)
    kcycle.push_back(v[cycle[i]]);
}

int getKCycle(int n, int k){

  strong_conn(n);
  for(size_t i = 0; i < scc.size(); i++){
    if((int)scc[i].size() >= k){
      FindCycle(scc[i], k);
      return 1;
    }
  }
  return 0;
}

int main(){
  int n, i, x, y, k;
  
  /* Read in number of vertices, size of cycle */
  while(scanf("%d %d", &n, &k) == 2){

    /* Clear adj. lists */
    for(i = 0; i < n; i++) g[i].clear();

    /* Build adj. lists */
    for(i = 0; i < n*(n-1)/2; i++){
      scanf("%d %d", &x, &y);
      g[x].push_back(y);
    }
    
    if(getKCycle(n, k)){
      printf("%d-cycle exists:\n", k);
      for(i = 0; i < k; i++)
	printf("%d%c", kcycle[i], i == k-1 ? '\n' : ' ');
    } else {
      printf("No %d-cycle exists\n", k);
    }
  }
  return 0;
}
