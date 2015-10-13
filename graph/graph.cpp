#include <vector>
#include <utility>
#include <limits>
#include <set>

using namespace std;

// Some basic data structures for graph storage.
struct Edge {
	Edge(int a, int b) : a(a), b(b) {}
	Edge() {}
	int a, b;
};

typedef pair<Edge, int> WeightedEdge;
typedef set<int>::iterator NodeIterator;
typedef set<int>::const_iterator ConstNodeIterator;
typedef vector<WeightedEdge>::iterator EdgeIterator;
typedef vector<WeightedEdge>::const_iterator ConstEdgeIterator;

// Graph implemented as edge list and node set.
struct Graph {
	vector<WeightedEdge> edges;	// Weighted directed edges in the graph.
	set<int> nodes;	// Keep a set of nodes around so we know how many nodes are in the graph.
	void AddEdge(int a, int b, int w)
	{
		nodes.insert(a); nodes.insert(b);
		edges.push_back(make_pair(Edge(a,b), w));
	}
	void AddBiEdge(int a, int b, int w) { AddEdge(a,b,w); AddEdge(b,a,w); }
	int NumEdges() const { return edges.size(); }
	int NumNodes() const { return nodes.size(); }
};
