// Input (zerobased):
//       g[n] should be the adjacency list of the graph
//       g[i] is a vector of int
// Output of cut_ver():
//       cut_vertex is a vector of int
//       comp[comp_size] contains the 2 connected components
//       comp[i] is a vector of int
const int maxn = 1000;
vector<int> g[maxn];
int d[maxn], mark[maxn], mark0[maxn], jad[maxn];
int n;
vector<int> cut_vertex;
// for components only
vector<int> comp[maxn];
int comp_size;
vector<int> comp_stack;
void dfs(int x, int level) {
  mark[x] = 1;
  // for components only
  comp_stack.push_back(x);
  for(int u : g[x]) {
    if(!mark[u]) {
      jad[u] = d[u] = d[x] + 1;
      dfs(u, level + 1);
      jad[x] = std::min(jad[u], jad[x]);
      if(jad[u] >= d[x] && d[x]) {
        cut_vertex.push_back(x);
        // for components only
        while(comp_stack.back() != u) {
          comp[comp_size].push_back(comp_stack.back());
          comp_stack.pop_back();
        }
        comp[comp_size].push_back(u);
        comp_stack.pop_back();
        comp[comp_size++].push_back(x);
      }
    } else if(d[u] != d[x] - 1)
      jad[x] = std::min(d[u], jad[x]);
  }
  // for components only
  if(level == 0) {
    while(comp_stack.size() > 0) {
      comp[comp_size].push_back(comp_stack.back());
      comp_stack.pop_back();
    }
    comp_size++;
  }
}
int dfs0(int x) {
  mark0[x] = 1;
  for(int to : g[x])
    if(!mark0[to]) return dfs0(to);
  return x;
}
void cut_ver() {
  memset(mark, 0, sizeof mark);
  memset(mark0, 0, sizeof mark0);
  memset(d, 0, sizeof d);
  memset(jad, 0, sizeof jad);
  // for components only
  for(int i = 0; i < maxn; i++) comp[i].clear();
  comp_stack.clear();
  comp_size = 0;
  cut_vertex.clear();
  for(int i = 0; i < n; i++)
    if(!mark[i]) dfs(dfs0(i), 0);
}
