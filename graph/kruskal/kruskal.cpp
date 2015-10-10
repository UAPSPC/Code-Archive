#include "../graph.cpp"
#include "../../data/disjoint/disjoint.cpp"

#include <algorithm>

// Comparison function for sorting edges by edge weight.
bool EdgeWeightComp(const WeightedEdge& L, const WeightedEdge& R)
{
	return L.second < R.second;
}

// Kruskal's MST algorithm using Disjoint Sets data structure.
vector<WeightedEdge> KruskalMST(const Graph& G)
{
	DisjointSets DS(G.nodes.size());
	vector<WeightedEdge> MST;
	MST.reserve(G.NumNodes() - 1);
	for (ConstNodeIterator it = G.nodes.begin(); it != G.nodes.end(); ++it)
		DS.MakeSet(*it);
	vector<WeightedEdge> edges = G.edges;
	sort(edges.begin(), edges.end(), EdgeWeightComp);
	for (int i = 0; i < edges.size(); ++i) {
		if (DS.Find(edges[i].first.a) != DS.Find(edges[i].first.b)) {
			MST.push_back(edges[i]);
			DS.Union(edges[i].first.a, edges[i].first.b);
		}
	}
	return MST;
}
