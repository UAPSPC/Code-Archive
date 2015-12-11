/* Generators: Binary Strings generator - (ordered by cardinality)
   =================================================================
   Description: Generates all possible binary strings of size N
                ordered in increasing order by the number of bits
		set, then lexographically.
		For example: when N = 3, the routine generates:
		     0 0 0  ] Cardinality 0
		     0 0 1  ]
		     0 1 0  | Cardinality 1
		     1 0 0  ]
		     0 1 1  ]
		     1 0 1  | Cardinality 2
		     1 1 0  ]
		     1 1 1  ] Cardinality 3
   
   Complexity:  O(2^N)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 9, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       This routine may be useful if we want to find the
                solution with the lowest cardinality.  
		For example, you may want to break off a search
		after a certain number of solutions have been found.
*/

#include <stdio.h>

#define MAXN 20

char bit[MAXN];

/* Add whatever work needs to be done in this routine */
/* For this sample, we just print out the bits */
void Process(int n){
  int i;

  for(i = 0; i < n; i++) printf("%2d", bit[i]);
  printf("\n");
}

void recurse(int n, int curr, int left){
  if(curr == n){
    Process(n);
  } else {
    if(curr+left < n){
      bit[curr] = 0;
      recurse(n, curr+1, left);
    } 
    if(left){
      bit[curr] = 1;
      recurse(n, curr+1, left-1);
    }
  }
}

/* This function generates the strings based on cardinality
   You may wish to add break conditions in this routine if
   necessary */
void gen_bin_card(int n){
  int i;
  
  for(i = 0; i <= n; i++){
    printf("Cardinality %d:\n", i);
    recurse(n, 0, i);
  }
}

int main(){
  int n;
  
  while(scanf("%d", &n) == 1){
    printf("Binary string length N = %d\n", n);
    gen_bin_card(n);
  }
  return 0;
}
