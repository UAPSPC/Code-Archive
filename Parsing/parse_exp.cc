/* Parsing: Arithmetic Expression Parsing Template
   =================================================================
   Description: A template for parsing arithmetic expressions.
                
                This version handles +,-,*,/,^, if all values
		and intermediate values fit within integers, as
		well as a variable mapping

   Complexity:  O(n)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Oct 22, 2003
   References:  Based on code by Kisman
   -----------------------------------------------------------------
   Reliability: 1 (Topcoder 2003 TCO Online Round 2 1000 pt)
   Notes:       - Doesn't handle overflow, but may be fixed by 
                  changing types or explicit checking
                - Doesn't handle division by 0
		- Doesn't handle whitespace
*/

#include <stdio.h>
#include <string>
#include <math.h>
#include <map>

using namespace std;

map<string, int> var;

int ParseExp(string e){
  int p, x, a, b;
  for(x = e.size()-1, p = 0; x >= 0; x--){
    p += (e[x] == ')') - (e[x] == '(');
    if(!p && (e[x] == '+' || e[x] == '-')){
      a = ParseExp(e.substr(0,x));
      b = ParseExp(e.substr(x+1));
      // Check overflow - underflow here
      return e[x] == '+' ? a+b : a-b;
    }
  }
  for(x = e.size()-1, p = 0; x >= 0; x--){
    p += (e[x] == ')') - (e[x] == '(');
    if(!p && (e[x] == '*' || e[x] == '/')){
      a = ParseExp(e.substr(0,x));
      b = ParseExp(e.substr(x+1));
      // Check overflow - underflow & div/0 here
      return e[x] == '*' ? a*b : a/b;
    }
  }
  for(x = e.size()-1, p = 0; x >= 0; x--){
    p += (e[x] == ')') - (e[x] == '(');
    if(!p && e[x] == '^'){
      a = ParseExp(e.substr(0,x));
      b = ParseExp(e.substr(x+1));
      // Check overflow here
      return (int)pow((double)a,b);
    }
  }
  if(e[0] == '(') return ParseExp(e.substr(1,e.size()-2));
  if(isdigit(e[0])) return atoi(e.c_str());
  return var[e];
}

int main(){
  int numv, i, x; char buff[1000];

  /* Read in number of variables */
  scanf("%d", &numv);
  
  /* Read in variables and their assignments into the map */
  var.clear();
  for(i = 0; i < numv; i++){
    scanf("%s %d", buff, &x);
    var[buff] = x;
  }

  /* Read expression */
  while(scanf("%s", buff) == 1)
    printf("[%s] = %d\n", buff, ParseExp(buff));

  return 0;
}

