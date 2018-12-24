/* Author: Noah Weninger, 2018

    Finds the least common ancestor (LCA) of two nodes in a tree.
    The LCA is the deepest node which is the ancestor of both input nodes.
    For example:

        0
       / \
      1   2
     / \   \
    3   4   5

    lca(4,4) = 4
    lca(0,3) = 0
    lca(5,3) = 0
    lca(3,4) = 1
    lca(2,5) = 2

    In general: (the root must be node 0)
    lca(a,b) = lca(b,a)
    lca(0,a) = 0
    lca(a,a) = a

    Complexity: O(log n)

    Use:
    Set MAXN to the max node count.
    Set n to the node count.
    Describe the tree in P (parents array) as follows:
       P[0][0] = -2
       P[i][0] = parent of i
    Call lca(u,v) or dist(u,v) as needed.

    Make sure to memset P and D to -1 in between test cases.

    Reference:
    LCA slides by Zachary Friggstad:
    https://webdocs.cs.ualberta.ca/~contest/meetingnotes/lca_queries.pdf

    Reliability:
    railway2 - Open Kattis
    tourists - Open Kattis
    stogovi - Open Kattis
*/

#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;
constexpr int log2(int n) {
    int c = 0;
    while(n >>= 1) c++;
    return c;
}

#define MAXN 200100 // TODO: Max node count
int n; // TODO: Node count
int P[MAXN][log2(MAXN)+1]; // TODO: Parents. P[i][0] = parent of i, P[0][0] = -2

// Find the vertex that is 2^i steps above u
int parent(int u, int i) {
    int &v = P[u][i];
    if (v != -1) return v;
    if (!i) return P[u][0];
    if (parent(u,i-1) == -2) return v = -2;
    return v = parent(parent(u,i-1),i-1);
}

// Depth of node u
int D[MAXN];
int depth(int u) {
    if (D[u] != -1) return D[u];
    return u ? D[u] = 1+depth(P[u][0]) : 0;
}

// Least common ancestor. O(log n)
int lca(int u, int v) {
    if (depth(v) > depth(u)) return lca(v,u);
    for (int i = log2(n); i >= 0; i--)
        if ((depth(u) - (1<<i)) >= depth(v)) u = parent(u,i);
    // invariant: depth(u) == depth(v)
    assert(depth(u) == depth(v));
    if (u == v) return u;
    for (int i = log2(n)-1; i >= 0; i--)
        if (parent(u,i) != parent(v,i)) {
            u = parent(u,i);
            v = parent(v,i);
        }
    // invariant: p(u,0) == p(v,0)
    assert(parent(u,0) == parent(v,0));
    return parent(u,0);
}

// Distance between u and v.
// Includes both endpoint nodes.
int dist(int u, int v) {
    int a = lca(u,v);
    return depth(u) + depth(v) - 2*depth(a) + 1;
}

int main() {
    memset(D,-1,sizeof D);
    memset(P,-1,sizeof P);
    P[0][0] = -2;

    cin >> n;
    for (int i = 0; i < n-1; i++) {
        // Read edges: parent of v is u
        int u, v; cin >> u >> v;
        P[v][0] = u;
    }
    int queries; cin >> queries;
    for (int i = 0; i < queries; i++) {
        int u, v; cin >> u >> v;
        cout << "LCA: " << lca(u,v) << ", Dist: " << dist(u,v) << endl;
    }
}
