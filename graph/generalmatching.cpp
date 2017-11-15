/* Copyright 2017 - Zachary Friggstad

   Maximum matching in a general (not necessarily bipartite) graph.

   g[v] is a vector representing an adjacency list for v

   Just call max_match(n) where n is the number of nodes.
   It returns the size of a maximum matching, afterward match[u] is the vertex
   that u is matched to (-1 if u is not matched).

   Running time: O(|V|^3)

   Guaranteed O(|V|*|E|) if the graph is bipartite (it will never blossom)

   Reliability:
   - UVa 11439
   - ICPC Live 3820
   - CodeJam AMER Semifinal 2008, problem D "King"
     https://code.google.com/codejam/contest/dashboard?c=32008#s=p3
*/

#include <iostream>
#include <queue>
#include <utility>
#include <vector>

#define MAXN 1000

using namespace std;

typedef pair<int,int> pii;

vector<int> g[MAXN];

queue<pii> q;

int match[MAXN], pre[MAXN], dist[MAXN], uf[MAXN];

int find(int v) { return (v == uf[v]) ? v : (uf[v] = find(uf[v])); }

// Augment the path starting at u all the way to the root of its tree
void aug(int u) {
    if (match[u] != -1) {
        int v = match[u], w = pre[match[u]];
        aug(w);
        match[w] = v;
        match[v] = w;
    }
}

void enqueue(int v, int d = 0) {
    if (uf[v] == -1) {
        uf[v] = v;
        dist[v] = d;
        for (auto w : g[v]) q.push(pii(v,w));
    }
}

// assumes b is the least common ancestor of u and v in their forest
// contracts the nodes on the u-b and v-b paths into a common blossom
void blossom(int u, int v, int b) {
    if (find(u) != b) pre[u] = v;
    while (find(u) != b) {
        v = match[u];
        int w = pre[v];

        enqueue(v);
        uf[u] = uf[v] = b;

        if (find(w) != b) pre[w] = v;
        u = w;
    }
}

// grows a forest of trees, implicitly contracting blossoms
bool grow(int n) {
    q = queue<pii>();

    // initialize and enqueue an exposed vertices
    for (int v = 0; v < n; ++v) {
        pre[v] = dist[v] = -1;
        uf[v] = -1;
        if (match[v] == -1) enqueue(v);
    }

    int iter = 0;
    while (!q.empty()) {
        int u = q.front().first, v = q.front().second;
        q.pop();

        // if uv is an edge to a new vertex, process v and its matched node w
        if (uf[v] == -1 && pre[v] == -1) {
            int w = match[v];
            pre[v] = u;
            enqueue(w, dist[u]+2);
        }
        else if (uf[v] != -1 && (find(u) != find(v))) {
            // now we know v is also an "outer" vertex and not
            // in a blossom with u

            // If u,v are in different trees, this will march to their
            // respective roots. Otherwise, this will march to their common
            // ancestor in the tree.
            int b = find(u), b2 = find(v);
            while (b != b2 && (dist[b]|dist[b2])) {
                int& bb = (dist[b] > dist[b2] ? b : b2);
                bb = find(pre[match[bb]]);
            }

            // If they were in different trees, we found an augmenting path!
            if (b != b2) {
                aug(u);
                aug(v);
                match[u] = v;
                match[v] = u;
                return true;
            }

            // otherwise contract the u-b and v-b paths into a common blossom
            // need both calls
            blossom(u, v, b);
            blossom(v, u, b);
        }
    }

    return false;
}

int max_match(int n) {
    for (int i = 0; i < n; ++i) match[i] = -1;

    int cnt = 0;

    // iterate while we find an augmenting path
    // each time we find an augmenting path, the matching size increases by 1
    while (grow(n)) ++cnt;
    return cnt;
}


int main() {
    int n, m;
    cout << "Enter # nodes and # edges, respectively: ";
    cin >> n >> m;

    cout << "Now enter edges (vertex indexing is base 0):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cout << "Max matching size: " << max_match(n) << endl;
    cout << "Edges:" << endl;
    for (int i = 0; i < n; ++i)
        if (match[i] != -1 && match[i] < i) // ensures each edge prints once
            cout << match[i] << ' ' << i << endl;

    return 0;
}
