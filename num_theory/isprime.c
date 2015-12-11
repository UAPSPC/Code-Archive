/* Number Theory: Primality Testing
   =================================================================
   Description: This routine checks if a positive integer N is a
                prime.
   
   Complexity:  O(sqrt(N))
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 21, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       if 1 is to be considered a prime, set ONEPRIME to 1
                - if there is a lot of primality testing to be done
		  try using primesieve.c instead of isprime.c for
		  speed reasons.
*/

#include <stdio.h>
#include <math.h>

#define ONEPRIME 0

int isPrime(int x){
  int i;
  if( x == 1 ) return ONEPRIME;
  if( x == 2 ) return 1;
  if( x % 2 == 0) return 0;
  
  for(i = 3; i*i <= x; i+=2)
    if( x % i == 0) return 0;
  return 1;
}

int main(){
  int x;
  
  for(x = 1; x < 100; x++){
    if(isPrime(x))
      printf("%d is prime\n", x);
    else 
      printf("%d is not prime\n", x);
  }
  return 0;
}
