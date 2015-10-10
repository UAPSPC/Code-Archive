#include <vector>
#include <list>
#include <limits>
#include <queue>
#include <functional>
#include <utility>

using namespace std;

struct Graph {
	Graph(int N) : graph(N, list<pair<int, int> >()) {}
	void addEdge(int src, int dst, int len) { graph[src].push_back(make_pair(dst, len)); }
	vector<list<pair<int, int> > > graph;
};

vector<int> Dijkstra(const Graph& G, int src)
{
	vector<bool> visited(G.graph.size(), false);
	vector<int> distance(G.graph.size(), numeric_limits<int>::max());
	vector<int> prev(G.graph.size(), -1);
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
	
	distance[src] = 0;
	q.push(make_pair(0, src));
	
	while (!q.empty()) {
		pair<int, int> entry = q.top(); q.pop();
		int cur = entry.second;
		if (visited[cur]) continue;
		for (list<pair<int, int> >::const_iterator it = G.graph[cur].begin(); it != G.graph[cur].end(); ++it) {
			if (visited[it->first]) continue;
			if (distance[cur] + it->second < distance[it->first]) {
				distance[it->first] = distance[cur] + it->second;
				prev[it->first] = cur;
				q.push(make_pair(distance[it->first], it->first));
			}
		}
		visited[cur] = true;
	}
	return prev;
}
