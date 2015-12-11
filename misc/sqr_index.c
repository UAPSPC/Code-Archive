/* Miscellaneous: Square index rotation/flipping
   =================================================================
   Description: For a square of size n with indices 0..n-1,
                Given x and y and a orientation
                returns the corresponding x,y coordinate.

   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Jan 27, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 1 Problem G: Noise Effect
                             (ACM South America - 2002) Jan 26, 2003
   Notes:       Here are diagrams of the various orientations:

                                  x       y
		 ^         ^    <--+     +-->
		y|         |x      |y   x|
		 +-->   <--+       v     v
                  x       y    
 	         d=0     d=1     d=2     d=3

                          y       x
                   ^    <--+     +-->    ^
                   |y      |x   y|      x|
		<--+       v     v       +-->
		  x                       y
		 d=4     d=5     d=6     d=7
*/

#include <stdio.h>

int n, g[10][10];

int dx(int x, int y, int d){
  switch(d){
  case 0: case 6: return x;
  case 1: case 5: return n-1-y;
  case 2: case 4: return n-1-x;
  case 3: case 7: return y;
  }
  return -1;
}

int dy(int x, int y, int d){
  switch(d){
  case 0: case 4: return y;
  case 1: case 7: return x;
  case 2: case 6: return n-1-y;
  case 3: case 5: return n-1-x;
  }
  return -1;
}

int main(){
  int i, j, d;
  
  scanf("%d", &n);
  
  for(i = 0; i < n; i++)
    for(j = 0; j < n; j++)
      g[i][j] = i*n+j;
  
  for(d = 0; d < 8; d++){
    printf("Orientation [%d]\n", d);
    for(i = 0; i < n; i++){
      for(j = 0; j < n; j++)
	printf("%d", g[dx(i,j,d)][dy(i,j,d)]);
      printf("\n");
    }
    printf("\n");
  }
  return 0;
}
