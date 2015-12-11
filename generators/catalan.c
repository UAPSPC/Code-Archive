/* Generator: Catalan Numbers
   =================================================================
   Description: Generates the first few catalan numbers
   
   Complexity:  O(n)
   -----------------------------------------------------------------
   Author:      Ashley Zinyk
   Date:        Dec 07, 2002
   References:  None.
   -----------------------------------------------------------------
   Reliability: 1
   Notes: The sequence of catalan numbers grows pretty quickly.  
      For n > 33, long longs are too small, so use the same
      algorithm with bignum.

      You may want to tweak the zeroth catalan number so that it 
      has meaning in your application (for instance, how many 
      ways are there to bracket zero terms?
*/

#include <stdio.h>

long long int cat[33];

void getcat() {
  int i;

  cat[0] = cat[1] = 1;
  for (i = 2; i < 33; i++)
    cat[i] = cat[i-1]*(4*i-6)/i;
}

int main() {
  int i;

  getcat();
  for (i = 0; i < 33; i++) {
    printf("%lld\n",cat[i]);
  }

  return 0;
}

