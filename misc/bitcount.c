/* Miscellaneous: Bit Count
   =================================================================
   Description: Takes an integer value and returns the number of
                bits that are set to one.
   
   Complexity:  O(N) where N is the number of '1' bits.
   -----------------------------------------------------------------
   Author:      Patrick Earl
   Date:        Sept 25, 2002
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       As is, it accepts large unsigned values.  It can be
                modified to check larger integers by using long long
		instead of int.
*/

#include <stdio.h>

int bitcount(int a){
  int c = 0;
  
  while(a){
    c++;
    a &= a-1;
  }
  return c;
}

int main(){
  int a;
  
  while(scanf("%d", &a) == 1){
    printf("Number of 1 bits in %d is %d\n", a, bitcount(a));
  }
  return 0;
}
