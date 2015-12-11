/* Number Theory: Primality testing with a sieve
   =================================================================
   Description: Fast primality testing using a sieve implementation.

		- getPrimes(maxn) sets bits in the array primes.
		- if the number of primes <= maxn is desired, 
		  uncomment out the specified region.
                - use isPrime(x) to check if x is prime
	      
   Complexity:  roughly O(N^(1.5))
   -----------------------------------------------------------------
   Author:      Gilbert Lee, Ashley Zinyk
   Date:        Dec 06, 2002
   References:  http://www.fpx.de/fp/Software/Sieve.html
   -----------------------------------------------------------------
   Reliability: 0                  
   Notes:       Running times: (P3 1.0Ghz)     Time         Time
                     N      # Primes <= N    w/ psize    w/o psize
                ----------------------------------------------------
		        100            25    0m0.004s     0m0.004s    
		      1 000           168    0m0.004s     0m0.004s
	 	     10 000         1 229    0m0.004s     0m0.004s
 		    100 000         9 592    0m0.006s     0m0.005s
	          1 000 000        78 498    0m0.025s     0m0.017s
	         10 000 000       664 579    0m0.587s     0m0.508s
		100 000 000     5 761 455    0m8.5050s    0m7.711s

*/

#include <stdio.h>
#include <stdlib.h>

#define TEST(f,x) (*(f+(x)/16)&(1<<(((x)%16L)/2)))
#define SET(f,x)  *(f+(x)/16)|=1<<(((x)%16L)/2)

#define ONEPRIME 0  /* whether or not 1 is considered to be prime */
#define UL unsigned long
#define UC unsigned char
 
UC *primes = NULL;

UL getPrimes(UL maxn){
  UL x, y, psize=1;

  primes = calloc(((maxn)>>4)+1L, sizeof(UC));
  for (x = 3; x*x <= maxn; x+=2)
    if (!TEST(primes, x)) 
      for (y = x*x; y <= maxn; y += x<<1) SET (primes, y);
  
  /* Comment out if you don't need # of primes <= maxn */
  for(x = 3; x <= maxn; x+=2)
    if(!TEST(primes, x)) psize++;

  return psize;
}

/* Returns whether or not a given POSITIVE number if prime. */
int isPrime(UL x){
  if(x == 1) return ONEPRIME;
  if(x == 2) return 1;
  if(x % 2 == 0) return 0;
  return (!TEST(primes, x));
}

int main(){
  UL x, maxn, psize;

  printf("Enter upper limit\n");
  scanf("%ld", &maxn);

  psize = getPrimes(maxn);
  printf ("%ld prime numbers found up to %ld.\n\nEnter numbers to test: ",
	  psize, maxn);

  while(scanf("%ld", &x)==1 && x <= maxn && x){
    if(isPrime(x)) printf("%ld is prime.\n",x);
    else printf("%ld is not prime.\n",x);
  }
  
  free (primes);
  return 0;
}

