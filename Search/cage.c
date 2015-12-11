/* Search: (r-g)-Cage search template
   =================================================================
   Description: This is a template for finding minimum order r-g
                cages.

		A r-g cage is a graph where each vertex has degree r
		and the smallest cycle in the graph is of size g.
		The minimum order cage is the one with the fewest
		vertices.

		The search builds a necessary tree, then searchs on
		the remaining vertices.  The final adjaceny list of
		the cage is stored in adj[][], where where adj[i][j]
		stores the jth neighbor of vertex i.
		
   Complexity:  O(exponential)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        March 12, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       r-3 cages are easy to find - complete cliques
                r-4 cages are also easy to find.
		Other cage values that run fast: 
		3-(5,6,7,8),  4-(5,6)
		
*/

#include <stdio.h>
#include <string.h>

#define MAXR  10          /* MAXR = max. degree of each vertex */
#define MAXG 100          /* MAXG = max. girth of cage         */
#define MAXN 100          /* MAXN = max. # of vertices in cage */

int adj[MAXN][MAXR];      /* Adj list of vertex i              */
int deg[MAXN];            /* Current degree of vertex i        */

int r, g, n;              /* Cage parameters                   */

#define max(x,y)          (((x)>(y))?(x):(y))
#define addEdge(x,y)      adj[x][deg[x]++]=y;adj[y][deg[y]++]=x
#define remEdge(x,y)      deg[x]--;deg[y]--

void FillTree(int root, int depth){
  int i;
  for(i = 0; i < r-1; i++){
    n++;
    addEdge(root, n);
    if(depth > 1) FillTree(n, depth-1);
  }
}

/* Builds the tree required by the lower bound */
void BuildTree(){
  int i; 
  
  n = 1;
  memset(deg, 0, sizeof(deg));         /* Clear graph          */
  if(g % 2){                           /* Odd girth            */
    for(i = 0; i < r; i++, n++){
      addEdge(0,n);
      if(g/2-1) FillTree(n,g/2-1);
    }
  } else {                             /* Even girth           */
    addEdge(0,n);
    FillTree(n, g/2-1);
    n++;
    for(i = 1; i < r; i++, n++){
      addEdge(0,n);
      if(g/2-2) FillTree(n,g/2-2);
    }
  }
}

void PrintCage(){
  int i, j;

  printf("Found (%d,%d)-cage of size %d\n", r, g, n);
  for(i = 0; i < n; i++){
    printf("%d:", i);
    for(j = 0; j < r; j++) printf(" %d", adj[i][j]);
    printf("\n");
    
    /* Make sure each vertex has degree r */
    if(deg[i] != r) printf("ERROR!\n");
  }
}

/* Determines if adding the edge x->y would create a (<g)-cycle */
int Cycle(int x, int y){
  int q[MAXN], tail = 1, head, node, next, i;
  char dist[MAXN];

  memset(dist, -1, sizeof(dist));
  q[0] = y;
  dist[y] = 0;
  for(head = 0, tail = 1; head != tail; head++){
    node = q[head];
    for(i = 0; i < deg[node]; i++){
      next = adj[node][i];
      if(dist[next] == -1){
	if(next == x) return 1;
	dist[next] = dist[node]+1;
	if(dist[node] < g-3) q[tail++] = next;
      }
    }
  }
  return 0;
}

int Search(int node){
  int i;
  if(node == n){                       /* Found cage */
    PrintCage();
    return 1;
  }

  /* Check if vertex has full degree */
  if(deg[node] == r) return Search(node+1);  

  /* Determine the next possibile candidate */
  if(deg[node] == 0) i = node+1;
  else i = max(node+1, adj[node][deg[node]-1]+1);
  
  /* Try connecting this vertex */
  for(; i < n; i++){
    if(deg[i] == r || Cycle(node, i)) continue;
    addEdge(node, i);
    if(Search(node)) return 1;
    remEdge(node, i);
  }
  return 0;
}

int main(){
  printf("Enter r and g: ");
  while(scanf("%d %d", &r, &g) == 2){  /* Read cage parameters */
    if(r < 2 || r > MAXR || g < 3 || g > MAXG){
      printf("Invalid parameters.\n");
      continue;
    }
    
    BuildTree();                      /* Builds the tree first */
    
    while(1){                         /* Search for the cage   */
      printf("Searching for cage of size %d\n", n);
      if(Search(0)) break;
      n++;
    }
  }
  return 0;
}
