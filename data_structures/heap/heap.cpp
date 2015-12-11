#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Templatized Heap (see test.cpp for usage)
// Heap is a min-heap (smallest element on top)
// Heap elements are stored in a vector.
// __heap[2*i+1] and __heap[2*i+2] are the children of __heap[i]
template <typename T>
class Heap {
	public:
		virtual ~Heap() {}
		virtual void Reserve(int N) { _heap.reserve(N); }
		virtual void Insert(const T& elem)
		{
			_heap.push_back(elem);
			ShiftUp(_heap.size()-1);
			
		}
		virtual T Top() const { return _heap[0]; }
		virtual void Pop()
		{
			swap(_heap[0], _heap[_heap.size()-1]);
			_heap.pop_back();
			ShiftDown(0);
		}
		virtual void Heapify(const vector<T>& vect)
		{
			_heap = vect;
			for (int i = Parent(_heap.size()-1); i >= 0; --i)
				ShiftDown(i);
		}
		virtual int Size() const { return _heap.size(); }
	private:
		virtual int Parent(int i) const { return (i-1)/2; }
		virtual int LeftChild(int i) const { return 2*i+1; }
		virtual int RightChild(int i) const { return 2*i+2; }
		virtual void ShiftUp(int i)
		{
			for (; i > 0 && _heap[Parent(i)] > _heap[i]; i = Parent(i))
				swap(_heap[Parent(i)], _heap[i]);
		}
		virtual void ShiftDown(int i)
		{
			int minIndex;
			while (true) {
				minIndex = LeftChild(i);
				if (minIndex >= _heap.size()) break;
				if (RightChild(i) < _heap.size() && _heap[RightChild(i)] < _heap[LeftChild(i)]) minIndex = RightChild(i);
				if (_heap[minIndex] < _heap[i]) {
					swap(_heap[i], _heap[minIndex]);
					i = minIndex;
				} else {
					break;
				}
			}
		}
		vector<T> _heap;
};
