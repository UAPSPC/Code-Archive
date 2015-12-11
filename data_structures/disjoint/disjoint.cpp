#include <vector>

using namespace std;

// Union-Find Algorithm with Union by Rank and Path Compression
class DisjointSets {
	public:
		DisjointSets(int N) : parent(vector<int>(N)), rank(vector<int>(N)) {}
		void MakeSet(int i) { parent[i] = i; rank[i] = 0; }
		void Union(int i, int j)
		{
			int iRoot = Find(i);
			int jRoot = Find(j);
			if (iRoot == jRoot) return;
			if (rank[iRoot] < rank[jRoot]) parent[iRoot] = jRoot;
			else if (rank[iRoot] > rank[jRoot]) parent[jRoot] = iRoot;
			else {
				parent[jRoot] = iRoot;
				rank[iRoot] += 1;
			}
		}
		int Find(int i)
		{
			if (parent[i] != i) parent[i] = Find(parent[i]);
			return parent[i];
		}
	private:
		vector<int> parent;
		vector<int> rank;
};
