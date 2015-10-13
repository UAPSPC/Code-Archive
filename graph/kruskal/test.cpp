#include "kruskal.cpp"

#include <iostream>

// Test Kruskal's MST algorithm.
int main(int argc, char **argv)
{
	Graph G;
	G.AddBiEdge(0,1,1);
	G.AddBiEdge(1,2,10);
	G.AddBiEdge(2,3,3);
	G.AddBiEdge(2,5,1);
	G.AddBiEdge(3,4,1);
	G.AddBiEdge(5,4,1);
	vector<WeightedEdge> MST = KruskalMST(G);
	for (int i = 0; i < MST.size(); ++i) {
		cout << MST[i].first.a << " -> " << MST[i].first.b << " (" << MST[i].second << ")" << endl;
	}
	return 0;
}
