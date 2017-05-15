// Given a weighted undirected graph G = (V, E) and a subset S of V,
// finds a minimum weight tree T whose vertices are a superset of S.
// NP-hard -- this is a pseudo-polynomial algorithm.
// Minimum stc[(1<<s)-1][v] (0 <= v < n) is weight of min. Steiner tree
// Minimum stc[i][v] (0 <= v < n) is weight of min. Steiner tree for
// the i’th subset of Steiner vertices
// S is the list of Steiner vertices, s = |S|
// d is the adjacency matrix (use infinities, not -1), and n = |V|
const int N = 32;
const int K = 8;
int d[N][N], n, S[K], s, stc[1 << K][N];
void steiner() {
  for(int k = 0; k < n; ++k)
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j) d[i][j] = min(d[i][k], d[i][k] + d[k][j]);
  for(int i = 1; i < (1 << s); ++i) {
    if(!(i & (i - 1))) {
      int u;
      for(int j = i, k = 0; j; u = S[k++], j >>= 1)
        ;
      for(int v = 0; v < n; ++v) stc[i][v] = d[v][u];
    } else
      for(int v = 0; v < n; ++v) {
        stc[i][v] = 0xffffff;
        for(int j = 1; j < i; ++j)
          if((j | i) == i) {
            int x1 = j, x2 = i & (~j);
            for(int w = 0; w < n; ++w) stc[i][v] = min(stc[i][v], d[v][w] + stc[x1][w] + stc[x2][w]);
          }
      }
  }
}
