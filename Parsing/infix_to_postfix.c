/* Parsing: Converting infix to postfix
   =================================================================
   Description: Given a infix expression in a string, as well as
                rules for prescedence of binary operators, returns
		the postfix version of the expression.
   
   Complexity:  O(N) where N is the size of the string
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 13, 2002
   References:  www.cs.usyd.edu.au/~loki/cs2ll/infix/InToPost.html
   -----------------------------------------------------------------
   Reliability: 1 successful use (Spain Problem 727) Sept 2002
   Notes:       The string should not contain any spaces.
*/

#include <stdio.h>
#include <string.h>

#define MAXN 1000
int pres[300];

void setPres(char op, int p){
  pres[(int)op] = p;
}

void infix_to_postfix(char *infix, char *post){
  int stack[MAXN];
  int head = 0, len = strlen(infix);
  int pos = 0, i;

  for(i = 0; i < len; i++){
    switch(infix[i]){
    case '(': stack[head++] = infix[i]; break;
    case ')':
      while(stack[--head] != '('){
	post[pos++] = stack[head];
      }
      break;
    case '+': case '-': case '*': case '/':
      while(head && pres[stack[head-1]] >= pres[(int)infix[i]]){
	post[pos++] = stack[--head];
      }
      stack[head++] = infix[i];
      break;
    default:
      post[pos++] = infix[i];	
    }
  }
  while(head){
    post[pos++] = stack[--head];
  }
  post[pos] = 0;
}

int main(){
  char infix[MAXN];
  char postfix[MAXN];
  
  setPres('+', 1);
  setPres('-', 1);
  setPres('*', 2);
  setPres('/', 2);

  while(scanf(" %s", infix) == 1){
    printf("Infix: [%s] ", infix);
    infix_to_postfix(infix, postfix);
    printf("Postfix: [%s]\n", postfix);
  }
  return 0;
}
