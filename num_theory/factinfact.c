/* Number Theory: Factors in Factorial
   =================================================================
   Description: How many factors of k are there in n! (n factorial)?

   Complexity:  O(lg(n)) if k is prime
                O(n) to generate primes in general case
   -----------------------------------------------------------------
   Author:      Ashley Zinyk
   Date:        February 11, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 3 (Spain 160, 568, 10061)
   Notes:       If k is guaranteed prime, just use pfif().
                It only makes sense when k >= 2, n >= 0.
*/

#include <stdio.h>

int pfif(int k, int n) {
  int pow, sum = 0;

  for (pow = k; pow <= n; pow *= k)
    sum += n / pow;
  return sum;
}

int primes[4800];

void getPrimes(){
  int i, j, isprime, psize = 1;

  primes[0] = 2;
  for(i = 3; i <= 46340; i+= 2){
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

int fif(int k, int n) {
  int i, p, m, tmp, min = 2000000000;
  
  for (i = 0; k > 1; i++) {
    p = primes[i];
    if (p*p > k) p = k;
    for (m = 0; k % p == 0; m++) k /= p;
    if (!m) continue;
    tmp = pfif(p,n)/m;
    if (tmp < min) min = tmp;
  }
  return min;
}

int main() {
  int n, k;
  
  getPrimes();
  while (scanf("%d %d",&n, &k)==2)
    printf("There's %d factor(s) of %d in %d!\n",fif(k,n),k,n);
  return 0;
}
