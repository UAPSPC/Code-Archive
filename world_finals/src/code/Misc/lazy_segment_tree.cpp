const int MAX_N = 1024000;
struct Node {
  int value;
  // Action will need to be applied to all children
  // Will already have been applied to the node
  // EG: Increase for all numbers in range
  int action;
  bool hasAction;
};
const int NO_ACTION = 0; // TODO?
const int NEUTRAL_QUERY_VALUE = 0; // TODO?
int N; // TODO
Node allNodes[5 * MAX_N];
// After generating the segment tree, doesn't use
// the index specific array
int baseValue[MAX_N];
int SubQueryMerge(int lhs_val, int rhs_val) {
  return lhs_val + rhs_val; // TODO?
}
// Inclusive on both
void GenerateSegmentTree(int index, int nodeLeft, int nodeRight) {
  allNodes[index].action = NO_ACTION;
  if(nodeLeft == nodeRight) {
    allNodes[index].value = baseValue[nodeLeft]; // TODO?
    return;
  }
  int mid = (nodeLeft + nodeRight) / 2;
  GenerateSegmentTree(index * 2, nodeLeft, mid);
  GenerateSegmentTree(index * 2 + 1, mid + 1, nodeRight);
  allNodes[index].value = SubQueryMerge(allNodes[index * 2].value, allNodes[index * 2 + 1].value);
}
void AddLazyUpdateAction(int index, int action) {
  allNodes[index].action += action; // TODO - Handle multiple different lazy updates
  allNodes[index].hasAction = true;
}
void ApplyAndPushLazyUpdate(int index, int nodeStart, int nodeEnd) {
  if(!allNodes[index].hasAction) return;
  allNodes[index].value += allNodes[index].action; // TODO: Apply
  if(nodeStart != nodeEnd) {
    int middle = (nodeStart + nodeEnd) / 2;
    // Tell children about their lazy status
    AddLazyUpdateAction(index * 2, allNodes[index].action);
    AddLazyUpdateAction(index * 2 + 1, allNodes[index].action);
  }
  allNodes[index].action = NO_ACTION;
  allNodes[index].hasAction = false;
}
// Inclusive on both starts and ends
void ApplyLazyChange(int index, int nodeStart, int nodeEnd, int changeStart, int changeEnd, int action) {
  // Make sure the value is updated and moved to children
  ApplyAndPushLazyUpdate(index, nodeStart, nodeEnd);
  if(nodeEnd < changeStart || nodeStart > changeEnd) return;
  // This index is contained completely
  if(nodeStart >= changeStart && nodeEnd <= changeEnd) {
    // Add the update to this node, then apply
    // it so parent will get correct value.
    AddLazyUpdateAction(index, action);
    ApplyAndPushLazyUpdate(index, nodeStart, nodeEnd);
    return;
  }
  int middle = (nodeStart + nodeEnd) / 2;
  ApplyLazyChange(index * 2, nodeStart, middle, changeStart, changeEnd, action);
  ApplyLazyChange(index * 2 + 1, middle + 1, nodeEnd, changeStart, changeEnd, action);
  allNodes[index].value = SubQueryMerge(allNodes[index * 2].value, allNodes[index * 2 + 1].value);
}
// Inclusive on both starts and ends
int Query(int index, int nodeStart, int nodeEnd, int queryStart, int queryEnd) {
  if(nodeEnd < queryStart || nodeStart > queryEnd) return NEUTRAL_QUERY_VALUE;
  // Make sure the value is updated and moved to children
  ApplyAndPushLazyUpdate(index, nodeStart, nodeEnd);
  // This index is contained completely
  if(nodeStart >= queryStart && nodeEnd <= queryEnd) return allNodes[index].value;
  int middle = (nodeStart + nodeEnd) / 2;
  int count = SubQueryMerge(Query(index * 2, nodeStart, middle, queryStart, queryEnd), Query(index * 2 + 1, middle + 1, nodeEnd, queryStart, queryEnd));
  return count;
}
