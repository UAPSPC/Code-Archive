/* Combinatorics: Digit Occurence count
   =================================================================
   Description: Given a digit and a number N, return the number of 
                times the digit occurs from 1..N.
   
   Complexity:  O(lg N)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        May 22, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
  
long long digit_count(int digit, int max){
  long long res = 0;
  char buff[15];
  int i, count;

  if(max <= 0) return 0;

  /* Number of times "digit" occurs in the one's place */
  res += max/10 + ((max % 10) >= digit ? 1 : 0);
  
  /* Since we start from 1, if digit = 0, remove 1 since "0"
     doesn't count */
  if(digit == 0) res--;
  
  /* Get the number of occurences in max/10-1, and multiply this by
     10 since we can choose 10 possible last digits [0-9] */
  res += digit_count(digit, max/10 - 1) * 10;
  
  /* The number of occurences in max/10 is equal to (1+max%10) * the
     number of times "digit" occurs in max/10 */
  sprintf(buff, "%d", max/10);
  for(i = 0, count = 0; i < strlen(buff); i++)
    if(buff[i] == digit+'0') count++;
  
  res += (1 + max%10) * count;
  return res;
}

int main(){
  int digit, max;
  
  while(1){
    printf("Enter a digit and a number: ");
    scanf("%d %d", &digit, &max);
    printf("The number of times '%d' occurs from 1..%d = %lld\n", 
           digit, max, digit_count(digit, max));
  }
  return 0;
}
