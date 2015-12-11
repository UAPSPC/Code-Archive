/* Number Theory: Number of Divisors
   =================================================================
   Description: Returns the number of divisors for a positive
                integer N
   
   Complexity:  O(sqrt(N))
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 8, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0  
   Notes:       
*/

#include <stdio.h>

int num_divisors(int n){
  int i, count, res = 1;
  
  for(i = 2; i*i <= n; i++){
    count = 0;
    while(!(n%i)){
      n /= i;
      count++;
    }
    if(count) res *= (count+1);
  }
  if(n > 1) res *= 2;
  return res;
}

int main(){
  int n;
  
  while(scanf("%d", &n) == 1){
    printf("%d has %d positive divisors\n", n, num_divisors(n));
  }
  return 0;
}
