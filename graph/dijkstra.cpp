/*

  Dijkstra's algorithm to compute the shortest path to every vertex in an
  edge-weighted graph from a given start vertex. The weights cannot be negative
  (it may not work if they are).

  The graph is an adjacency list of edges. Each edge in graph[u] is from u
    to the outgoing neighbour v, and has weight w.

  Simply call dijkstra(start_node).

  Can recover a shortest path from start_node to any other node v by
    first calling dijkstra(start_node) and then get_path(v, path)
    where path is a vector of edges that will be the path.

  Only need to call dijkstra(start_node) once, and then can compute
    get_path(v, path) for many different v.

  Running time:
    dijkstra(start_node) : O( m * log(m) ) where m = # edges
    get_path(v, path) : O(n) where n = # nodes
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int u, v;
  int w;
  Edge (int uu, int vv, int ww) : u(uu), v(vv), w(ww) {}

  bool operator<(const Edge& rhs) const { return w > rhs.w; }
};

typedef vector<Edge> VE;

vector<VE> graph;
VE pre;

void dijkstra(int s) {
  priority_queue< Edge > pq;

  pre.assign(graph.size(), Edge(-1, -1, -1));

  pq.push(Edge(-2, s, 0));

  while (!pq.empty()) {
    Edge curr = pq.top();
    pq.pop();

    if (pre[curr.v].v != -1) continue;

    pre[curr.v] = curr;

    for (auto e : graph[curr.v])
      pq.push(Edge(e.u, e.v, e.w + curr.w));
  }
}

/*
  Reconstruct a shortest path from node s to v, stored as an array of edges.

  Must have called dijkstra(s) before calling this.

  Returns the length of this path, -1 if v cannot be reached by s.
  
*/
int get_path(int v, VE& path) {
  if (pre[v].v == -1) return -1; // no path

  path.clear();
  
  int len = pre[v].w;
  while (pre[v].u != -2) {
    path.push_back(Edge(pre[v].u, pre[v].v, pre[v].w - pre[pre[v].u].w));
    v = pre[v].u;
  }

  reverse(path.begin(), path.end());

  return len;
}

int main() {
  int n, m, s;
  cin >> n >> m >> s;
  graph.assign(n, VE());

  while (m--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back(Edge(u,v,w));
  }

  dijkstra(s);

  cout << endl;
  for (int i = 0; i < n; ++i) {
    VE path;
    int len = get_path(i, path);
    if (len == -1)
      cout << "No " << s << " - " << i << " path" << endl << endl;
    else {
      cout << "Shortest " << s << " - " << i << " distance = "
	   << len << endl;
      cout << "Path: " << s;
      for (auto e : path) cout << ' ' << e.v;
      cout << endl << endl;
    }
  }
  
  return 0;
}

