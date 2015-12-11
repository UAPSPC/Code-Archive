/* Misc: Uniquely Decipherable Codes 
   =================================================================
   Description: A set of code words is said to be uniquely 
                decipherable if every possible message can be broken
		down into the code words in only one unique way.
		
		E.g. {0,01} is UD, where {0,1,01} is not since the
		     message 01 can be either [01] or [0][1]

		UDFind(codewords) returns an empty string is the
		codewords are UD, otherwise the smallest
		lexicographic message that is not UD.
		
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
		- Use ud_test.cc if you only want to test if a set 
		  of codewords is UD.
		- The routine handles all characters (including 
		  spaces if necssary): just change input format
*/

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

#define MAXL 200           /* Maximum length of a codeword */
#define VS vector<string>

#define SS(x)       (x.size())
#define TAIL(x,y)   y.substr(SS(x),SS(y)-SS(x))
#define ADD(x,y)    s.insert(TAIL(x,y));c.a=x;c.b=TAIL(x,y);tails.push(c)
#define ADD2(x,y)   c.a=top.a+x;c.b=TAIL(x,y);tails.push(c)
#define PRE(x,y)    (SS(x) < SS(y) && x==y.substr(0,SS(x)))
#define CHECK(x,y)  if(PRE(x,y) && !s.count(TAIL(x,y))){ADD(x,y);}
#define CHECK2(x,y) if(PRE(x,y) && !s.count(TAIL(x,y))){ADD2(x,y);}

struct Code{
  string a,b;
  bool operator<(const Code &o) const{
    string x = a+b; string y = o.a+o.b;
    return (SS(x)>SS(y)) || (SS(x)==SS(y) && x>y);
  }
};

bool cmpSS(const string &a, const string &b){
  return SS(a) < SS(b) || (SS(a) == SS(b) && a < b);
}

string UDFind(VS code){
  int i, j, n = code.size(); string t; Code c;
  set<string> s;               /* Mark tails already seen */
  priority_queue<Code> tails;  /* Keep track of current tails */

  sort(code.begin(), code.end(), cmpSS);
  s.clear();
  for(i = 0; i < n; i++) for(j = i+1; j < n; j++){
    if(code[i] == code[j]) return code[i];
    CHECK(code[i], code[j]);
    CHECK(code[j], code[i]);
  }
  s.clear();
  while(!tails.empty()){
    Code top = tails.top(); tails.pop();
    if(s.count(top.b)) continue;
    s.insert(top.b);
    for(j = 0; j < n; j++){
      if(top.b == code[j]) return top.a+top.b;
      CHECK2(top.b, code[j]);
      CHECK2(code[j], top.b);
    }
  }
  return "";
}

int main(){
  int i, n; char buff[MAXL]; VS code;

  while(scanf("%d", &n) == 1){
    code.clear();
    for(i = 0; i < n; i++){
      scanf(" %s", buff);
      code.push_back(buff);
    }
    printf("[%s]\n", UDFind(code).c_str());
  }
  return 0;
}
