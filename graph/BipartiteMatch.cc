/* Graph Theory: Maximum Bipartite Matching
   =================================================================
   Description: Given a bipartite graph G = {U,V,E}, this routine
                computes the maximum bipartite matching.

		For vertex i of set U:
		match[i] = -1 means i is not matched
		match[i] =  x means the edge i->(x-|U|) is selected
		                             **********
		For simplicity, use addEdge(i,j,n) to add edges, where
		0 <= i < |U| and 0 <= j < |V| and |U| = n.

		If there is an edge from vertex i of U to vertex
		j of V then: e[i][j+|U|] = e[j+|U|][i] = 1. 
		                  ******     *****

   Complexity:  O(U+V) where U and V are the sizes of the sets
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        May 6, 2003
   References:  Waterloo code
   
   -----------------------------------------------------------------
   Editor:      Morgan Redshaw
   Date:        January 2016
   
   Changes: Changed to use c++
            Improved the speed, by removing an unnecessary reset in bipmatch
            Reduced the number of globals
   -----------------------------------------------------------------
   Reliability: 2 old (Spain 10080 - Golpher holes II, 
                   Housing Complexes Mar 8th, 2003)
                1 success with current version, on UVa 1221
   Notes:       - If |U| = n and |V| = m, then vertices are assumed
                  to be from [0,n-1] in set U and [0,m-1] in set V.
		- Remember that match[i]-n gives the edge from i,
		  not just match[i].

        A bipartite graph is one where the vertices can be
        separated into two disjoint sets U and V, such that
		all edges in the graph are between a vertex in U and
		a vertex iv V.  A maximum matching on such a graph
		is the selection of the most edges such that each
		vertex is adjacent to at most one edge.
		
		The maximum matching is equivalent to the minimal
		vertex cover in a bipartite graph.
*/
#include <iostream>

using namespace std;

const int MaxNumNodes = 500;
bool edge[MaxNumNodes][MaxNumNodes];
int match[MaxNumNodes];

void addEdge(int uIndex, int vIndex, int sizeOfU)
{
    edge[uIndex][vIndex + sizeOfU] = edge[vIndex + sizeOfU][uIndex] = true;
}

int find(int node, int totalNumberNodes)
{
    if (match[node] != -1)
        return 0;
    
    // Stoers the order that nodes were accessed
    int nodesInOrder[MaxNumNodes];
    
    // Back stores the reverse order of accessess, indexed by node
        // -1 if not accessed
    int back[MaxNumNodes];

    for (int i = 0; i < totalNumberNodes; ++i)
        back[i] = -1;

    nodesInOrder[0] = node;
    for (int i = 0, numNodesEncountered = 1; i < numNodesEncountered; i++)
    {
        const int currentNode = nodesInOrder[i];
        for (int j = 0; j < totalNumberNodes; j++)
        {
            // Ensure is edge from currentNode to j
            if (!edge[currentNode][j])
                continue;

            // j has already been encountered as a match
            if (match[j] != -1)
            {
                // Ensure we havent reached it already in this iteration
                if (back[j] == -1)
                {
                    back[j] = currentNode;
                    nodesInOrder[numNodesEncountered] = match[j];
                    back[match[j]] = j;
                    numNodesEncountered++;
                }
            } 
            else
            {
                match[currentNode] = j;
                match[j] = currentNode;
                for (int r = back[currentNode]; r != -1; r = back[back[r]])
                {
                    match[r] = back[r];
                    match[match[r]] = r;
                }

                return 1;
            }
        }
    }
    return 0;
}

void bipmatch(int totalNumberNodes)
{
    // Reset the matches
    for (int i = 0; i < totalNumberNodes; ++i)
        match[i] = -1;
    
    for (int i = 0; i < totalNumberNodes; i++)
        find(i, totalNumberNodes);
}

int main()
{
    int sizeOfU, sizeOfV;

    // Read size of sets
    while (cin >> sizeOfU >> sizeOfV)
    {
        // Clear edges
        for (int i = 0; i < sizeOfU + sizeOfV; ++i)
            for (int j = 0; j < sizeOfU + sizeOfV; ++j)
                edge[i][j] = edge[j][i] = false;
        
        int numEdges;
        cin >> numEdges;
        
        // Add edges
        while (numEdges--)
        {
            int x, y;
            // Remember, enter y as the index in V, relative to 0
            cin >> x >> y;
            addEdge(x, y, sizeOfU);
        }

        bipmatch(sizeOfU + sizeOfV);

        // Determine count
        int count = 0;
        for (int i = 0; i < sizeOfU; i++)
            if (match[i] != -1)
                count++;
            
        cout << "Matching size: " << count << '\n';
    }
}
