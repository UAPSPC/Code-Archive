/* Parsing: Evaluating Arithmetic Expressions
   =================================================================
   Description: Given a infix expression in a string, the parser
                evaluates the string and reports errors if the
                parsing fails or the evaluation causes a division by
                zero.
   
   Complexity:  O(N) where N is the size of the string
   -----------------------------------------------------------------
   Author:      Patrick Earl
   Date:        Nov 14, 2002
   -----------------------------------------------------------------
   Reliability: 0
   Notes:  Leading zeros are handled.
           By default, the code uses long long, but it cannot handle
           the minimum long long value, only that value plus one.
           Overflow in the math operations is not checked.
           Whitespace is ignored.

   Expressions follow this grammar:
       Expr = Term (('+'|'-') Term) *
       Term = Factor (('*'|'/') Factor) *
       Factor = Unit | ('+'|'-')? Factor
       Unit = LongLongInteger | '('Expr')'
*/

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

enum {
  SUCCESS,
  DIV_BY_ZERO,     /* A division by zero would have occured. */
  PARSE_UNEXPECTED,/* Unexpected character.  Also reported for empty
                      string. */
  PARSE_TOOLONG,   /* Extra non-whitespace junk after complete
                      expression has been parsed. */
  PARSE_OVERFLOW,  /* Integer is too long to fit in an int. */
  PARSE_NOPAREN    /* No matching parentheses. */
};

/* If you change this, you need to change the low level parsing as well. */
typedef long long TYPE;

char *s;
int pos;
int error;

char gc() {
  while(isspace(s[pos])) pos++;
  return s[pos++];
}

void ugc() {
  pos--;
}

TYPE Expr();

TYPE Unit() {
  char c;
  TYPE expr;
  char num[100];
  char *ref;
  int p, zero;

  c = gc();

  if(c == '(') {
    expr = Expr();
    if(error) return 0;
    if(gc() != ')') {
      error = PARSE_NOPAREN;
      return 0;
    }
    return expr;
  } else if(isdigit(c)) {
    p=0;
    zero=1;
    while(isdigit(c)) {
      if(zero && c=='0') {
        c=gc();
        continue;
      }
      zero=0;
      num[p++]=c;
      if(p > 19) {
        error = PARSE_OVERFLOW;
        return 0;
      }
      c=gc();
    }
    ugc();
    if(zero) num[p++]='0';
    num[p]=0;

    /* The largest 64 bit long long value. */
    ref = "9223372036854775807";
    if(strlen(num) == strlen(ref) && strcmp(num, ref) > 0) {
      error = PARSE_OVERFLOW;
      return 0;
    }

    if(sscanf(num,"%lld",&expr) != 1) {
      error = PARSE_OVERFLOW;
      return 0;
    }

    return expr;
  } else {
    error=PARSE_UNEXPECTED;
    return 0;
  }
}

TYPE Factor() {
  char c = gc();

  /* Unary +/- is handled here. */
  if(c == '-') {
    return -Factor();
  } else if(c == '+') {
    return Factor();
  } else {
    ugc();
    return Unit();
  }
}

TYPE Term() {
  TYPE total;
  TYPE factor;
  char c;

  total = Factor();
  if(error) return 0;

  while(1) {
    c = gc();
    if(c == '*') {
      total *= Factor();
      if(error) return 0;
    } else if(c == '/') {
      factor = Factor();
      if(error) return 0;
      if(factor == 0) {
        error = DIV_BY_ZERO;
        return 0;
      }
      total /= factor;
    } else {
      ugc();
      return total;
    }
  }
}

TYPE Expr() {
  TYPE total;
  char c;

  total = Term();
  if(error) return 0;

  while(1) {
    c = gc();
    if(c == '-') {
      total -= Term();
      if(error) return 0;
    } else if(c == '+') {
      total += Term();
      if(error) return 0;
    } else {
      ugc();
      return total;
    }
  }
}

TYPE parse(char *str) {
  TYPE res;

  s = str;
  error = SUCCESS;
  pos = 0;

  res = Expr();

  if(!error && gc() != 0) error=PARSE_TOOLONG;

  return res;
}

void chomp(char *s) {
  int len = strlen(s);
  if(s[len-1]=='\n') s[len-1]=0;
}

int main() {
  char line[1000];
  TYPE res;

  while(fgets(line,1000,stdin)) {
    res=parse(line);
    chomp(line);
    printf("Parsed: %s\n",line);
    switch(error) {
    case SUCCESS:
      printf("The value of the expression is: %lld\n",res);
      break;
    case DIV_BY_ZERO:
      printf("A division by zero occured.\n");
      break;
    case PARSE_UNEXPECTED:
      printf("An unexpected character was encountered.\n");
      break;
    case PARSE_TOOLONG:
      printf("There was extra junk at the end of the string.\n");
      break;
    case PARSE_OVERFLOW:
      printf("An integer was parsed that would not fit in int.\n");
      break;
    case PARSE_NOPAREN:
      printf("A closing parenthesis was not found.\n");
      break;
    }
  }

  return 0;
}
