/* Graph Theory: Minimum disjoint-vertex path cover on an
                 acyclic directed graph
   =================================================================
   Description: Given a directed ACYCLIC graph, this routine finds 
                the minimum number of directed vertex-disjoint paths 
		which cover all the vertices of the graph.
		
		The paths are returned as a vector of vector of ints.
		Nodes are assumed to be labelled [0..n-1].
   
   Complexity:  O(N^2)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Feb 12, 2003
   References:  "Covering the Points of a Digraph with
                 Point-Disjoint Paths and it's Application to Code
		 Generation" - F. T. Boesch & J. F. Gimpel
   -----------------------------------------------------------------
   Reliability: 1 (Air Raid - Problem A Feb 11, 2003)
   Notes:       The idea behind this algorithm is to split each
                vertex v into two vertices: v_in and v_out.  For
		each of the original edges u->v, create a new
		edge u_out -> v_in.  Proceed by running maximum
		bipartite matching on this new graph.  Run through
		each matching, following paths when they occur
		(We need that the graph is acyclic so that such
		 a path does not result in a cycle)
		
		The problem for general directed graphs is NP-C.
*/

#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define VI vector<int>
#define VII vector<VI>

#define MAXN 300

char e[MAXN][MAXN];       /* Adj. Matrix */
int match[MAXN], back[MAXN], q[MAXN], tail;

int find(int x, int n, int m){
  int i, j, r;

  if(match[x] != -1) return 0;
  memset(back, -1, sizeof(back));
  for(q[i=0]=x, tail = 1; i < tail; i++)
    for(j = 0; j < n+m; j++){
      if(!e[q[i]][j]) continue;
      if(match[j] != -1){
        if(back[j] == -1){
          back[j] = q[i];
          back[q[tail++] = match[j]] = j;
        }
      } else {
        match[match[q[i]] = j] = q[i];
        for(r = back[q[i]]; r != -1; r = back[back[r]])
          match[match[r] = back[r]] = r;
        return 1;
      }
    }
  return 0;
}

void bipmatch(int n, int m){
  memset(match, -1, sizeof(match));
  for(int i = 0; i < n+m; i++) if(find(i,n,m)) i = 0;
}

VII path_cover(int n){
  VII res; char done[MAXN] = {0};
  
  bipmatch(n, n);
  for(int i = 0; i < n; i++){
    if(done[i]) continue;
    VI p;
    for(int j = i; j != -n-1; j = match[j]-n){
      done[j] = 1;
      p.push_back(j);
    }
    res.push_back(p);
  }
  return res;
}

int main(){
  int n, m, x, y; VII path;
  
  while(scanf("%d %d", &n, &m) == 2){   /* n = number of vertices */
    memset(e, 0, sizeof(e));            /* m = number of edges */
    for(int i = 0; i < m; i++){
      scanf("%d %d", &x, &y);           /* vertices [0..n-1] */
      e[x][n+y] = e[n+y][x] = 1;        /* Offset y by n in bip. graph */
    }
    path = path_cover(n);

    printf("Minimum number of vertex disjoint paths: %d\n", path.size());
    for(size_t i = 0; i < path.size(); i++){
      printf("Path %d: ", i+1);
      for(size_t j = 0; j < path[i].size(); j++)
        printf(" %d", path[i][j]);
      printf("\n");
    }
  }
  return 0;
}
