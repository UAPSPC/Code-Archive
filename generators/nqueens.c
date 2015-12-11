/* Generators: N-Queens Solution Generator
   =================================================================
   Description: This code generates a solution for the n-queens 
                problem.  Solutions exist for n = 1 || n > 3.
		Solutions are stored in the array called row[],
		where row[i] represents the row where the queen in
		the i'th column is placed.  Coordinates are [0..n-1]
   
   Complexity:  O(n)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 9, 2002
   References:  www.bridges.canterbury.ac.nz/features/eight.html
   -----------------------------------------------------------------
   Reliability: 1 (Sept 2002)
   Notes:       - This solution is only 1 of perhaps many
                  solutions
		- No checking is done by the routine for valid n
		* Solves Spanish Problem 10094
*/

#include <stdio.h>
#include <string.h>

#define MAXN 10001

int row[MAXN];

void gen_nqueens(int n){
  int i;
  
  if(n % 2){
    gen_nqueens(n-1);
    row[n-1] = n-1;
  } else {
    if(n % 6 == 2){
      for(i = 0; i < n/2; i++) row[i] = (n/2+2*i-1)%n;
      for(i = n/2; i < n; i++) row[i] = (n/2+2*i+2)%n;
    } else {
      for(i = 0; i < n/2; i++) row[i] = 2*i+1;
      for(i = n/2; i < n; i++) row[i] = (2*i)%n;
    }
  }
}

int main(){
  int i, n;
  
  while(scanf("%d", &n) == 1){
    if(n == 1 || n > 3){
      gen_nqueens(n);
      for(i = 0; i < n; i++)
	printf("%d%c", row[i], i == n-1 ? '\n' : ' ');
    } else {
      printf("Impossible\n");
    }
  }
  return 0;
}
