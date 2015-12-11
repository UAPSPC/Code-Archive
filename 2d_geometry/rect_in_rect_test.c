/* 2D-Geometry: Rectangle in Rectangle Test
   =================================================================
   Description: Given two rectangles defined by their lengths and 
                widths, returns whether or not the first rectangle
		fits completely within the second.
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 13, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 3 successful use (Feb 2003)
                (ACM 1999 Central European: Box)
		(ACM 2002 European: Problem B: Bricks)
		(Prob B: Equipment Box Nov 8, 2003)
   Notes:       
*/

#include <stdio.h>
#include <math.h>

#define SQR(x) ((x)*(x))

typedef struct{
  int n;             /* Number of solutions */
  long double x[2];  /* Solutions */
} Result;

Result solve_quad(long double a, long double b, long double c){
  Result r;
  long double z = SQR(b)-4*a*c;
  
  if(z < 0){
    r.n = 0;
  } else if(z == 0){
    r.n = 1;
    r.x[0] = -b/(2*a);
  } else {
    r.n = 2;
    r.x[0] = (-b+sqrt(z))/(2*a);
    r.x[1] = (-b-sqrt(z))/(2*a);
  }
  return r;
}

int fit_diag(double x1, double y1, double x2, double y2){
  long double A = SQR(x1)+SQR(y1);
  long double B = -2*SQR(x1)*x2;
  long double C = SQR(x1)*(SQR(x2)-SQR(y1));
  long double a;
  Result r = solve_quad(A,B,C);
  long double w1, w2;
  int i;

  for(i = 0; i < r.n; i++){
    if(0 <= r.x[i] && r.x[i] <= x2){
      a = r.x[i];
      w1 = sqrt(SQR(x1)-SQR(a));
      w2 = sqrt(SQR(y1)-SQR(x2-a));
      if(y2 >= sqrt(SQR(x1)-SQR(a))+sqrt(SQR(y1)-SQR(x2-a))) return 1;
    }
  }
  return 0;
}

int rect_in_rect_test(double x1, double y1, double x2, double y2){
  
  if(x1 <= x2 && y1 <= y2) return 1;
  if(x1 <= y2 && y1 <= x2) return 1;
  if(x1 > x2 && y1 > y2) return 0;
  if(x1 > y2 && y1 > x2) return 0;

  if(fit_diag(x1,y1,x2,y2) ||
     fit_diag(x1,y1,y2,x2) ||
     fit_diag(y1,x1,x2,y2) ||
     fit_diag(y1,x1,y2,x2)) return 1;
  return 0;
}

int main(){
  double len1, wid1, len2, wid2;

  while(scanf("%lf %lf %lf %lf", &len1, &wid1, &len2, &wid2) == 4){
    if(rect_in_rect_test(len1, wid1, len2, wid2)){
      printf("The first rectangle can fit inside the second\n");
    } else {
      printf("Impossible to fit\n");
    }
  }
  return 0;
}
