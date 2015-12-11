/* Graph Theory: Articulation Points in a Graph (Adj List version)
   =================================================================
   Description: An articulation point in a undirected graph is a
                vertex which disconnects the graph when removed.
		This routine takes a graph represented by an
		adjacency list, and finds all articulation points in
		the graph.
		
		If b is an articulation point, then there exists
		two distinct vertices a and c, such that b is on
		EVERY path from a to c.
		
		- An array called ART[] contains 1 if node i is an
  		  articulation point and 0 otherwise.
		- use addEdge(int x, int y) to create a undirected
		  edge between node x and y
		- use clearList() to clear out all elements of the 
		  adjacency list

   Complexity:  O(V+E)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Oct 23, 2002 (mod Jan 16, 2003)
   References:  Algorithms in C, Robert Sedgewick pg.440-441
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       - Nodes must be indexed from 0..N-1.
                - Edges should not be added more than once to
		  prevent array overflow
		- On graphs which are not connected, nodes which 
		  disconnect components they are part of are 
		  considered articulation points.
*/

#include <stdio.h>
#include <string.h>

#define MAXN 200
#define min(a,b) (((a)<(b))?(a):(b))

typedef struct{
  int deg;
  int adj[MAXN];
} Node;

Node alist[MAXN];
char ART[MAXN], val[MAXN];
int id;

void addEdge(int x, int y){
  alist[x].adj[alist[x].deg++] = y;
  alist[y].adj[alist[y].deg++] = x;
}

void clearList(){
  memset(alist, 0, sizeof(alist));
}

int visit(int x, int root){
  int i, y, m, res, child = 0;
  
  res = val[x] = ++id;
  for(i = 0; i < alist[x].deg; i++){
    y = alist[x].adj[i];
    if(!val[y]){
      if(root && ++child > 1) ART[x] = 1;
      m = visit(y, 0);
      res = min(res, m);
      if(m >= val[x] && !root) ART[x] = 1;
    } else {
      res = min(val[y], res);
    }
  }
  return res;
}

void articulate(int n){
  int i;
  
  memset(ART, 0, sizeof(ART));
  memset(val, 0, sizeof(val));
  for(id = i = 0; i < n; i++)
    if(!val[i]) visit(i, 1);
}

int main(){
  int i, n, m, x, y, found;
  
  /* Read in number of vertices, number of edges */
  while(scanf("%d %d", &n, &m) == 2){

    /* Read in edge between node x and node y */
    for(i = 0; i < m; i++){
      scanf("%d %d", &x, &y);
      addEdge(x,y);
    }
    
    /* Find articulation points */
    articulate(n);
    
    for(found = i = 0; i < n; i++)
      if(ART[i]){
	printf("Node %d is an articulation point\n", i);
	found = 1;
      }
    if(!found) printf("No articulation points\n");
    clearList();
  }
  return 0;
}
