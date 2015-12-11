/* Number Theory: Euler Phi function
   =================================================================
   Description: The Euler Phi function returns the number of 
                positive integers less than N that are relatively
		prime to N
   
   Complexity:  O(sqrt(N))
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 21, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       Time estimates:  1 000    0m00.600s
                                10 000    0m00.770s
			       100 000    0m03.180s
 		             1 000 000    0m34.270s
*/

#include <stdio.h>
#include <math.h>

int phi(int n){
  int i, count, res = 1;
  
  for(i = 2; i*i <= n; i++){
    count = 0;
    while(n % i == 0){
      n /= i;
      count++;
    }
    if(count > 0) res *= (pow(i, count)-pow(i, count-1));
  }
  if(n > 1) res *= (n-1);
  return res;
}

int main(){
  int n;

  for(n = 0; n < 10; n++)
    printf("Euler phi (%d) = %d\n", n, phi(n));
  return 0;
}
