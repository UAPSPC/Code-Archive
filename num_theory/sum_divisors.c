/* Number Theory: Sum of divisors
   =================================================================
   Description: Returns the sum of all the positive divisors for
                a positive integer N
   
   Complexity:  O(sqrt(N))
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 8, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 2 successful use Oct 2002, Topcoder SRM 101 (450 pt)
                (Spain: #382)
   Notes:       
*/

#include <stdio.h>
#include <math.h>

#define LL long long

LL sum_divisors(LL n){
  int i, count; LL res = 1;

  for(i = 2; i*i <= n; i++){
    count = 0;
    while(n % i == 0){
      n /= i;
      count++;
    }
    if(count) res *= ((pow(i, count+1)-1)/(i-1));
  }
  if(n > 1) res *= ((pow(n, 2)-1)/(n-1));
  return res;
}

int main(){
  LL n;
  
  while(scanf("%lld", &n) == 1){
    printf("The sum of all divisors of %lld is %lld\n", n, sum_divisors(n));
  }
  return 0;
}
