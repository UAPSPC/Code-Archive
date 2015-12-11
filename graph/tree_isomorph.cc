/* Graph Theory: Tree Isomorphism by certificates
   =================================================================
   Description: Given a tree this algorithm returns a certificate of
                the tree.  Two trees are isomorphic if and only if
		the certificates of the two trees are the same.

		The certificate computed is a binary string of 
		length 2n.

   Complexity:  O(N) (maybe a little more)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Feb 12, 2003
   References:  Combinatorial Algorithms: D Kreher
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       - A tree is given by the number of vertices (t.n) and
                  and adjacency list.  
		- Vertices are numbered 0..n-1
		- Note that with strings, equality can be checked by
		  "s1 == s2".
		- Verification: 5-Line (0-1-2-3-4) = 0001100111
		                5-Star (0-[1-4])   = 0010101011
*/

#include <stdio.h>
#include <string>
#include <list>
#include <set>

using namespace std;

#define MAXN 1000

typedef struct{
  int n; list<int> adj[MAXN];
} Tree;

string getTreeID(Tree t){
  multiset<string> s[MAXN]; multiset<string>::iterator it;
  set<int> leaf; set<int>::iterator j;
  char parent[MAXN]; string id[MAXN], res[2];
  int left = t.n, i, k, x;
  
  for(i = 0; i < t.n; i++) id[i] = "01";
  
  while(left > 2){
    memset(parent, 0, sizeof(parent));
    for(i = 0; i < t.n; i++) s[i].clear();
    leaf.clear();
    
    for(i = 0; i < t.n; i++)
      if(t.adj[i].size() == 1){
	leaf.insert(i);
	x = *t.adj[i].begin();
	s[x].insert(id[i]);
	parent[x] = 1;
	left--;
      }
    
    for(i = 0; i < t.n; i++)
      if(parent[i]){
	x = id[i].size();
	if(x > 2) s[i].insert(id[i].substr(1,x-2));
	for(id[i] = "0", it = s[i].begin(); it != s[i].end(); ++it)
	  id[i] += *it;
	id[i] += '1';
      }

    for(i = 0; i < t.n; i++)
      if(leaf.count(i) == 1) t.adj[i].clear();
      else
	for(j = leaf.begin(); j != leaf.end(); ++j)
	  for(k = 0; k < t.n; k++)
	    t.adj[k].remove(*j);
  }
  
  for(i = x =  0; i < t.n; i++)
    if(parent[i]) res[x++] = id[i];
  
  if(left == 1) return res[0];
  return (res[0] < res[1]) ? res[0]+res[1] : res[1]+res[0];
}

int main(){
  int i, x, y;
  Tree t;
  string id;
  
  while(scanf("%d", &t.n) == 1 && t.n){   /* Get number of nodes */
    
    for(i = 0; i < t.n; i++)
      t.adj[i].clear();                   /* Clear adj. list */
    
    for(i = 0; i < t.n-1; i++){           /* Get edges of tree */
      scanf("%d %d", &x, &y);
      t.adj[x].push_back(y);
      t.adj[y].push_back(x);
    }
    
    id = getTreeID(t);
    printf("This tree's ID is [%s]\n", id.c_str());
  }
  return 0;
}
