/* 2D-Geometry: Lattice-polygons - Pick's Theorem
   =================================================================
   Description: Given a lattice N-gon (a polygon where ends points
                are on integer coordinates), this routine counts
		the number of lattice points on the boundary, as
		well as the number of interior lattice points.
   
   Complexity:  O(roughly N) (N calls to gcd())
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 12, 2002
   References:  http://mathworld.wolfram.com/PicksTheorem.html
   -----------------------------------------------------------------
   Reliability: 1 successful use (Spain 10088) Sept 2002
   Notes:       Pick's Formula is: A = I + B/2 - 1
                where A = area of the closed lattice polygon
		      I = # of interior lattice points
		      B = # of lattice points on boundary
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1005
typedef struct{
  long long x, y;
} Point;

int gcd(long long a, long long b){
  int r;
  
  a = abs(a);
  b = abs(b);
  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

double area_poly(Point *p, int n){
  double sum = 0;
  int i, j;
  
  for(i = n-1, j = 0; j < n; i = j++)
    sum += p[i].x * p[j].y - p[i].y * p[j].x;
  return sum/2.0;
    }

void lat_poly_pick(Point *p, int n, long long *I, long long *B){
  int i, j, dx, dy;
  double A = fabs(area_poly(p, n));
  
  *B = 0;
  for(i = n-1, j = 0; j < n; i = j++){
    dx = abs(p[i].x - p[j].x);
    dy = abs(p[i].y - p[j].y);
    *B += gcd(dx,dy);
  }
  *I = A+1-*B/2.0;
}

int main(){
  int i, n;
  long long numI, numB;
  Point p[MAXN];
  
  while(scanf("%d", &n) == 1 && n){
    for(i = 0; i < n; i++){
      scanf("%lld %lld", &p[i].x, &p[i].y);
    }
    lat_poly_pick(p, n, &numI, &numB);
    printf("The lattice polygon has %lld interior points and %lld boundary points\n", numI, numB);
  }
  return 0;
}


