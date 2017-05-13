// find_flow returns max flow from s to t in an n-vertex graph.
// Use add_edge to add edges (directed/undirected) to the graph.
// Call clear_flow() before each testcase.
const int maxn = 1000;
int c[maxn][maxn];
vector<int> adj[maxn];
int par[maxn];
int dcount[maxn + maxn];
int dist[maxn];
void add_edge(int a, int b, int cap, int rev_cap = 0) {
  c[a][b] += cap;
  c[b][a] += rev_cap;
  adj[a].push_back(b);
  adj[b].push_back(a);
}
void clear_flow() {
  memset(c, 0, sizeof c);
  memset(dcount, 0, sizeof dcount);
  for(int i = 0; i < maxn; ++i) adj[i].clear();
}
int advance(int v) {
  for(int i = 0; i < adj[v].size(); ++i) {
    int w = adj[v][i];
    if(c[v][w] > 0 && dist[v] == dist[w] + 1) {
      par[w] = v;
      return w;
    }
  }
  return -1;
}
int retreat(int v) {
  int old = dist[v];
  --dcount[dist[v]];
  for(int i = 0; i < adj[v].size(); ++i) {
    int w = adj[v][i];
    if(c[v][w] > 0) dist[v] = min(dist[v], dist[w]);
  }
  ++dist[v];
  ++dcount[dist[v]];
  if(dcount[old] == 0) return -1;
  return par[v];
}
int augment(int s, int t) {
  int delta = c[par[t]][t];
  for(int v = t; v != s; v = par[v]) delta = min(delta, c[par[v]][v]);
  for(int v = t; v != s; v = par[v]) {
    c[par[v]][v] -= delta;
    c[v][par[v]] += delta;
  }
  return delta;
}
queue<int> q;
void bfs(int v) {
  memset(dist, -1, sizeof dist);
  while(!q.empty()) q.pop();
  q.push(v);
  dist[v] = 0;
  ++dcount[dist[v]];
  while(!q.empty()) {
    v = q.front();
    q.pop();
    for(int i = 0; i < adj[v].size(); ++i) {
      int w = adj[v][i];
      if(c[w][v] > 0 && dist[w] == -1) {
        dist[w] = dist[v] + 1;
        ++dcount[dist[w]];
        q.push(w);
      }
    }
  }
}
int find_flow(int n, int s, int t) {
  bfs(t);
  int v = s;
  par[s] = s;
  int ans = 0;
  while(v != -1 && dist[s] < n) {
    int newv = advance(v);
    if(newv != -1)
      v = newv;
    else
      v = retreat(v);
    if(v == t) {
      v = s;
      ans += augment(s, t);
    }
  }
  return ans;
}
