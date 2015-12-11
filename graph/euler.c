/* Graph Theory: Eulerian Graphs
   =================================================================
   Description: This routine establishes if an undirected graph is
                Eulerian.  If a graph has an Eulerian path, or an
		Eulerian cycle, the buildPath() routine generates 
		the sequence of nodes visited in the global array
		seq[] of size 'seqsize'

		Before adding edges, call Init() to initialize all
		necessary data structures.

		Use the provided function addEdge(x,y,c) which
		adds c number of edges between x and y.

		isEulerian(int n, int *start, int *end) returns:
		   0  if the graph is not Eulerian
		   1  if the graph has a Euler cycle
		   2  if the graph a path, from start to end
		with n being the number of nodes in the graph
		
		For more information about Euler cycles and 
		Euler paths, see the Notes section.
		
   Complexity:  O(N) where N is the number of edges
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Jan 8, 2003
                Mar 13, 2003 - Update to handle vertices with no 
		               edges
   References:  
   -----------------------------------------------------------------
   Reliability: 2 (Problem B: Floor    - Set from 2003 Jan 04)
                  (Problem A: Door Man - Set from 2003 Mar 13)
   Notes:       - Indexing of nodes MUST be from [0...n-1], since
                  the connectivity is checked using node 0.
                - buildPath modifies the original graph g[][].
		  Uncomment the marked regions to keep a copy of
		  the graph in g2[][].  This also allows for
		  multiple calls to buildPath for the same input
		  graph
		- A Euler cycle in an undirected graph is a cycle
		  which travels along every edge of the graph, 
		  with the first node being the same as the last
		  node
		- A Euler path in an undirected graph is a path
		  which travels along every edge of the graph,
		  but the first node does not necessarily need
		  to be identical to the last node
		- A graph has a Euler cycle if it is connected,
		  and all nodes have even degree.  If the graph
		  is connected, and only two nodes have odd 
		  degree a Euler path exists starting and ending
		  from those two odd-degree nodes
*/

#include <stdio.h>
#include <string.h>

#define MAXN 105     /* Number of nodes */
#define MAXM 505     /* Maximum number of edges */

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define DEC(a,b) g[a][b]--;g[b][a]--;deg[a]--;deg[b]--

int sets[MAXN], deg[MAXN];
int g[MAXN][MAXN];
int seq[MAXM], seqsize;
/* Uncomment if you need copy of graph
   int g2[MAXN][MAXN], deg2[MAXN];
*/

int getRoot(int x){
  if(sets[x] < 0) return x;
  return sets[x] = getRoot(sets[x]);
}

void Union(int a, int b){
  int ra = getRoot(a), rb = getRoot(b);
  
  if(ra != rb){
    sets[ra] += sets[rb];
    sets[rb] = ra;
  }
}

void Init(){
  memset(sets, -1, sizeof(sets));
  memset(g, 0, sizeof(g));
  memset(deg, 0, sizeof(deg));
}

void addEdge(int x, int y, int count){
  g[x][y] += count; deg[x] += count;
  g[y][x] += count; deg[y] += count;
  Union(x,y);
}

int isEulerian(int n, int *start, int *end){
  int odd = 0, i, count = 0, x;
  
  /* Check if graph is connected.  If all vertices
     are guaranteed to be used then use this:
     
     if(sets[getRoot(0)] != -n) return 0;

     Otherwise, count only vertices used like this: */ 
  for(i = 0; i < n; i++)
    if(deg[i]){ 
      x = i; count++;
    }
  if(sets[getRoot(x)] != -count) return 0;
  for(i = 0; i < n; i++){
    if(deg[i]%2){
      odd++;   
      if(odd == 1) *start = i;
      else if(odd == 2) *end = i;
      else return 0;
    }
  }
  return odd ? 2 : 1;
}

void getPath(int n, int start, int end){
  int temp[MAXM], tsize = 1, i, j;

  temp[0] = start;
  while(1){
    j = temp[tsize-1];
    for(i = 0; i < n; i++){
      if(i == end) continue;
      if(g[i][j]){
	temp[tsize++] = i;
	DEC(i,j);
	break;
      }
    }
    if(i == n){
      if(g[end][j]){
	temp[tsize++] = end;
	DEC(j,end);
      }
      break;
    }
  } 
  for(i = 0; i < tsize; i++)
    if(!deg[temp[i]]) seq[seqsize++] = temp[i];
    else getPath(n, temp[i], temp[i]);
}

void buildPath(int n, int start, int end){
  seqsize = 0;
  /* Uncomment if you need copy of graph
     memcpy(g, g2, sizeof(g));
     memcpy(deg, deg2, sizeof(deg));
  */
  getPath(n, start, end);
}

int main(){
  int i, x,y,start,end, n, m;

  while(scanf("%d %d", &n, &m) == 2){
    Init();    
    for(i = 0; i < m; i++){
      scanf("%d %d", &x, &y);
      addEdge(x,y,1);
    }
    /* Uncomment if you need copy of graph
       memcpy(g2, g, sizeof(g2));
       memcpy(deg2, deg, sizeof(deg2));
    */
    switch(isEulerian(n, &start, &end)){
    case 0:
      printf("Graph is not Eulerian\n"); break;
    case 1: 
      printf("Graph has an Eulerian Cycle\n");
      buildPath(n, 0, 0);
      for(i = 0; i < seqsize; i++) printf("%d ", seq[i]);
      printf("\n"); break;
    case 2:
      printf("Graph has an Eulerian path from %d to %d\n", start, end); 
      buildPath(n,start,end);
      for(i = 0; i < seqsize; i++) printf("%d ", seq[i]);
      printf("\n"); break;
    }
  }
  return 0;
}
