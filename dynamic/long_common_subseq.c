/* Dynamic Programming: Longest Common Subsequence
   =================================================================
   Description: Given two arrays A and B with sizes n and m 
                respectively, compute the length of the longest
		common subsequence.  This routine also returns in 
		the array 's' a longest common subsequence (it
		may not be unique).  One can specify which one to
		choose when multiply longest common subsequences
		exist.
   
   Complexity:  O(N*M)
   -----------------------------------------------------------------
   Author:      Howard Cheng, Gilbert Lee
   Date:        Nov 19, 2002
   References:  www.ics.uci.edu/~eppstein/161/960229.html
   -----------------------------------------------------------------
   Reliability: 2 (Spanish Problem 10405, 10066) Dec 2002
   Notes:       - Added way to change type of array
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 20
#define Atype int
#define max(x,y) (((x)>(y))?(x):(y))

int LCS(Atype *A, int n, Atype *B, int m, Atype *s)
{
  int L[MAXN+1][MAXN+1];
  int i, j, k;
  
  for(i = n; i >= 0; i--) for(j = m; j >= 0; j--){
    if(i == n || j == m){
      L[i][j] = 0;
    } else if(A[i] == B[j]){
      L[i][j] = 1 + L[i+1][j+1];
    } else {
      L[i][j] = max(L[i+1][j], L[i][j+1]);
    }
  }
  
  /* The following is not needed if you are not interested in
     a longest common subsequence */

  k = 0;
  i = j = 0;
  while(i < n && j < m){
    if(A[i] == B[j]){
      s[k++] = A[i++];
      j++;
    } else if(L[i+1][j] > L[i][j+1]){
      i++;
    } else if(L[i+1][j] < L[i][j+1]){
      j++;
    } else {
      /* put tie-breaking conditions here */
      
      /* eg. pick the one that starts at the first one the earliest */
      j++;
    }
  }
  return L[0][0];
}

int main(void)
{
  Atype A[MAXN], B[MAXN], s[MAXN];
  int m, n, i, l;

  while (scanf("%d %d", &n, &m) == 2 && 1 <= n && 1 <= m &&
	 n <= MAXN && m <= MAXN) {
    for (i = 0; i < n; i++) scanf("%d", &A[i]);
    for (i = 0; i < m; i++) scanf("%d", &B[i]);
    l = LCS(A, n, B, m, s);
    for (i = 0; i < l; i++) printf("%d ", s[i]);
    printf("\nLen = %d\n", l);
  }
  return 0;
}
