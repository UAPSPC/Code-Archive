/* Graph Theory: Minimum Spanning Tree (version 2)
   =================================================================
   Description: Returns the edges / weight of the minimum spanning
                tree, given the graph in terms of edges.

		Vertices are numbered 0..N-1.
   
   Complexity:  O(M lg M) where M is the number of edges
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Dec 06, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 1 (Spain 10034)
   Notes:       
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXN   1000
#define MAXM   1000000
#define EPS    1e-8
int n;

typedef struct{
  int u, v;     /* Edge between u, v with weight w */
  double w;      
} Edge;

int  sets[MAXN];
Edge edge[MAXM], treeedge[MAXN];
int numedge;

int cmp_Edge(Edge *a, Edge *b){
  if(fabs(a->w-b->w) < EPS) return 0;
  if(a->w < b->w) return -1;
  return 1;
}

int getRoot(int x){
  if(sets[x] < 0) return x;
  return sets[x] = getRoot(sets[x]);
}

void Union(int a, int b){
  int ra = getRoot(a);
  int rb = getRoot(b);
  if(ra != rb){
    sets[ra] += sets[rb];
    sets[rb] = ra;
  }
}

double mintree(){
  double weight = 0.0;
  int i, count;

  qsort(edge, numedge, sizeof(edge[0]), (void *)cmp_Edge);  
  for(i = count = 0; count < n-1; i++){
    if(getRoot(edge[i].u) != getRoot(edge[i].v)){
      Union(edge[i].u, edge[i].v);
      weight += edge[i].w;
      treeedge[count++] = edge[i];
    }
  }
  return weight;
}

int main(){
  int i;
  double weight;

  while(scanf("%d %d", &n, &numedge) == 2){
    memset(sets, -1, sizeof(sets));
    for(i = 0; i < numedge; i++){
      scanf("%d %d %lf", &edge[i].u, &edge[i].v, &edge[i].w);
    }
    weight = mintree();
    printf("Minimum cost tree = %f\n", weight);
    printf("Tree edges: \n");
    for(i = 0; i < n-1; i++){
      printf("%d %d %f\n", treeedge[i].u, treeedge[i].v, treeedge[i].w);
    }
  }
  return 0;
}
