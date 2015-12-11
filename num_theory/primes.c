/* Number Theory: Generating list of primes
   =================================================================
   Description: This routine generates primes up to MAXN and stores
                them in the array called primes[].  The number of 
		such primes is counted by psize.
   
   Complexity:  O(n^2)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Oct 23, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:            N      Primes up to N      Run time (P2 333MHz)
                ----------------------------------------------------
		       100              25            0m0.005s
		     1 000             168            0m0.006s
		    10 000           1 229            0m0.012s
		   100 000           9 592            0m0.118s
		 1 000 000          78 498            0m2.235s
		10 000 000         664 579           0m46.093s
		
  (Sqrt of INT_MAX) 46 340           4 792            0m0.045s

                - Don't forget to allocate enough room for the 
		  primes (MAXP).
	       - The sample program includes checking primes up to
	         INT_MAX (2^31-1)
*/

#include <stdio.h>

#define MAXN 46340
#define MAXP 5000

int primes[MAXP];
int psize;

void getPrimes(){
  int i, j, isprime;
  
  psize = 0;
  primes[psize++] = 2;
  for(i = 3; i <= MAXN; i+= 2){
    for(isprime = j = 1; j < psize; j++){
      if(i % primes[j] == 0){
	isprime = 0;
	break;
      }
      if(1.0*primes[j]*primes[j] > i) break;
    }
    if(isprime) primes[psize++] = i;
  }
}

int isPrime(int x){
  int i;
  
  if(x <= 1) return 0;
  for(i = 0; i < psize && primes[i]*primes[i] <= x; i++){
    if(x % primes[i] == 0) return 0;
  }
  return 1;
}

int main(){
  int i, x;

  getPrimes();
  printf("%d primes between 1 to %d\n", psize, MAXN);
  while(scanf("%d", &x) == 1){
    if(isPrime(x)) printf("%d is prime\n", x);
    else printf("%d is not prime\n", x);
  }
  return 0;
}
			 
