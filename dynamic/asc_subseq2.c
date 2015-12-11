/* Dynamic Programming: Longest ascending subsequence (N^2 version)
   =================================================================
   Description: Given an array of size N, asc_seq returns the length
                of the longest ascending subsequence, and stores one
		such subsequence in the array S.

		Ascending is defined by cmp(A,B), which returns
		1 if A may come after B in the sequence, and 0
		otherwise
   
   Complexity:  O(N^2)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Jan 16, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       - To support other data types, just redefine Item
                  and cmp
                - Various cmp functions are included below
*/

#include <stdio.h>
#define MAXN 500

typedef int Item;

int cmp(Item a, Item b){
  return a >= b; /* Ascending (Nondecreasing) */
  return a > b;  /* Strictly ascending */
  return a <= b; /* Descending (Nonincreasing) */
  return a < b;  /* Strictly descending */
}

int longest(int n, Item *A, Item *S){
  int most = 0, mi, i, j, last[MAXN], len[MAXN];
  
  for(i = 0; i < n; i++){
    len[i] = 1;
    for(j = 0; j < i; j++)
      if(cmp(A[i], A[j]) && len[j]+1 > len[i]){
	len[i] = len[j]+1;
	last[i] = j;
      }
    if(len[i] > most){
      most = len[i];
      mi = i;
    }
  }

  /* Skip if you do not need to build S */
  for(i = most-1; i >= 0; i--){
    S[i] = A[mi];
    mi = last[mi];
  }
  return most;
}

int main(){
  int n, result, i;
  Item A[MAXN], S[MAXN];
  
  scanf("%d", &n);
  for(i = 0; i < n; i++) scanf("%d", &A[i]);
  result = longest(n, A, S);

  printf("Size of longest subsequence: %d\n", result);
  for(i = 0; i < result; i++) printf("%d ", S[i]);
  printf("\n");
  return 0;
}
