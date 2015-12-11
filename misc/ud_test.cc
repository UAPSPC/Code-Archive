/* Misc: Uniquely Decipherable Codes Test
   =================================================================
   Description: A set of code words is said to be uniquely 
                decipherable if every possible message can be broken
		down into the code words in only one unique way.
		
		E.g. {0,01} is UD, where {0,1,01} is not since the
		     message 01 can be either [01] or [0][1]

		isUDTest(codewords) returns 1 if the codewords are
		                    UD and 0 otherwise.
		
   Complexity:  O(N^2 * L^2) where N is # of codewords, L is maximum
                             length of a code word
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        March 13, 2003
   References:  Graph Algorithms - Shimon Even - pg. 69-70
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       - Note that prefix-free codes (e.g. Huffman) are UD
                  but some non-prefix-free codes are UD ({0,01})
		- Use ud_find.cc if you want to find a minimum length
		  string which is not uniquely decipherable.
		- The routine handles all characters (including 
		  spaces if necssary): just change input format
*/

#include <stdio.h>
#include <string>
#include <vector>
#include <set>

using namespace std;

#define MAXL 200           /* Max codeword length */
#define VS vector<string> 

#define SS(x)      (x.size())
#define TAIL(x,y)  y.substr(SS(x),SS(y)-SS(x))
#define ADD(x,y)   s.insert(TAIL(x,y));tails.push_back(TAIL(x,y))
#define PRE(x,y)   (SS(x) < SS(y) && x==y.substr(0,SS(x)))
#define CHECK(x,y) if(PRE(x,y) && !s.count(TAIL(x,y))){ADD(x,y);}
		       
int isUDTest(VS code){
  int i, j, n = code.size(); VS tails; 
  set<string> s; string t;

  tails.clear(); s.clear();
  for(i = 0; i < n; i++)
    for(j = i+1; j < n; j++){
      if(code[i] == code[j]) return 0;
      CHECK(code[i], code[j]);
      CHECK(code[j], code[i]);
    }
  for(i = 0; i < (int)tails.size(); i++)
    for(j = 0; j < n; j++){
      if(tails[i] == code[j]) return 0;
      CHECK(tails[i], code[j]);
      CHECK(code[j], tails[i]);
    }
  return 1;
}

int main(){
  int i, n; char buff[MAXL]; VS code;

  while(scanf("%d", &n) == 1){
    code.clear();
    for(i = 0; i < n; i++){
      scanf(" %s", buff);
      code.push_back(buff);
    }
    printf("%s\n", isUDTest(code) ? "YES" : "NO");
  }
  return 0;
}
