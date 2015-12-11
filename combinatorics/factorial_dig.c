/* Combinatorics: Digits in N!
   =================================================================
   Description: Given N, computes the number of digits that N! will
                occupy in base B.
   
   Complexity:  O(N)
   -----------------------------------------------------------------
   Author:      Gilbert Lee, Ashley Zinyk
   Date:        Feb 14, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 1 (Problem B - Big Number Feb 11, 2003)
   Notes:       The results fit nicely in doubles up to N = 10^7, but
                run time may be slow.  

                Returns 1 for n < 0, although technically undefined.
                The base must be larger than 1.
*/

#include <stdio.h>
#include <math.h>

long long fac_digit(int n, int b) {
  double sum = 0; int i;
  
  for (i = 2; i <= n; i++) sum += log(i);
  return (long long) floor(1+sum/log(b));  /* don't use ceil! */
}

int main() {
  int n, b;
  
  while (scanf("%d %d", &n, &b)==2) {
    printf("%d! has %lld symbol(s) when represented "
           "in base %d\n", n, fac_digit(n,b), b); 
  }
  return 0;
}
