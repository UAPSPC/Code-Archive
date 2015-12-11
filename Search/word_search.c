/* Miscellaneous: Word Search
   =================================================================
   Description: Given a very long string, sometimes you have to find 
		a list of substrings in the string.  This program 
		will be faster than the obvious brute force solution.

   Complexity:	O(N*M lg N) setup, O(M lg N) each query
		where N is the length of your string,
		M is the length of your substring.
   -----------------------------------------------------------------
   Author:	Ashley Zinyk
   Date:	March 12, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes: 	If you want to find out how many instances of the
		substring B appear in the substring A, find the
		index of last, subtract the index of the first, and
		add 1.  Remember to return 0 if you couldn't find
		at least one.
		The buffer for your long string should be at least
		sizeof(longest string) + sizeof(longest substring) + 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxm;
int ptrcmp(const void *aa, const void *bb) {
  char *a = *(char **)aa;
  char *b = *(char **)bb;
  int res = strncmp(a,b,maxm);
  return (res) ? res : a-b;
  /* if two substrings are the same, keep them in their
     original order */
}

/* to find the first instance of the key, make fl = 0
   to find the last instance of the key, make fl = 1 */
int getindex(char *key, char **ptrs, int n, int fl) { 
  int lng, res, mid, upp = n, low = 0;

  lng = strlen(key);
  while (1) {
    mid = (upp+low)/2;
    res = strncmp(key,ptrs[mid],lng);
    if (!res) {
      if (fl) {
        if (mid != n-1 && !strncmp(ptrs[mid+1],key,lng)) low = mid;
        else return mid;
      } else {
        if (mid != 0 && !strncmp(ptrs[mid-1],key,lng)) upp = mid;
        else return mid;
      }
    } else if (res < 0) {
      if (low==mid) return -1;
      low = mid;
    } else {
      if (upp==mid) return -1;
      upp = mid;
    }
  }
}

/* str is the string you are searching in
   n is the number of characters in the long string
   k is the number of characters in the longest substring */
void makeptrs(char *str, int n, char **ptrs, int k) {
  int i;

  for (i = 0; i < k; i++) str[n+k] = '\0';
  for (i = 0; i < n; i++) ptrs[i] = &str[i];
  maxm = k;
  qsort(ptrs[i], n, sizeof(char *), ptrcmp);
}

char message[1001000];
char *ptrs[1001000];
char word[1000];

int main() {
  int i, n, m, first;

  scanf("%d",&n);
  n *= 64; /* The SETI problem had n 64-byte lines */
  for (i = 0; i < n; i+=64)
    scanf("%s",&message[i]); /* input the string */
  makeptrs(message,n,ptrs,30);
  scanf("%d",&m);
  for (i = 0; i < m; i++) {
    scanf("%s",word);
    first = getindex(word,ptrs,n,0);
    if (first < 0) {
      printf("%s not found\n",word);
    } else {
      printf("There are %d instances of %s in the message\n",
             getindex(word,ptrs,n,1)-first+1,word);
      printf("The first instance was found at index %d\n",first);
    }
  }
  return 0;
}
