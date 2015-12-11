/* Dynamic Programming: Integer Parititoning
   =================================================================
   Description: Template for calculating the number of ways of 
                partitioning the integer N into M parts.
	      		
   Complexity:  O(N^2)
   -----------------------------------------------------------------
   Author:      Gilbert LEe
   Date:        Feb 10, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 1 (Spain 10313 Pay the Price)
   Notes:       A partition of a number N is a representation of 
                N as the sum of positive integers
		e.g. 5 = 1+1+1+1+1

		The number of ways of partitioning an integer N
		into M parts is equal to the number of ways of 
		partitioning the number N with the largest element
		being of size M.  This is best seen with a Ferres-
		Young diagram:
		Suppose N = 8, M = 3:

		4 = * * * *
                3 = * * * 
                1 = *
		    3 2 2 1
		By transposition from rows to columns, this equality
		can be seen.
		
		P(N, M) = P(N-1, M-1) + P(N-M, M)
		P(0, M) = P(N, 0) = 0
		P(N, 1) = 1
*/

#include <stdio.h>
#include <string.h>
#define MAXN 300
#define ULL unsigned long long

ULL A[MAXN+1][MAXN+1];

void Build(){
  int i, j;

  memset(A, 0, sizeof(A));
  A[0][0] = 1;
  for(i = 1; i <= MAXN; i++){
    A[i][1] = 1;
    for(j = 2; j <= i; j++)
      A[i][j] = A[i-1][j-1] + A[i-j][j];
  }
}

int main(){
  int n, m;
  
  Build();
  while(scanf("%d %d", &n, &m) == 2){
    printf("Partitions of %d into %d parts: %llu\n", n, m, A[n][m]);
  }
  return 0;
}
