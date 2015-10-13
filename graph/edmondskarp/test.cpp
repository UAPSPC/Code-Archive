#include "EdmondsKarp.cpp"

// Test flow implementation.
int main(int argc, char **argv)
{
	FlowGraph FG(7);
	FG.addEdge(0,1,3);
	FG.addEdge(0,2,5);
	FG.addEdge(1,2,4);
	FG.addEdge(2,4,6);
	FG.addEdge(2,5,3);
	FG.addEdge(4,5,1);
	FG.addEdge(4,3,3);
	FG.addEdge(3,6,10);
	FG.addEdge(5,6,4);
	cout << EdmondsKarp(FG, 0, 6) << endl;
}