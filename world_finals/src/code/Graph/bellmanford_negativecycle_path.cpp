const int MaxN = 205;
int N; // TODO
struct Edge { int from, to, cost; };
vector<Edge> allEdgesFromNode[MaxN];
// MUST be updated in update loop
int predecessor[MaxN];
// If the END of a path is in negative cycle, then no min cost path
bool inNegativeCycle[MaxN];
// Black - No cycle.
// Gray - Is in a cycle
// White - unknown.
const int White = 0, Gray = 1, Black = 2;
int color[MaxN];
// Determines if a node is contained in an infinite cycle
int ExpandPredecessor(int node) {
  if(color[node] != White) return color[node];
  color[node] = Gray;
  // Not part of a cycle at all
  if(predecessor[node] == -1) return color[node] = Black;
  int newColor = ExpandPredecessor(predecessor[node]);
  inNegativeCycle[node] = (newColor == Gray);
  return color[node] = newColor;
}
void ExpandNegativeCycle(int node) {
  inNegativeCycle[node] = true;
  for(Edge &e: allEdgesFromNode[node])
    if(!inNegativeCycle[e.to]) ExpandNegativeCycle(e.to);
}
void FinishUpBellmanFord() {
  // Go along the predecessor graph
  for(int i = 0; i < N; ++i) color[i] = White;
  // Find all nodes that are part of a negative cycle
  for(int i = 0; i < N; ++i) ExpandPredecessor(i);
  // Now, expand from all nodes that are in a negative cycle
  // - they cause all children to become negative cycle nodes
  for(int i = 0; i < N; ++i)
    if(inNegativeCycle[i]) ExpandNegativeCycle(i);
}
