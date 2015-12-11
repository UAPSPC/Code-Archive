/* Generators: Pythagorean Triples
   =================================================================
   Description: A Pythagorean triple is a set of three positive
                integers a < b < c such that a^2 + b^2 = c^2.  A
                primitive triple has the property that a,b,c are
                relatively prime.  Given N, this code generates
                all the primitive triples such that c < N.

   Complexity:  O(N)
   -----------------------------------------------------------------
   Author:      Ashley Zinyk
   Date:        Dec 15, 2002
   References:  Leonhard Euler, so you know it's fast.
   -----------------------------------------------------------------
   Reliability: 1 (Spain 106)
   Notes:       There will be no more than N/4 triples generated;
                allocate this much space.  The function will 
                return the actual number of triples generated.
                The triples will be in no particular order; you may
                want to sort the results after generating them.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int a, b, c;
} ptrip;

int gcd(int a, int b) {
  int r;

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int gen_triples(int n, ptrip *res) {
  int a, b, p, q, cnt = 0;

  for (p = 2; p*p < n; p++) {
    for (q = 1+p%2; q < p && p*p+q*q < n; q += 2) {
      if (gcd(p,q)!=1) continue;
      a = p*p-q*q;
      b = 2*p*q;
      if (a < b) { res[cnt].a = a; res[cnt].b = b; }
      else       { res[cnt].a = b; res[cnt].b = a; }
      res[cnt++].c = p*p+q*q;
    }
  }
  return cnt;
} 

int main() {
  ptrip *arra = NULL;
  int i, max, ntrip;

  while (scanf("%d",&max)==1) {
    arra = realloc(arra,sizeof(ptrip)*max/4);
    ntrip = gen_triples(max,arra);
    printf("%d\n",ntrip);
    for (i = 0; i < ntrip; i++)
      printf("%d %d %d\n", arra[i].a, arra[i].b, arra[i].c);
  }
  return 0;
}
