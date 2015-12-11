/* Graph Theory: Articulation Points & Bridges (adj list)
   ==========================================================
   Description: An articulation point in a graph is a vertex that
                will result in a connected graph being disconnected
		upon removal.  A bridge is an edge that will
		result in a connected graph being disconnected
		if it is severed.

		-array entry art[v] is true iff vertex v is an
		 articulation point

		-array entries bridge[i][0] and bridge[i][1] are
		 the endpoints of a bridge in the graph.  Note
		 that if bridge (u,v) is represented in the array,
		 then (v,u) is not.

		-variable bridges is the number of bridges in the graph

   Complexity O(V + E)
   -----------------------------------------------------------
   Author:     Zac Friggstad
   Date:       Jan 13, 2006
   References: "The Design & Analysis of Computer Algorithms"
               Aho, Hopcroft, Ullman
   -----------------------------------------------------------
   Reliability: 610 on Spain
   Notes: -index vertices from 0 to n-1
*/

#include <stdio.h>
#include <string.h>

#define MAX_N 200
#define min(a,b) (((a)<(b))?(a):(b))

typedef struct {
  int deg;
  int adj[MAX_N];
} Node;

Node alist[MAX_N];
bool art[MAX_N];
int df_num[MAX_N], low[MAX_N], father[MAX_N], count;
int bridge[MAX_N*MAX_N][2], bridges;

void add_edge(int v1, int v2) {
  alist[v1].adj[alist[v1].deg++] = v2;
  alist[v2].adj[alist[v2].deg++] = v1;
}

void add_bridge(int v1, int v2) {
  bridge[bridges][0] = v1;
  bridge[bridges][1] = v2;
  ++bridges;
}

void clear() {
  for (int i = 0; i < MAX_N; ++i) alist[i].deg = 0;
}

void search(int v, bool root) {
  int w, child = 0;

  low[v] = df_num[v] = count++;

  for (int i = 0; i < alist[v].deg; ++i) {
    w = alist[v].adj[i];

    if (df_num[w] == -1) {
      father[w] = v;
      ++child;
      search(w, false);
      if (low[w] > df_num[v]) add_bridge(v, w);
      if (low[w] >= df_num[v] && !root) art[v] = true;
      low[v] = min(low[v], low[w]);
    }
    else if (w != father[v]) {
      low[v] = min(low[v], df_num[w]);
    }
  }

  if (root && child > 1) art[v] = true;
}

void articulate(int n) {
  int child = 0;

  for (int i = 0; i < n; ++i) {
    art[i] = false;
    df_num[i] = -1;
    father[i] = -1;
  }

  count = bridges = 0;

  search(0, true);
}


int main() {
  int n, m, v1, v2, c = 0;

  while (true) {
    scanf("%d %d", &n, &m);

    if (!n && !m) break;

    clear();

    for (int i = 0; i < m; ++i) {
      scanf("%d %d", &v1, &v2);
      add_edge(v1 - 1, v2 - 1);
    }

    articulate(n);

    printf("Articulation Points:");
    for (int i = 0; i < n; ++i)
      if (art[i]) printf(" %d", i + 1);
    printf("\n");

    printf("Bridges:");
    for (int i = 0; i < bridges; ++i)
      printf(" (%d,%d)", bridge[i][0] + 1, bridge[i][1] + 1);
    printf("\n\n");
  }

  return 0;
}
      
