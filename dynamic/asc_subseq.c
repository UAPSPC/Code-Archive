/* Dynamic Programming: Longest Ascending Subsequence
   =================================================================
   Description: Given an array of size n, asc_seq returns the length 
                of the longest ascending subsequence, as well as one
	        of the subsequences in S.
		
		sasc_seq returns the length of the longest strictly
		ascending subsequence.
   
   Complexity:  O(n log n)
   -----------------------------------------------------------------
   Author:      Howard Cheng / Gilbert Lee
   Date:        Oct 25, 2002
   References:  Gries, D. The Science of Programming
   -----------------------------------------------------------------
   Reliability: 0/0
   Notes:       If you want to do the same things with descending
                subsequences, just reverse the array before calling
		the routines.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int asc_seq(int *A, int n, int *S){
  int *m, *seq, i, k, low, up, mid, start;
  
  m   = malloc((n+1) * sizeof(int));
  seq = malloc(n * sizeof(int));
  /* assert(m && seq); */
  
  for (i = 0; i < n; i++) seq[i] = -1;  
  m[1] = start = 0;
  for (k = i = 1; i < n; i++) {
    if (A[i] >= A[m[k]]) {
      seq[i] = m[k++];
      start = m[k] = i;
    } else if (A[i] < A[m[1]]) {
      m[1] = i;
    } else {
      /* assert(A[m[1]] <= A[c] && A[c] < A[m[k]]); */
      low = 1;
      up = k;
      while (low != up-1) {
	mid = (low+up)/2;
	if(A[m[mid]] <= A[i]) low = mid;
	else up = mid;
      }
      seq[i] = m[low];
      m[up] = i;
    }
  }
  for (i = k-1; i >= 0; i--) {
    S[i] = A[start];
    start = seq[start];
  }
  free(m); free(seq);
  return k;
}

int sasc_seq(int *A, int n, int *S){
  int *m, *seq, i, k, low, up, mid, start;
  
  m   = malloc((n+1) * sizeof(int));
  seq = malloc(n * sizeof(int));
  /* assert(m && seq); */
  
  for (i = 0; i < n; i++) seq[i] = -1;
  m[1] = start = 0;
  for (k = i = 1; i < n; i++) {
    if (A[i] > A[m[k]]) {
      seq[i] = m[k++];      
      start = m[k] = i;
    } else if (A[i] < A[m[1]]) {
      m[1] = i;
    } else if (A[i] < A[m[k]]) {
      low = 1;
      up = k;
      while (low != up-1) {
	/* assert(A[m[h]] <= A[c] && A[c] < A[m[j]]); */
	mid = (low+up)/2;
	if(A[m[mid]] <= A[i]) low = mid;
	else up = mid;
      }
      if (A[i] > A[m[low]]) {
	seq[i] = m[low];
	m[up] = i;
      }
    }
  }
  for (i = k-1; i >= 0; i--) {
    S[i] = A[start];
    start = seq[start];
  } 
  free(m); free(seq);
  return k;
}

int main(void)
{
  int *A, *S, n, i, k;
  
  while (scanf("%d", &n) == 1 && n > 0) {
    A = malloc(n*sizeof(int));
    S = malloc(n*sizeof(int));

    /* Read in array */
    for (i = 0; i < n; i++) scanf("%d", &A[i]);

    /* Find longest ascending subsequence */
    k = asc_seq(A, n, S);
    printf("length = %d\n", k);
    for (i = 0; i < k; i++){
      printf("%d ", S[i]);
    }
    printf("\n");
    
    /* Find longest strictly ascending subsequence */
    k = sasc_seq(A, n, S);
    printf("length = %d\n", k);
    for (i = 0; i < k; i++) {
      printf("%d ", S[i]);
    }
    printf("\n");
    free(A);
    free(S);
  }
  return 0;
}
