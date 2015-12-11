#include "disjoint.cpp"

#include <iostream>

// Demonstration of Disjoint Set data structure.
int main(int argc, char **argv)
{
	// Create 5 disjoint elements.
	DisjointSets DS(5);
	for (int i = 0; i < 5; ++i) DS.MakeSet(i);
	// Union together subsets.
	DS.Union(0,1);
	DS.Union(1,2);
	DS.Union(3,4);
	// Query subsets.
	cout << DS.Find(0) << ' ' << DS.Find(2) << endl;
	cout << DS.Find(4) << endl;
	// This union should result in all elements belonging to the same set.
	DS.Union(4,0);
	cout << DS.Find(0) << ' ' << DS.Find(1) << ' ' << DS.Find(4) << endl; 
}
