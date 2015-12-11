/* Search: Golden section Search
   =================================================================
   Description: Given an function f(x) with a single local minimum,
                a lower and upper bound on x, and a tolerance for
		convergence, this function finds the value of x 
		
		The function is written globally as f(x)
   
   Complexity:  Depends on tolerance
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Mar 14, 2003
   References:  www.chemeng.ed.ac.uk/~jwp/MSO/section5/maths/
                                     part3/handout2/
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       - watch out for -0.000
*/

#include <stdio.h>

#define GOLD 0.381966
#define move(a,b,c)    x[a]=x[b];x[b]=x[c];fx[a]=fx[b];fx[b]=fx[c]

double f(double x){
  return x*x;
}

double golden(double xlow, double xhigh, double tol){
  double x[4], fx[4], L;
  int iter = 0, left = 0, mini, i;

  fx[0] = f(x[0]=xlow); 
  fx[3] = f(x[3]=xhigh);
  
  while(1){
    L = x[3]-x[0];
    if(!iter || left){
      x[1] = x[0]+GOLD*L;
      fx[1] = f(x[1]);
    }
    if(!iter || !left){
      x[2] = x[3]-GOLD*L;
      fx[2] = f(x[2]);
    }
    for(mini = 0, i = 1; i < 4; i++)
      if(fx[i] < fx[mini]) mini = i;
    if(L < tol) break;
    
    if(mini < 2){
      left = 1;
      move(3,2,1);
    } else {
      left = 0;
      move(0,1,2);
    }
    iter++;
  }
  return x[mini];
}

int main(){
  double low, high , tol, minx;
  
  while(scanf("%lf %lf %lf", &low, &high, &tol) == 3){
    minx = golden(low, high, tol);
    printf("f(%.6f) = %.6f\n", minx, f(minx));
  }
  return 0;
}




