/* 2D Geometry: Minimum bounding circle
   =================================================================
   Description: Given a set of points, this returns the circle with
                the minimum area which completely contains all those
		points
   
   Complexity:  O(n^3) worst case, where n is the number of points
                but on average O(n)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Jan 24, 2003
   References:  http://www.cs.unc.edu/~eberly/gr_cont.htm
   -----------------------------------------------------------------
   Reliability: 2 (Spain 10005 - Packing polygons)
                   Problem C Aliens Jan 21, 2003
   Notes:       This is a simplification of the old min_circle code
                by Scott Crosswhite (/Old/min_circle.c)
		The input array is sorted to increase stability of
		an answer.  This may be removed to increased speed
*/

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

#define EPS 1e-6
#define MAXN 100
#define SQR(x) ((x)*(x))

typedef struct{
  double x, y;
} Point;

typedef struct{
  double x, y, r;
} Circle;

int inside(Point p, Circle c){
  return SQR(p.x-c.x)+SQR(p.y-c.y) <= SQR(c.r);
}

Circle Circle1(Point p){
  Circle c;
  c.x = p.x; c.y = p.y; c.r = 0;
  return c;
}

Circle Circle2(Point p1, Point p2){
  Circle c;
  c.x = 0.5*(p1.x + p2.x);
  c.y = 0.5*(p1.y + p2.y);
  c.r = 0.5*sqrt(SQR(p1.x-p2.x)+SQR(p1.y-p2.y));
  return c;
}

Circle Circle3(Point p1, Point p2, Point p3){
  Circle res; double a,b,c,d,e,f,g;
  a =  p2.x - p1.x;  b = p2.y - p1.y;
  c =  p3.x - p1.x;  d = p3.y - p1.y;
  e = (p2.x + p1.x)*a + (p2.y + p1.y)*b;
  f = (p3.x + p1.x)*c + (p3.y + p1.y)*d;
  g = 2.0*(a*(p3.y - p2.y) - b*(p3.x - p2.x));
  if (fabs(g) < EPS){
    res.x = res.y = res.r = DBL_MAX;
    return res;
  }
  res.x = (d*e - b*f) / g;
  res.y = (a*f - c*e) / g;
  res.r = sqrt(SQR((p1.x-res.x))+SQR((p1.y-res.y)));
  return res;
}

Circle min_circle(Point *p, int n){
  int i, j, k; Point t; Circle c = Circle1(p[0]);
  
  /* Randomize point array to avoid doctored input - may modify the
     limit on the for loop to increase/decrease randomness */
  for(i = 0; i < n; i++){
    j = rand() % n;
    k = rand() % n;
    t = p[j]; p[j] = p[k]; p[k] = t;
  }
  
  for(i = 1; i < n; i++) if(!inside(p[i], c)){ c = Circle1(p[i]);
  for(j = 0; j < i; j++) if(!inside(p[j], c)){ c = Circle2(p[i],p[j]);
  for(k = 0; k < j; k++) if(!inside(p[k], c))  c = Circle3(p[i],p[j],p[k]);}}
  return c;
}

int main(){
  Point pts[MAXN]; Circle res; int i, n;
  
  while(scanf("%d", &n) == 1 && n){
    for(i = 0; i < n; i++)
      scanf("%lf %lf", &pts[i].x, &pts[i].y);
    res = min_circle(pts, n);
    printf("(%.3f, %.3f) r = %.3f\n", res.x, res.y, res.r);
  }
  return 0;
}
