// Input:
//    n: size of part1, m: size of part2
//    a[i]: neighbours of i-th vertex of part1
//    b[i]: neighbours of i-th vertex of part2
const int maxn = 2020, maxm = 2020;
int n, m;
vector<int> a[maxn], b[maxm];
int matched[maxn], mark[maxm], mate[maxm];
int dfs(int v) {
  if(v < 0) return 1;
  for(int i = 0; i < a[v].size(); ++i)
    if(!mark[a[v][i]]++ && dfs(mate[a[v][i]])) return matched[mate[a[v][i]] = v] = 1;
  return 0;
}
int set_mark() {
  memset(matched, 0, sizeof matched);
  memset(mate, -1, sizeof mate);
  memset(mark, 0, sizeof mark);
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < a[i].size(); ++j)
      if(mate[a[i][j]] < 0) {
        matched[mate[a[i][j]] = i] = 1;
        break;
      }
  for(int i = 0; i < n; ++i)
    if(!matched[i] && dfs(i)) memset(mark, 0, sizeof mark);
  for(int i = 0; i < n; ++i)
    if(!matched[i]) dfs(i);
}
// res.size(): size of matching
// res[i]: i-th edge of matching
// res[i].first is in part1, res[i].second is in part2
void matching(vector<pair<int, int>> &res) {
  set_mark();
  res.clear();
  for(int i = 0; i < m; ++i)
    if(mate[i] >= 0) res.push_back(pair<int, int>(mate[i], i));
}
// p1: vertices in part1, p2: vertices in part2
// union of p1 and p2 cover the edges of the graph
void vertex_cover(vector<int> &p1, vector<int> &p2) {
  set_mark();
  p1.clear();
  p2.clear();
  for(int i = 0; i < m; ++i)
    if(mate[i] >= 0)
      if(mark[i])
        p2.push_back(i);
      else
        p1.push_back(mate[i]);
}
// p1: vertices in part1, p2: vertices in part2
// union of p1 and p2 is the largest disjoint set of the graph
void disjoint_set(vector<int> &p1, vector<int> &p2) {
  set_mark();
  p1.clear();
  p2.clear();
  for(int i = 0; i < m; ++i)
    if(mate[i] >= 0 && mark[i])
      p1.push_back(mate[i]);
    else
      p2.push_back(i);
  for(int i = 0; i < n; ++i)
    if(!matched[i]) p1.push_back(i);
}
// edges in res cover the vertices of the graph
// res[i].first is in part1, res[i].second is in part2
void edge_cover(vector<pair<int, int>> &res) {
  set_mark();
  res.clear();
  for(int i = 0; i < m; ++i)
    if(mate[i] >= 0)
      res.push_back(pair<int, int>(mate[i], i));
    else if(b[i].size())
      res.push_back(pair<int, int>(b[i][0], i));
  for(int i = 0; i < n; ++i)
    if(!matched[i] && a[i].size()) res.push_back(pair<int, int>(i, a[i][0]));
}
