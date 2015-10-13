#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

// Flow graph implementation, including reverse-edge pointers.
struct FlowEdge {
	FlowEdge() : dst(0), src(0), cap(0), flow(0) {}
	FlowEdge(int src, int dst, int cap) : src(src), dst(dst), cap(cap), flow(0) {}
	int dst, src, cap;
	int flow;
	FlowEdge *redge;
};

// Typedefs for readability.
typedef vector<list<FlowEdge> > AdjFlowGraph;
typedef vector<list<FlowEdge> >::iterator NodeIterator;
typedef vector<list<FlowEdge> >::const_iterator ConstNodeIterator;
typedef list<FlowEdge>::iterator EdgeIterator;
typedef list<FlowEdge>::const_iterator ConstEdgeIterator;

struct FlowGraph {
	FlowGraph(int N) : graph(N, list<FlowEdge>()) {}
	void reserve(int N) { graph.reserve(N); }
	void addEdge(int src, int dst, int cap)
	{
		graph[src].push_back(FlowEdge(src, dst, cap));
		FlowEdge *e1 = &graph[src].back();
		graph[dst].push_back(FlowEdge(dst, src, 0));
		FlowEdge *e2 = &graph[dst].back();
		e1->redge = e2;	// Carefully assign pointers to reverse edges.
		e2->redge = e1;	// This is really bad and likely buggy. Should be fixed.
	}
	AdjFlowGraph graph;
};

int EdmondsKarp(FlowGraph& FG, int source, int sink)
{
	for(;;) {
		queue<int> visitQueue;
		vector<bool> visited(FG.graph.size(), false);

		vector<FlowEdge *> pathTo(FG.graph.size(), NULL);
		
		visitQueue.push(source);
		visited[source] = true;
		
		int cur;
		for(;;) {
			if (visitQueue.empty()) {
				int flow = 0;
				for (ConstEdgeIterator it = FG.graph[source].begin();
						it != FG.graph[source].end(); ++it) {
					flow += it->flow;
				}
				return flow;
			}
			cur = visitQueue.front();
			visitQueue.pop();
			if (cur == sink) break;
			for (EdgeIterator it = FG.graph[cur].begin();
					it != FG.graph[cur].end(); ++it) {
				if (visited[it->dst] || it->flow >= it->cap) continue;
				visitQueue.push(it->dst);
				visited[it->dst] = true;
				pathTo[it->dst] = &*it;
			}
		}
		int capacity = numeric_limits<int>::max();
		for (int loc = cur; loc != source; loc = pathTo[loc]->src) {
			capacity = min(pathTo[loc]->cap - pathTo[loc]->flow, capacity);
		}
		for (int loc = cur; loc != source; loc = pathTo[loc]->src) {
			pathTo[loc]->flow += capacity;
			pathTo[loc]->redge->flow -= capacity;
		}
	}
}
