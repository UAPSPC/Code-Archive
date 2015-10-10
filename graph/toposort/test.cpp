#include "toposort.cpp"

#include <iostream>

// Topological sort example.
int main(int argc, char **argv)
{
	Graph G(9);
	G.addEdge(0, 1);
	G.addEdge(1, 4);
	G.addEdge(1, 5);
	G.addEdge(2, 4);
	G.addEdge(3, 5);
	G.addEdge(3, 8);
	G.addEdge(4, 6);
	G.addEdge(4, 7);
	G.addEdge(5, 7);
	vector<int> sorted = Toposort(G);
	for (int i = 0; i < sorted.size(); ++i)
		cout << sorted[i] << ' ';
	cout << endl;
}
