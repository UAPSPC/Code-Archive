/* Graph Theory: Maximum Bipartite Matching
   =================================================================
   Description: Given a bipartite graph G = {U,V,E}, this routine
                computes the maximum bipartite matching.

		For vertex i of set U:
		match[i] = -1 means i is not matched
		match[i] =  x means the edge i->(x-|U|) is selected
		                             **********
		For simplicity, use addEdge(i,j,n) to add edges, where
		0 <= i < |U| and 0 <= j < |V| and |U| = n.

		If there is an edge from vertex i of U to vertex
		j of V then: e[i][j+|U|] = e[j+|U|][i] = 1. 
		                  ******     *****

   Complexity:  O(U+V) where U and V are the sizes of the sets
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        May 6, 2003
   References:  Waterloo code
   -----------------------------------------------------------------
   Reliability: 2 (Spain 10080 - Golpher holes II, 
                   Housing Complexes Mar 8th, 2003)
   Notes:       - If |U| = n and |V| = m, then vertices are assumed
                  to be from [0,n-1] in set U and [0,m-1] in set V.
		- Remember that match[i]-n gives the edge from i,
		  not just match[i].
		- This code is roughly 2 times slower than the old
		  code since it doesn't try multiple BFS paths at
		  once, however, it's about 4 times shorter...

                A bipartite graph is one where the vertices can be
                separated into two disjoint sets U and V, such that
		all edges in the graph are between a vertex in U and
		a vertex iv V.  A maximum matching on such a graph
		is the selection of the most edges such that each
		vertex is adjacent to at most one edge.
		
		The maximum matching is equivalent to the minimal
		vertex cover in a bipartite graph.
*/
#include <stdio.h>
#include <string.h>

#define MAXN 300          /* How many vertices in U+V (in total) */

char e[MAXN][MAXN];       /* MODIFIED Adj. matrix (see note) */
int match[MAXN], back[MAXN], q[MAXN], tail;

void addEdge(int x, int y, int n){
  e[x][y+n] = e[y+n][x] = 1;
}

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
  int i;
  memset(match, -1, sizeof(match));
  for(i = 0; i < n+m; i++) if(find(i,n,m)) i = 0;
}

int main(){
  int n, m, esize, x, y;
  int i, count;

  /* Read size of set U into n, size of set V into m */
  while(scanf("%d %d", &n, &m) == 2){

    memset(e, 0, sizeof(e));          /* Clear edges */
    scanf("%d", &esize);              /* get # of edges */
    while(esize--){
      scanf("%d %d", &x, &y);         /* add edges */ 
      addEdge(x,y,n);                 /* Edges [0,n-1]->[0,m-1] */
    }

    bipmatch(n, m);                   /* Perform matching */

    for(count = i = 0; i < n; i++){   /* Print results */
      if(match[i] != -1){              
	printf("%d->%d\n", i, match[i]-n);
	count++;
      }
    }
    printf("Matching size: %d\n", count);
  }
  return 0;
}
