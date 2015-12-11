/* Miscellaneous: Roman Numerals
   =================================================================
   Description:  Converts an arabic number (as an int) to roman 
		numerals (as a null-terminated string) and vice versa.

   Complexity:	O(1)
   -----------------------------------------------------------------
   Author:	Ashley Zinyk
   Date:	March 07, 2003
   References:  http://www.wilkiecollins.demon.co.uk/roman/front.htm
   -----------------------------------------------------------------
   Reliability: 0
   Notes: 	Remember that the romans didn't use negative
		numbers or the number zero, so those aren't valid
		numbers.  Numbers greater than or equal to 5000
		aren't valid either; those roman numbers can't 
		easily be represented in ASCII.  

		The romans didn't have well-defined numbers; this
		implementation uses the rules you see for dating
		television shows, so things like IX are legal, 
		but IM is not.
*/

#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
using namespace std;

map<string, int, less <string> > dict;

char nums[5000][20];

void gen_roman() {
  char *roman[13] = 
    {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
  int i, j, n, arab[13] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
  string key;

  for (i = 0; i < 5000; i++) {
    nums[i][0] = 0;
    for (n = i, j = 0; n; j++)
      for (; n >= arab[j]; n -= arab[j]) 
        strcat(nums[i],roman[j]);
    key = nums[i];
    dict[key] = i;
  }
}

char *to_roman(int n) {
  if (n < 1 || n >= 5000) return 0;
  return nums[n];
}

int to_arabic(char *in) {
  string key = in;

  if (!dict.count(key)) return -1;
  return dict[key];
}

int main() {
  int i;

  gen_roman();
  for (i = 1; i < 5000; i++)
    printf("%d = %s\n",to_arabic(to_roman(i)),to_roman(i));
  return 0;
}
