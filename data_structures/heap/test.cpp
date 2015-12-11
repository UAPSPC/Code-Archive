#include "heap.cpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

// Example usage of heap datatype
int main(int argc, char **argv)
{
	Heap<int> H;	// Heap of int
	srand(time(NULL));
	
	// Populate heap by inserting numbers one at a time.
	for (int i = 0; i < 20; ++i) H.Insert(rand());
	// Pop elements in sorted order.
	while (H.Size() > 0) {
		cout << H.Top() << endl;
		H.Pop();
	}
	
	cout << endl;
	
	// Populate heap by running "heapify" on vector.
	// O(N)
	vector<int> toHeap;
	for (int i = 0; i < 20; ++i) toHeap.push_back(rand());
	H.Heapify(toHeap);
	// Pop elements in sorted order.
	while (H.Size() > 0) {
		cout << H.Top() << endl;
		H.Pop();
	}
	
	return 0;
}
