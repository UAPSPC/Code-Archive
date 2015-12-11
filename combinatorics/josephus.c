/* Combinatorics: Josephus Ring Survivor
   =================================================================
   Description: Suppose that there are n people in a ring, [0..n-1].
                Count around the ring, starting from 0, and 
		dismissing every m-th person.
		
		Given m, this function builds an array survive[i] 
		which contains the last person left in the ring if
		there were i people to begin with. 
   
   Complexity:  O(N)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        March 01, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 2 (Spain 151 - Power Crisis)
                  (Spain 180 - Eeny Meeny)
   Notes:       - survive[i] is only define when i >= 1
*/

#include <stdio.h>

#define MAXN 1000005

int survive[MAXN];

void josephus(int n, int m){
  int i;
  survive[1] = 0;
  for(i = 2; i <= n; i++)
    survive[i] = (survive[i-1]+(m%i))%i;
}  

int main(){
  int n, m;

  while(scanf("%d %d", &n, &m)==2){
    josephus(n,m);
    printf("Survivor is %d\n", survive[n]);
  }
  return 0;
}
