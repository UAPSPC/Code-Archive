#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// Typedefs for readability.
typedef vector<list<int> >::const_iterator ConstNodeIterator;
typedef list<int>::const_iterator ConstEdgeIterator;

// Adjacency list graph representation.
struct Graph {
	Graph(int N) : graph(N, list<int>()) {}
	void addEdge(int src, int dst) { graph[src].push_back(dst); }
	vector<list<int> > graph;
};

// DFS-based Toposort algorithm. Visit children, then append this node.
void visit(const Graph& G, int node, vector<bool>& marked, vector<bool>& tempMarked, vector<int>& sorted)
{
	if (tempMarked[node]) return;	// Error: Not a DAG, topological sort not possible.
	if (marked[node]) return;	// This is OK
	tempMarked[node] = true;
	for (ConstEdgeIterator it = G.graph[node].begin(); it != G.graph[node].end(); ++it) {
		visit(G, *it, marked, tempMarked, sorted);
	}
	tempMarked[node] = false;
	marked[node] = true;
	sorted.push_back(node);
}

// Topological sort. Wrapper around visit, sorts all components of graph.
vector<int> Toposort(const Graph& G)
{
	vector<int> sorted;
	sorted.reserve(G.graph.size());
	vector<bool> marked(G.graph.size(), false);
	vector<bool> tempMarked(G.graph.size(), false);
	for (int i = 0; i < marked.size(); ++i)
		if (!marked[i]) visit(G, i, marked, tempMarked, sorted);
	reverse(sorted.begin(), sorted.end());
	return sorted;
}
