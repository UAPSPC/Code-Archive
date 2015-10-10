#include <vector>
#include <list>
#include <algorithm>
#include <limits>
#include <queue>
#include <functional>
#include <utility>

using namespace std;

// Simple adjacency list graph implementation.

struct Edge {
	Edge() : dst(0), len(0) {}
	Edge(int dst, int len) : dst(dst), len(len) {}
	int dst, len;
};

// Typedefs for later readability.
typedef list<Edge> EdgeList;
typedef vector<EdgeList> AdjGraph;
typedef vector<EdgeList>::iterator NodeIterator;
typedef vector<EdgeList>::const_iterator ConstNodeIterator;
typedef EdgeList::iterator EdgeIterator;
typedef EdgeList::const_iterator ConstEdgeIterator;

// Basic graph class.
struct Graph {
	Graph(int N) : graph(N, list<Edge>()) {}
	void addEdge(int src, int dst, int len)
	{
		graph[src].push_back(Edge(dst, len));
	}
	AdjGraph graph;
};

vector<int> Dijkstra(const Graph& G, int src)
{
	vector<bool> visited(G.graph.size(), false);
	vector<int> distance(G.graph.size(), numeric_limits<int>::max());
	vector<int> prev(G.graph.size(), -1);
	// Long template parameter list to make this a min-first priority queue
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
	
	// Add the source node with distance 0 to start.
	distance[src] = 0;
	q.push(make_pair(0, src));
	
	while (!q.empty()) {
		// Look at the next node on the queue.
		pair<int, int> entry = q.top(); q.pop();
		// Cur is the node index.
		int cur = entry.second;
		// If we visited this node by some other route, that other route is better than or
		// equal to the current route, so we can skip it.
		if (visited[cur]) continue;
		// For each neighbour of this node . . .
		for (ConstEdgeIterator it = G.graph[cur].begin(); it != G.graph[cur].end(); ++it) {
			if (visited[it->dst]) continue;	// Skip it if we've seen it.
			// If following this edge improves the shortest path . . .
			if (distance[cur] + it->len < distance[it->dst]) {
				// Update shortest path info, and enqueue node.
				distance[it->dst] = distance[cur] + it->len;
				prev[it->dst] = cur;
				q.push(make_pair(distance[it->dst], it->dst));
			}
		}
		visited[cur] = true;
	}
	// Return vector of parents in the SSSP tree.
	return prev;
}
