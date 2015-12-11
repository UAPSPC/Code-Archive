/* Graph Theory: Bellman-Ford Algorithm - negative weigth cycles
   =================================================================
   Description: Given a directed graph G, expressed in terms of its
                edges, and a source vertex s, Bellman-Ford returns
		whether or not it is possible to encounter a cycle
		of negative weight.  If such a cycle exists, it
		returns 0, otherwise 1.

		If no negative-weight cycle exists, then dist[v]
		contains the shortest distance from source s to 
		v.
   
   Complexity:  O(NM) where N is # of nodes, M is # of edges
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 20, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 1 successful use (Sept 2002)
                (Spain 558)
   Notes:       INF must be set to a value larger than any edge
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define INF INT_MAX
#define MAXNODES 1005
#define MAXEDGES 2005

typedef struct{
  int u,v,w;
} Edge;

int dist[MAXNODES], pred[MAXNODES];
Edge edge[MAXEDGES];
int n, m;

int BellmanFord(int source){
  int i, j;
  
  for(i = 0; i < n; i++){
    dist[i] = INF;
    pred[i] = -1;
  }
  dist[source] = 0;
  
  for(i = 0; i < n-1; i++)
    for(j = 0; j < m; j++){
      if(dist[edge[j].v] > dist[edge[j].u]+edge[j].w){
	dist[edge[j].v] = dist[edge[j].u]+edge[j].w;
	pred[edge[j].v] = edge[j].u;
      }
    }
  
  for(j = 0; j < m; j++){
    if(dist[edge[j].v] > dist[edge[j].u]+edge[j].w) return 0;
  }
  return 1;
}

int main(){
  int tnum, i;
  
  scanf("%d", &tnum);
  while(tnum--){
    scanf("%d %d", &n, &m);
    for(i = 0; i < m; i++){
      scanf("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].w);
    }
    if(BellmanFord(0)) printf("not ");
    printf("possible\n");
  }
  return 0;
}
