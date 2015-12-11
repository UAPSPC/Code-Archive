/* Number Theory: GCD of binary numbers (Algorithm B)
   =================================================================
   Description: Computes the greatest common divisor of two 
                integers expressed in binary. 
   
   Complexity:  O((lg2(uv))^2)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Dec 29, 2002
   References:  http://www.nist.gov/dads/HTML/binaryGCD.html
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       When efficiency isn't a big concern, the standard 
                gcd algorithm is probably a better choice.
*/

#include <stdio.h>
#include <stdlib.h>

int gcd_b(int u, int v){
  int g = 1, t;

  while(!(u & 1 || v & 1)){
    u >>= 1;
    v >>= 1;
    g <<= 1;
  }
  while(u){
    if(!(u&1)) u >>= 1;
    else if(!(v&1)) v >>= 1;
    else {
      t = abs(u-v)>>1;
      if(u < v) v = t;
      else u = t;
    }
  }
  return g*v;
}

int main(){
  int a, b;

  while(scanf("%d %d", &a, &b) == 2){
    printf("GCD %d %d = %d\n", a, b, gcd_b(a,b));
  }
  return 0;
}
