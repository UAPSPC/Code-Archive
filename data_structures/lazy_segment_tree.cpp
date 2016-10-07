/* Data Structures: Lazy Segment Tree
   =================================================================
   Description: Segment Tree Structure
   
   Complexity:  Let N be the size of the heap:
                Construction: O(N logN)
                Query: O(logN)
                Update: O(logN)
   Memory:      O(N logN)
   -----------------------------------------------------------------
   Author:      Morgan Redshaw
   Date:        October, 2016
   References:  Learned segment tree from Competitive Programming 3 awhile ago?
   -----------------------------------------------------------------
   Reliability: 3 - UVa 12532, 11402, 1232
   Notes:       - Current example is containing the value for each node,
                  with the update being a sum change to the value, and query
                  asking for the sum over the range
                - By following the TODOs, can be heavily customized to fit the
                  needs of the current problem.
*/

#include <iostream>

#include <string>
#include <vector>

using namespace std;

const int MAX_N = 1024000;

struct Node
{
    int value;
    // Action will need to be applied to all children
    // Will already have been applied to the node
    // EG: Increase for all numbers in range
    int action;
    bool hasAction;
};

// TODO: Value may need to be changed.
// Note that it isn't always relevant, but might as well keep it
const int NO_ACTION = 0;
// TODO: Should be a value that doesn't change the result.
const int NEUTRAL_QUERY_VALUE = 0;

int N;
Node allNodes[5 * MAX_N];   

// After generating the segment tree, doesn't use the index specific array
int baseValue[MAX_N];

// TODO: This function may need to be altered.
// Such as by doing a max, min, or multiplication
int SubQueryMerge(int lhs_val, int rhs_val)
{
    return lhs_val + rhs_val;
}

// Inclusive on both
void GenerateSegmentTree(int index, int nodeLeft, int nodeRight)
{
    allNodes[index].action = NO_ACTION;
    
    if (nodeLeft == nodeRight)
    {
        // TODO: It can be worthwhile to transform the base values
        allNodes[index].value = baseValue[nodeLeft];
        return;
    }
    
    int mid = (nodeLeft + nodeRight) / 2;
    
    GenerateSegmentTree(index * 2, nodeLeft, mid);
    GenerateSegmentTree(index * 2 + 1, mid + 1, nodeRight);
    
    allNodes[index].value = SubQueryMerge(allNodes[index * 2].value, allNodes[index * 2 + 1].value);
}

// TODO: Will need to change the variable(s) passed in, and update all variables of node applied to!
// TODO: This must be able to handle having multiple lazy updates being applied without applying them.
// Like changing the value, then changing it again.
void AddLazyUpdateAction(int index, int action)
{
    allNodes[index].action += action;
    allNodes[index].hasAction = true;
}

void ApplyAndPushLazyUpdate(int index, int nodeStart, int nodeEnd)
{
    if (!allNodes[index].hasAction)
        return;

    // TODO: Apply the update
    allNodes[index].value += allNodes[index].action;
    
    if (nodeStart != nodeEnd)
    {
        int middle = (nodeStart + nodeEnd) / 2;
        
        // Tell children about their lazy status
        AddLazyUpdateAction(index * 2, allNodes[index].action);
        AddLazyUpdateAction(index * 2 + 1, allNodes[index].action);
    }
    
    allNodes[index].action = NO_ACTION;
    allNodes[index].hasAction = false;
}

// Inclusive on both starts and ends
void ApplyLazyChange(int index, int nodeStart, int nodeEnd, int changeStart, int changeEnd, int action)
{
    // Make sure the value is updated and moved to children
    ApplyAndPushLazyUpdate(index, nodeStart, nodeEnd);
    
    if (nodeEnd < changeStart || nodeStart > changeEnd)
    {
        return;
    }
    
    // This index is contained completely
    if (nodeStart >= changeStart && nodeEnd <= changeEnd)
    {
        // Add the update to this node, then apply it so parent will get correct value.
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
int Query(int index, int nodeStart, int nodeEnd, int queryStart, int queryEnd)
{
    if (nodeEnd < queryStart || nodeStart > queryEnd)
        return NEUTRAL_QUERY_VALUE;
    
    // Make sure the value is updated and moved to children
    ApplyAndPushLazyUpdate(index, nodeStart, nodeEnd);
    
    // This index is contained completely
    if (nodeStart >= queryStart && nodeEnd <= queryEnd)
    {
        return allNodes[index].value;
    }
    
    int middle = (nodeStart + nodeEnd) / 2;
    
    int count = SubQueryMerge(Query(index * 2, nodeStart, middle, queryStart, queryEnd),
                              Query(index * 2 + 1, middle + 1, nodeEnd, queryStart, queryEnd));
    return count;
}

int main()
{
    int N;
    
    while (cin >> N)
    {
        // TODO: Only necessary to reset allNodes structure if not building up the table
        // Otherwise, read in input here.
        for (int i = 0; i < N; ++i)
            cin >> baseValue[i];
        
        GenerateSegmentTree(1, 0, N - 1);
        
        int q;
        cin >> q;
        
        while (q--)
        {
            string cmd;
            int start, end;
            
            cin >> cmd >> start >> end;
            // TODO: Make sure start and end are inclusive before calling functions
            if (cmd == "query")
            {
                cout << Query(1, 0, N - 1, start, end) << '\n';
            }
            else
            {
                int increase;
                cin >> increase;
                ApplyLazyChange(1, 0, N - 1, start, end, increase);
            }
        }
    }
}
