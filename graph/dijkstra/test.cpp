#include "dijkstra_min.cpp"

#include <iostream>

// Test of Djikstra's algorithm.
int main(int argc, char **argv)
{
	Graph G(6);
	G.addEdge(0, 1, 12);
	G.addEdge(0, 2, 3);
	G.addEdge(2, 3, 1);
	G.addEdge(3, 1, 2);
	G.addEdge(3, 4, 7);
	G.addEdge(1, 5, 1);
	G.addEdge(5, 4, 1);
	vector<int> prev = Dijkstra(G, 0);
	cout << "Node\tPrev" << endl;
	for (int i = 0; i < prev.size(); ++i)
		cout << i << '\t' << prev[i] << endl;
}
