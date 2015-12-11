/* Arithmetic: Binomial coefficient
   =================================================================
   Description: Given n objects in total, returns the number of ways
                to choose k of those objects with no regard to order
		
   Complexity:  O(N^2) to generate table
                O(1) lookup cost
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 16, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       This program is accurate to up to n = 68.  At n = 69
                there is a slight deviation.  Note that all results
		with n <= 68 are representable exactly by 
		floating point.
*/

#include <stdio.h>
#include <float.h>

#define MAXN 100

long double bin[MAXN+1][MAXN+1];

void getBinCoeff(){
  int i, k;

  for(k = 0; k <= MAXN; k++){
    bin[k][0] = bin[k][k] = 1;
    for(i = 1; i < k; i++)
      bin[k][i] = bin[k-1][i-1]+bin[k-1][i];
  }
}

int main(){
  int n,k;
  
  getBinCoeff();

  while(scanf("%d %d", &n, &k) == 2){
    printf("%d C %d = %.0Lf\n", n,k,bin[n][k]);
  }
  return 0;
}
