/* Graph_Theory: Maximum Flow in a directed graph
   =================================================================
   Description: Given a directed graph G, a source node (s), and a
                sink node (t), computes the maximum flow from source
		to sink, and calculates the flow along each edge.  
		
   Complexity:  O(|V|^3)
   -----------------------------------------------------------------
   Author:      Jason Klaus
   Date:        November 12, 2003
   References:  CLRS p690 - Relabel-to-front
   -----------------------------------------------------------------
   Reliability: 2 Spain 10330 - Power Transmission 
                  Oct 28, 2003 - Problem G
		        (2003 Southeastern European Regional Contest)

   Notes:     - Faster then the original maximum flow code for graphs
                with lots of edges.
              - Multiple edges from u to v may be added.  They are
	        converted into a single edge with a capacity equal to
    	        their sum
  	      - Vertices are assumed to be numbered from 0..n-1
              - The graph is supplied as the number of nodes (n), the
	        zero-based indexes of the source (s) and the sink (t),
		and a vector of edges u->v with capacity c (M).
*/

#include <cstdio>
#include <vector>
#include <list>

using namespace std;

#define MAXN 200

//Edge u->v with capacity c
struct Edge {
  int u, v, c;
};

int F[MAXN][MAXN]; //Flow of the graph

int maxFlow(int n, int s, int t, vector<Edge> &M)
{
  int u, v, c, oh, min, df, flow, H[n], E[n], T[n], C[n][n];
  vector<Edge>::iterator m;
  list<int> N;
  list<int>::iterator cur;
  vector<int> R[n];
  vector<int>::iterator r;

  for (u = 0; u < n; u++) {
    E[u] = H[u] = T[u] = 0;
    R[u].clear();
    for (v = 0; v < n; v++)
      C[u][v] = F[u][v] = 0;
  }

  for (m = M.begin(); m != M.end(); m++) {
    u = m->u;
    v = m->v;
    c = m->c;
    if (c && !C[u][v] && !C[v][u]) {
      R[u].push_back(v);
      R[v].push_back(u);
    }
    C[u][v] += c;
  }

  H[s] = n;

  for (r = R[s].begin(); r != R[s].end(); r++) {
    v = *r;
    F[s][v] =  C[s][v];
    F[v][s] = -C[s][v];
    E[v]  = C[s][v];
    E[s] -= C[s][v];
  }

  N.clear();
  for (u = 0; u < n; u++)
    if ((u != s) && (u != t))
      N.push_back(u);

  for (cur = N.begin(); cur != N.end(); cur++) {
    u = *cur;
    oh = H[u];
    
    while (E[u] > 0)
      if (T[u] >= (int)R[u].size()) {
	min = 10000000;
	for (r = R[u].begin(); r != R[u].end(); r++) {
	  v = *r;
	  if ((C[u][v] - F[u][v] > 0) && (H[v] < min))
	    min = H[v];
	}
	H[u] = 1 + min;
	T[u] = 0;
      }
      else {
	v = R[u][T[u]];
      
	if ((C[u][v] - F[u][v] > 0) && (H[u] == H[v]+1)) {
	  df = C[u][v] - F[u][v];
	  if (df > E[u])
	    df = E[u];

	  F[u][v] += df;
	  F[v][u]  = -F[u][v];
	  E[u] -= df;
	  E[v] += df;
	}
	else
	  T[u]++;
      }

    if (H[u] > oh)
      N.splice(N.begin(), N, cur);
  }
  
  flow = 0;

  for (r = R[s].begin(); r != R[s].end(); r++)
    flow += F[s][*r];

  return flow;
}


int main()
{
  int n, m, s, t, f;
  Edge e;
  vector<Edge> E;
  
  while (scanf("%d %d %d %d", &n, &s, &t, &m) == 4) {
    E.clear();
    while (m--) {
      scanf("%d %d %d", &e.u, &e.v, &e.c);
      E.push_back(e);
    }

    f = maxFlow(n, s, t, E);

    printf("Maximum Flow: %d\n", f);
  }

  return 0;
}
