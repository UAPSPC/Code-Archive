/* Graph_Theory: Maximum Flow in a directed graph
   =================================================================
   Description: Given a directed graph G, a source node, and a sink
                node, computes the maximum flow from source to sink,
		and calculates the flow along each edge.  
		
		In addition, the array S[] is marked to indicate 
		which side of the cut each vertex is on.  
		   S[i] = 1   means vertex i is on source side
		   S[i] = 0   means vertex i is on sink side
		An edge u->v with S[u] == 1 and S[v] == 0 is an
		edge of the minimum cut.

		Usage:
		1. Clear graph as shown in main()
		2. Add edges u->v by calling addEdge(u,v,cap)
		3. maxflow(n, source, sink) returns maxflow
		4. getEdge(u, v) returns a pointer to the edge
		   u->v, NULL if this edge does not exist
		
   Complexity:  O(|V|^2*|E|) (Rough approximation)
   -----------------------------------------------------------------
   Author:      Matthew McNaughton, Gilbert Lee
   Date:        Mar 10, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 2 Spain 10330 - Power Transmission 
                  Spain 104?? - Sabotage

   Notes:       - Multiple edges from u to v may be added.  They
                  are converted into a single edge with a capacity
		  equal to their sum
		- Vertices are assumed to be numbered from 0..n-1
		- The graph is stored as an adjaceny list in "g"
		  The vector<Edge> g[u] contains the edges adj.
		  to the vertex u.
		- Basic idea is performing a BFS from the source
		  to find an augmenting path -> a path through 
		  which flow may be increased.  When there are no
		  more such paths, a maximum flow/minimum cut has
		  been found.
*/

#include <stdio.h>
#include <vector>

using namespace std;

#define MAXN 200

typedef struct{
  int v, cap, flow;
} Edge;

vector<Edge> g[MAXN];
int pred[MAXN], maxcap[MAXN], S[MAXN];

void addEdge(int u, int v, int cap){
  size_t i; Edge e;

  for(i = 0; i < g[u].size(); i++)    /* Add cap if edge exists */
    if(g[u][i].v == v){
      g[u][i].cap += cap;
      return;
    }

  e.v = v; e.cap = cap; e.flow = 0;  
  g[u].push_back(e);                 /* Add edge u->v */
  
  for(i = 0; i < g[v].size(); i++)   /* Add dummy reverse edge */
    if(g[v][i].v == u) return;
  
  e.v = u; e.cap = 0;
  g[v].push_back(e);
}

Edge *getEdge(int u, int v){
  for(size_t i = 0; i < g[u].size(); i++)
    if(g[u][i].v == v) return &g[u][i];
  return 0;
}

int maxflow(int n, int source, int sink){
  vector<int> q; int i, v, flow, inc;
  size_t j; Edge *e1, *e2;

  for(i = 0; i < n; i++)
    for(j = 0; j < g[i].size(); j++)
      g[i][j].flow = 0;                 /* Clear all flows */
  
  flow = 0;

  while(1){                 /* BFS to find augmenting path */
    memset(S, 0, sizeof(S));
    S[source] = 1;
    q.clear(); q.push_back(source);
    for(i = 0; i < (int)q.size(); i++){
      v = q[i];
      if(v == sink) break;
      for(j = 0; j < g[v].size(); j++){
	Edge e = g[v][j];
	if(S[e.v]) continue;
	if(e.cap && e.flow < e.cap){
	  q.push_back(e.v); S[e.v] = 1; pred[e.v] = v;
	  maxcap[e.v] = e.cap - e.flow;
	} else {
	  e1 = getEdge(e.v, v);
	  if(e1 && e1->cap && e1->flow > 0){
	    q.push_back(e.v); S[e.v] = 1; pred[e.v] = v;
	    maxcap[e.v] = e1->flow;
	  }
	}
      }
    }
    if(v != sink) break;  /* No more augmenting paths */
    
    /* Calculate flow */
    for(inc = INT_MAX, v = sink; v != source; v = pred[v])
      inc = min(inc, maxcap[v]);
    flow += inc;
    
    /* Update flow */
    for(v = sink; v != source; v = pred[v]){
      e1 = getEdge(pred[v], v);
      e2 = getEdge(v, pred[v]);
      
      if(e1 && e1->cap)      e1->flow += inc;
      else if(e2 && e2->cap) e2->flow -= inc;

      if(e1 && e2 && e1->flow && e2->flow){
	if(e1->flow > e2->flow){
	  e1->flow -= e2->flow;
	  e2->flow = 0;
	} else {
	  e2->flow -= e1->flow;
	  e1->flow = 0;
	}
      }
    }
  }
  return flow;
}

int main(){
  int n;       /* Number of vertices */
  int m;       /* Number of edges */
  int source;  /* Source of the flow */
  int sink;    /* Sink of the flow */
  int flow;    /* The value of the max flow */
  int i, u, v, cap;
  
  /* n = # of vertices,  m = # of edges */
  while(scanf("%d %d %d %d", &n, &m, &source, &sink) == 4){
    
    /* Clear graph */
    for(i = 0; i < n; i++) g[i].clear();    
    
    /* Read in m edges */
    for(i = 0; i < m; i++){
      scanf("%d %d %d", &u, &v, &cap);
      addEdge(u,v,cap);
    }
    
    flow = maxflow(n, source, sink);
    
    printf("The maximum flow: %d\n", flow);
    printf("Min-cut edges:\n");
    for(i = 0; i < n; i++)
      if(S[i] == 1){
	for(size_t j = 0; j < g[i].size(); j++)
	  if(S[g[i][j].v] == 0)
	    printf("(%d->%d)\n", i, g[i][j].v);
      }
    printf("Flow values:\n");
    for(i = 0; i < n; i++)
      for(size_t j = 0; j < g[i].size(); j++)
	printf("(%d->%d): %d/%d\n", i, g[i][j].v, g[i][j].flow, g[i][j].cap);
  }
  return 0;
}


