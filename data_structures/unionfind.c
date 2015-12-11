/* Data Structures: Unionfind with array
   =================================================================
   Description: Unionfind is a way to implement the union operator
                on sets.  It consists of 2 functions:
		  getRoot(x) which returns the identifier of a set
		  Union(a,b) which performs a union on the set 
		             containing a with the set containing b
   
   Complexity:  Union   - O(1)
                getRoot - O(roughly constant)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 21, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 
   Notes:       The array sets must be initialized to -1.  Negative
                numbers in the array represent the size of the set
		associated with that element, while positive numbers
		serve as a link back to the root of the set.
*/

#include <stdio.h>
#include <string.h>

#define MAXN 1000

int sets[MAXN];

int getRoot(int x){
  if(sets[x] < 0) return x;
  return sets[x] = getRoot(sets[x]);
}

void Union(int a, int b){
  int ra = getRoot(a);
  int rb = getRoot(b);

  if(ra != rb){
    sets[ra] += sets[rb];
    sets[rb] = ra;
  }
}

int main(){
  int a, b, i, n, m;
  
  while(scanf("%d %d", &n, &m) == 2){
    memset(sets, -1, sizeof(sets));
    for(i = 0; i < m; i++){
      scanf("%d %d", &a, &b);
      Union(a,b);
    }
    for(i = 0; i < n; i++){
      printf("%d belongs in the set with [%d]\n", i, getRoot(i));
    }
  }
  return 0;
}
