/* Miscellaneous: String Reverse
   =================================================================
   Description: Given a string of characters, reverse it.

   Complexity:	O(N)
   -----------------------------------------------------------------
   Author:	Ashley Zinyk
   Date:	March 14, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 1 (Spain 483)
   Notes: 	This is extremely simple but sometimes you forget.
*/

#include <stdio.h>
#include <string.h>

char *strrev(char *a) {
  int i, n = strlen(a);
  char tmp;

  for (i = 0; i < n/2; i++) {
    tmp = a[i];
    a[i] = a[n-i-1];
    a[n-i-1] = tmp;
  }
  return a;
}

int main() {
  char word[1000];

  while (scanf("%s",word)==1)
    printf("%s\n",strrev(word));
  return 0;
}
