#include "../graph.cpp"

// Bellman-Ford algorithm. Update distances N-1 times, where N is the number of nodes in the graph.
vector<int> BellmanFord(const Graph& G, int source)
{
	vector<int> dist(G.NumNodes(), numeric_limits<int>::max());
	dist[source] = 0;
	for (int i = 0; i < G.NumNodes()-1; ++i)
		for (ConstEdgeIterator it = G.edges.begin(); it != G.edges.end(); ++it)
			dist[it->first.b] = min(dist[it->first.b], dist[it->first.a] + it->second);
	return dist;
}

// If one more iteration of Bellman-Ford updates the distance to a node, there is a negative cycle.
bool HasNegativeCycle(const Graph& G, const vector<int>& dist)
{
	for (ConstEdgeIterator it = G.edges.begin(); it != G.edges.end(); ++it)
		if (dist[it->first.a] + it->second < dist[it->first.b]) return true;
	return false;
}
