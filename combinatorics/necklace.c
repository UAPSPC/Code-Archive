/* Combinatorics: Necklace/Bracelet Enumeration
   =================================================================
   Description: Calculate the number of necklaces/bracelets with N
                beads of K different colors. 
		
		Necklaces are unique up to rotation while bracelets
		can be reflected as well (i.e. mirror images count
		only once)
   
   Complexity:  O(N^2)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Nov 13, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 1 Successful use (Spain 10294)
   Notes:       Burnside Lemma's states that the number of such is
                equal to the total sum of all invariants / # of
		transformations. 
                Basically, this is what the algorithm calculates.
*/

#include <stdio.h>
#include <string.h>

#define MAXN 51

int seen[MAXN];

double getNecklaces(int n, int t){
  int r, i, pos;
  double p, sum = 0;

  for(r = 0; r < n; r++){
    memset(seen, 0, sizeof(seen));
    p = 1;
    for(i = 0; i < n; i++){
      if(seen[i]) continue;
      p *= t;
      seen[i] = 1;
      pos = i;
      while(!seen[(pos+r)%n]){
	pos += r;
	pos %= n;
	seen[pos] = 1;
      }
    }
    sum += p;
  }
  return sum/n;
}
 
double getBracelets(int n, int t){
  int r, i, pos;
  double p, sum;

  sum = n*getNecklaces(n, t);
  for(r = 0; r < n; r++){
    memset(seen, 0, sizeof(seen));
    p = 1;
    for(i = 0; i < n; i++){
      if(seen[i]) continue;
      p *= t;
      pos = i;
      while(!seen[(2*n-(pos+r))%n]){
	pos = (2*n-(pos+r))%n;
	seen[pos] = 1;
      }
    }
    sum += p;
  }
  return sum/(2*n);
}

int main(){
  int n, k;
  
  while(scanf("%d %d", &n, &k) == 2){
    printf("%.0f %.0f\n", getNecklaces(n,k), getBracelets(n,k));
  }
  return 0;
}
