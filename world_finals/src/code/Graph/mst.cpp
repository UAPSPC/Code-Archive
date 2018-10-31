#define MAXN 1000
#define MAXM 1000000
#define EPS 1e-8
int n;
struct Edge {
  int u, v; /* Edge between u, v with weight w */
  double w;
};
int sets[MAXN];
Edge edge[MAXM], treeedge[MAXN];
int numedge;
int getRoot(int x) {
  if(sets[x] < 0) return x;
  return sets[x] = getRoot(sets[x]);
}
void Union(int a, int b) {
  int ra = getRoot(a);
  int rb = getRoot(b);
  if(ra != rb) {
    sets[ra] += sets[rb];
    sets[rb] = ra;
  }
}
double mintree() {
  double weight = 0.0;
  int i, count;
  sort(edge, edge + numedge, [](auto a, auto b) { return a.w < b.w; });
  for(i = count = 0; count < n - 1; i++) {
    if(getRoot(edge[i].u) != getRoot(edge[i].v)) {
      Union(edge[i].u, edge[i].v);
      weight += edge[i].w;
      treeedge[count++] = edge[i];
    }
  }
  return weight;
}
