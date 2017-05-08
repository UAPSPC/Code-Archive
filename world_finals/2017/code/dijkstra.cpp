struct Edge {
  int u, v, w;
  Edge (int u, int v, int w) : u(u), v(v), w(w) {}
  bool operator<(const Edge& rhs) const { return w > rhs.w; }
};
typedef vector<Edge> VE;
vector<VE> graph;
VE pre;
void dijkstra(int s) {
  priority_queue<Edge> pq;
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
