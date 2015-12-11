/* Generators: K-Subset functions
   =================================================================
   Description: Some functions dealing with subsets of {0,1,...,N-1}
                of size K.

		Subsets are represented by integer arrays, of size
		K, with values in the range [0,N-1]

		============ Lexicographically ordered =============
		rank_lexkset(A,n,k) returns the rank (i.e the index
		in the lexicographically sorted list of all 
		K-subsets) of subset A.

		unrank_lexkset(r,n,k,A) builds the rth 
		lexicographic K-subset into the array A

		next_kset(A,B,n,k) builds the K-subset that comes 
		lexicographically after A into the array B.  The
		function returns 1 if this is done sucessfully, and
		0 otherwise
		
		=========== Co-lexicographically ordered ===========
		rank_colexkset(A,n,k) returns the rank of A in the 
		co-lexicographically sorted list

		unrank_colexkset(r,n,k,A) builds the rth 
		co-lexicographic K-subset into the array A

		============= Minimum change ordered ===============	
		rank_minkset(A,n,k) returns the rank of A in a
		minimal change ordering known as revolving door
		
		unrank_minkset(r,n,k,A) builds the rth K-subset
		of the minimum change ordering
		
		minchange(r,n,k,plus,minus) sets plus to the
		index that is added, and minus to the index that
		is removed from the rth K-subset to get to the 
		(r+1)th K-subset.  The function returns 1
		if this is done sucessfully, and 0 otherwise
		
   Complexity:  rank_lexkset     => O(n)
                unrank_lexkset   => O(n)
		next_lexkset     => O(k)

		rank_colexkset   => O(k)
		unrank_colexkset => O(n)
		
		unrank_minkset   => O(n)
		minchange        => O(n+k^2)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Jan 17, 2003
   References:  Combinatorial Algorithms - Donald L. Kreher
                Chapter 2.3
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       bin[n][k] stores n choose k. This may be redone 
                using arbitrary precision arithmetic, if necessary
*/


#include <stdio.h>

#define MAXN 200
#define MAXK 12
#define ULL unsigned long long
#define min(a,b) (((a)<(b))?(a):(b))

ULL bin[MAXN+1][MAXK+1];

/* ============ Lexicographically ordered ============= */
ULL rank_lexkset(int *A, int n, int k){
  ULL r; int i, j;
  for(i = r = 0; i < k; i++)
    for(j = i?A[i-1]+1:0; j < A[i]; j++)
      r += bin[n-1-j][k-1-i];
  return r;
}

void unrank_lexkset(ULL r, int n, int k, int *A){
  int i, x;
  for(i = x = 0; i < k; i++){
    while(r >= bin[n-1-x][k-1-i])
      r -= bin[n-1-x++][k-1-i];
    A[i] = x++;
  }
}

int next_lexkset(int *A, int *B, int n, int k){
  int i, j;
  for(i = k-1; i >= 0; i--)
    if(A[i] != n-k+i){
      for(j = 0; j < i; j++) B[j] = A[j];
      for(j = i; j < k; j++) B[j] = A[i]+1+j-i;
      return 1;
    }
  return 0;
}

/* ============ Co-lexicographically ordered ============= */
ULL rank_colexkset(int *A, int n, int k){
  ULL r; int i;
  for(i = r = 0; i < k; i++)
    r += bin[A[i]][k-i];
  return r;
}

void unrank_colexkset(ULL r, int n, int k, int *A){
  int i, x = n;
  for(i = 0; i < k; i++){
    while(bin[x][k-i] > r) x--;
    A[i] = x;
    r -= bin[x][k-i];
  }
}

/* ============ Minimal Change ordering ============= */
ULL rank_minkset(int *A, int n, int k){
  ULL r; int s = 1, i;
  
  if(k % 2) r = -1; else r = 0;
  for(i = k; i > 0; i--){
    r += s*bin[A[i-1]+1][i];
    s *= -1;
  }
  return r;
}

void unrank_minkset(ULL r, int n, int k, int *A){
  int x = n, i;
  for(i = k; i > 0; i--){
    while(bin[x][i] > r) x--;
    A[i-1] = x;
    r = bin[x+1][i]-r-1;
  }
}


int minchange(int r, int n, int k, int *plus, int *minus){
  int A[MAXK], B[MAXK], i, j;
  
  if(r == bin[n][k]-1) return 0;
  unrank_minkset(r, n, k, A);
  unrank_minkset(r+1, n, k, B);
  for(i = 0; i < k; i++){
    for(j = 0; j < k; j++)
      if(A[i] == B[j]){
	B[j] = -1;
	break;
      }
    if(j == k) *minus = A[i];
  }
  for(i = 0; i < k; i++){
    if(B[i] != -1){
      *plus = B[i];
      break;
    }
  }
  return 1;
}

void buildBin(){
  int n,k;
  for(n = 0; n <= MAXN; n++){
    bin[n][0] = 1;
    for(k = 1; k <= min(n,MAXK); k++)
      bin[n][k] = bin[n-1][k]+bin[n-1][k-1];
  }
}

int main(){
  int A[MAXK], B[MAXK], n, k, i, j, plus, minus;

  buildBin(); /* Build table of binomial coefficients */
  
  while(scanf("%d %d", &n, &k) == 2){

    for(i = 0; i < bin[n][k]; i++){
      printf("Rank[%d]  Lex:", i);
      unrank_lexkset(i, n, k, A);
      for(j = 0; j < k; j++) printf("%d ", A[j]);
      printf("{%llu}   Co-lex:", rank_lexkset(A,n,k));
      
      unrank_colexkset(i, n, k, B);
      for(j = 0; j < k; j++) printf(" %d", B[j]);
      printf(" {%llu}  Minchange:", rank_colexkset(B, n, k));
      
      unrank_minkset(i, n, k, A);
      for(j = 0; j < k; j++) printf(" %d", A[j]);      
      if(minchange(i, n, k, &plus, &minus)){
	printf(" [+%d][-%d] {%llu}\n",
	       plus, minus, rank_minkset(A, n, k));
      } else {
	printf(" No change {%llu}\n", rank_minkset(A, n, k));
      }
    }
  }
  return 0;
}
