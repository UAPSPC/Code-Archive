/* Graph Theory: Maximum Flow with Lower bounds on edges 
   =================================================================
   Description: Calculates the maximum flow along a network with 
                both upper and lower capacities on edges, from a 
		source node, to a sink node.  As a side effect the
		global array S[] is marked with a 1 if the ith 
		vertex is on the source side of the cut.

		The function maxflow_lb returns the maximum flow
		if one exists, and -1 if a valid flow does not
		exist.

		1. Clear graph (shown below)
		2. Add edges using addEdge(u,v,low,up,g)
		3. Call maxflow_lb

   Complexity:  O(|V|^2*|E|) (Rough approximation)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        March 18, 2003
   References:  Graph Algorithms - Shimon Even  Chapter 5.3
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       - This implementation allows for multiple edges 
                  between a pair of vertices
		- the lower bound is assumed to be less than or
		  equal to the upper bound, and greater or 
		  equal to zero
		- No valid flow exists if the minimum flow
		  requirements for some edge can not be met.
		- How it works:
		  Creates a new auxilary graph with a new source and
		  sink, and assigns upper capacities, while leaving
		  lower bounds 0.  Finds a maximum flow on the new
		  graph, and then checks if it is valid.  Moves the
		  flow over to the original graph, then perform
		  a maximum flow on the original graph
*/

#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

#define MAXN 500

typedef struct{
  int v, low, up, flow;
} Edge;

vector<Edge> g[MAXN];
vector<Edge> aux[MAXN];
int pred[MAXN], maxcap[MAXN], S[MAXN];

void addEdge(int u, int v, int low, int up, vector<Edge> G[]){
  Edge e; 
  e.flow = 0; e.v = v; e.low = low; e.up = up; 
  G[u].push_back(e);
  for(size_t i = 0; i < G[v].size(); i++) if(G[v][i].v == u) return;
  e.v = u;  e.low = e.up = 0;
  G[v].push_back(e);
}

int inc_flow(int n, int src, int sink, vector<Edge> G[]){
  size_t i, j, k; Edge e, e1; int flow, v, inc, found;
  vector<int> q;

  flow = 0;
  while(1){
    memset(S, 0, sizeof(S));
    S[src] = 1;
    q.clear(); q.push_back(src);
    for(i = 0; i < q.size(); i++){
      v = q[i]; if(v == sink) break;
      for(j = 0; j < G[v].size(); j++){
	e = G[v][j]; 
	if(S[e.v]) continue;
	if(e.flow < e.up){
	  q.push_back(e.v); S[e.v] = 1; pred[e.v] = v;
	  maxcap[e.v] = e.up-e.flow;
	} else {
	  for(k = 0; k < G[e.v].size(); k++){
	    e1 = G[e.v][k];
	    if(e1.v == v && e1.flow > e1.low){
	      q.push_back(e.v); S[e.v] = 1; pred[e.v] = v;
	      maxcap[e.v] = e1.flow - e1.low;
	      break;
	    }
	  }
	}
      }
    }
    if(v != sink) break;

    for(inc = INT_MAX, v = sink; v != src; v = pred[v])
      inc = min(inc, maxcap[v]);
    flow += inc;

    for(v = sink; v != src; v = pred[v]){
      found = 0;
      for(i = 0; i < G[pred[v]].size(); i++){
	e = G[pred[v]][i];
	if(e.v == v && e.flow + inc <= e.up){
	  found = 1;
	  G[pred[v]][i].flow += inc;
	  break;
	}
      }
      if(!found){
	for(i = 0; i < G[v].size(); i++){
	  e = G[v][i];
	  if(e.v == pred[v] && e.flow - inc >= e.low){
	    found = 1;
	    G[v][i].flow -= inc;
	    break;
	  }
	}
      }
      assert(found);
    }
  }
  return flow;
}

int maxflow_lb(int n, int src, int sink){
  int in[MAXN]={0}, out[MAXN]={0}, total = 0, flow, i;
  int nsrc = n, nsink = n+1; size_t j; 
  
  for(i = 0; i < n+2; i++) aux[i].clear();
  
  /* Join each vertex to new src and sink with modified upper bounds */
  for(i = 0; i < n; i++) for(j = 0; j < g[i].size(); j++){
    out[i] += g[i][j].low;
    in[g[i][j].v] += g[i][j].low;
  }

  for(i = 0; i < n; i++){
    total += out[i];
    addEdge(nsrc, i, 0, in[i], aux);  
    addEdge(i, nsink, 0, out[i], aux);
  }
  
  /* Copy old edges in with modified capacities */
  for(i = 0; i < n; i++) for(j = 0; j < g[i].size(); j++)
    addEdge(i, g[i][j].v, 0, g[i][j].up-g[i][j].low, aux);
  
  /* Add high capacity edges between old src and sink */
  addEdge(sink, src, 0, INT_MAX, aux);  
  addEdge(src, sink, 0, INT_MAX, aux);  

  /* Determine if a valid flow exists */
  if(inc_flow(n+2, nsrc, nsink, aux) != total) return -1;

  /* Move flow in auxillary graph into the original graph */
  for(i = 0; i < n; i++) for(j = 0; j < g[i].size(); j++){
    Edge e = g[i][j];
    if(e.up){
      for(size_t k = 0; k < aux[i].size(); k++)
	if(aux[i][k].v == e.v && e.up-e.low == aux[i][k].up){
	  g[i][j].flow = aux[i][k].flow + g[i][j].low;
	  aux[i][k].v = -1;
	  break;
	}
    }
  }

  inc_flow(n, src, sink, g);  /* Increment the flow */

  for(flow = j = 0; j < g[src].size(); j++) /* Calc. max flow */
    flow += g[src][j].flow;
  return flow;
}

int main(){
  int n, m, src, sink, u, low, up, v, i, flow;

  while(scanf("%d %d %d %d", &n, &m, &src, &sink) == 4){

    /* 1. Clear graph */
    for(i = 0; i < n; i++) g[i].clear();
    
    /* 2. Add edges */
    for(i = 0; i < m; i++){
      scanf("%d %d %d %d", &u, &v, &low, &up);
      addEdge(u, v, low, up, g);
    }
	  
    /* 3. Call maxflow_lb */
    flow = maxflow_lb(n, src, sink);
   
    /* 4. Print off edges */
    if(flow == -1){
      printf("No possible flow\n");
    } else {
      printf("Valid flow exists %d\n", flow);
      for(i = 0; i < n; i++) for(size_t j = 0; j < g[i].size(); j++){
	Edge e = g[i][j];
	if(e.up) printf("Edge %d->%d (%d,%d) Flow:%d %s\n",
			i, e.v, e.low, e.up, e.flow,
			S[i]&&!S[e.v] ? "CUT" : "NOT");
      }
    }
  }
  return 0;
}
