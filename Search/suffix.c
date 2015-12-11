/* Searching: Suffix array
   =================================================================
   Description: Builds a suffix array of a string of N characters
   
   Complexity:  O(N log N)
   -----------------------------------------------------------------
   Author:      Howard Cheng
   Date:        Oct 30, 2003
   References:  Manber, U. and Myers, G.  "Suffix Arrays: a New
                Method for On-line String Searches." 
                SIAM Journal on Computing.  22(5) p. 935-948, 1993.

		T. Kasai, G. Lee, H. Arimura, S. Arikawa, and
                K. Park.  "Linear-time Longest-common-prefix
                Computation in Suffix Arrays and Its Applications."
                Proc. 12th Annual Conference on Combinatorial
		Pattern Matching, LNCS 2089, p. 181-192, 2001

   -----------------------------------------------------------------
   Reliability: 1 (Spain 719 - Glass Beads)
   Notes:      The build_sarray routine takes in a string S of n
               characters (null-terminated), and constructs two
               arrays sarray and lcp.  The properties are:

             - If p = sarray[i], then the suffix of str starting at
               p (i.e. S[p..n-1] is the i-th suffix when all the
               suffixes are sorted in lexicographical order

             - NOTE: the empty suffix is not included in this list,
                     so sarray[0] != n.

             - lcp[i] contains the length of the longest common
               prefix of the suffixes pointed to by sarray[i-1]
               and sarray[i].  lcp[0] is defined to be 0.

             - To see whether a pattern P occurs in str, you can
               look for it as the prefix of a suffix.  This can be
               done with a binary search in O(|P| log n) time.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define MAXN 100000
int bucket[CHAR_MAX-CHAR_MIN+1];
int prm[MAXN], count[MAXN];
char bh[MAXN+1];

void build_sarray(char *str, int* sarray, int *lcp){
  int n, a, c, d, e, f, h, i, j, x;
  
  n = strlen(str);
  
  /* sort the suffixes by first character */
  memset(bucket, -1, sizeof(bucket));

  for (i = 0; i < n; i++) {
    j = str[i] - CHAR_MIN;
    prm[i] = bucket[j];
    bucket[j] = i;
  }

  for (a = c = 0; a <= CHAR_MAX - CHAR_MIN; a++) {
    for (i = bucket[a]; i != -1; i = j) {
      j = prm[i];
      prm[i] = c;
      bh[c++] = (i == bucket[a]);
    }
  }
  bh[n] = 1;
 
  for (i = 0; i < n; i++)
    sarray[prm[i]] = i;
  
  /* inductive sort */
  x = 0;
  for (h = 1; h < n; h *= 2) {
    for (i = 0; i < n; i++) {
      if (bh[i] & 1) {
	x = i;
	count[x] = 0;
      }
      prm[sarray[i]] = x;
    }
    
    d = n - h;
    e = prm[d];
    prm[d] = e + count[e];
    count[e]++;
    bh[prm[d]] |= 2;
    
    i = 0;
    while (i < n) {
      for (j = i; (j == i || !(bh[j] & 1)) && j < n; j++) {
	d = sarray[j] - h;
	if (d >= 0) {
	  e = prm[d];
	  prm[d] = e + count[e];
	  count[e]++;
	  bh[prm[d]] |= 2;
	}
      }
      
      for (j = i; (j == i || !(bh[j] & 1)) && j < n; j++) {
	d = sarray[j] - h;
	if (d >= 0 && bh[prm[d]] & 2) {
	  for (e = prm[d]+1; bh[e] == 2; e++) ;
	  for (f = prm[d]+1; f < e; f++) {
	    bh[f] &= 1;
	  }
	}
      }
      i = j;
    }
    
    for (i = 0; i < n; i++) {
      sarray[prm[i]] = i;
      if (bh[i] == 2) {
	bh[i] = 3;
      }
    }
  }
  
  h = 0;
  for (i = 0; i < n; i++) {
    e = prm[i];
    if (e > 0) {
      j = sarray[e-1];
      while (str[i+h] == str[j+h]) {
	h++;
      }
      lcp[e] = h;
      if (h > 0) {
	h--;
      }
    }
  }
  lcp[0] = 0;
}

int main(){
  char S[MAXN]; int sarray[MAXN], lcp[MAXN], i;
  char T[MAXN];
  int n, j;
  while (scanf("%s", S) == 1) {
    n = strlen(S);
    for(i = 0; i < n; i++) S[n+i] = S[i];
    S[n+n] = 0;
    build_sarray(S, sarray, lcp);
    for (i = 0; S[i]; i++)
      if(sarray[i] < n){
	printf("%3d: %2d [%d]\n", i, lcp[i], n);
	for(j = 0; j < n; j++){
	  printf("%c", S[sarray[i]+j]);
	}
	printf("\n");
      }
  }
  return 0;
}
