/* Combinatorics - Permutation index on distinct characters
   =================================================================
   Description: Given a string formed of distinct characters,
                returns the index of the permutation from 0..N!-1.
   
   Complexity:  O(N^2) where N is size of the string
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Nov 14, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       This does not work when characters can be the same
                for example: "aaba"
*/

#include <stdio.h>
#include <string.h>

int permdex (char *s){
  int i, j, size = strlen(s);
  int index = 0;
  
  for (i = 1; i < size; i++){
    for (j = i; j < size; j++)
      if (s[i-1] > s[j]) index ++;
    index *= size - i;
  }
  return index;
}

int main(){
  char s[100];

  while(scanf(" %s", s) == 1){
    printf("Index of %s = %d\n", s,  permdex(s));
  }
  return 0;
}
