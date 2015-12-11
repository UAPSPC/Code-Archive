/* 2D-Geometry: Circle-Line Intersection
   =================================================================
   Description: Given either a line or a line segment, and a circle
                these routines calculate the number and coordinates
		of the intersection points.
   
   Complexity:  O(1) 
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 8, 2002
   References:  mathworld.wolfram.com/Circle-LineIntersection.html
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>
#include <math.h>

#define SQR(x) ((x)*(x))
#define EPS 1e-8

typedef struct{
  double x, y;
} Point;

typedef struct{
  Point o;
  double r;
} Circle;

int sgn(double x){
  return x < 0 ? -1 : 1;
}

double dist_2d(Point a, Point b){
  return sqrt(SQR(a.x-b.x)+SQR(a.y-b.y));
}

int circ_iline_isect(Circle c, Point a, Point b,
		     Point *r1, Point *r2){
  double dx = b.x-a.x, dy = b.y-a.y;
  double sdr = SQR(dx)+SQR(dy), dr = sqrt(sdr);
  double D,disc,x,y;
  
  a.x -= c.o.x; a.y -= c.o.y;
  b.x -= c.o.x; b.y -= c.o.y;
  D = a.x*b.y - b.x*a.y;
  disc = SQR(c.r*dr)-SQR(D);
  
  if(disc < 0) return 0;
  x = sgn(dy)*dx*sqrt(disc);
  y = fabs(dy)*sqrt(disc);
  r1->x = (D*dy + x)/sdr + c.o.x;
  r2->x = (D*dy - x)/sdr + c.o.x;
  r1->y = (-D*dx + y)/sdr + c.o.y;
  r2->y = (-D*dx - y)/sdr + c.o.y;
  return disc == 0 ? 1 : 2;
}

int circ_lineseg_isect(Circle c, Point a, Point b,
		       Point *r1, Point *r2){
  double d = dist_2d(a,b);
  int res = circ_iline_isect(c,a,b,r1,r2);
  
  if(res == 2 && dist_2d(a,*r2)+dist_2d(*r2,b) != d) res--;
  if(res >= 1 && dist_2d(a,*r1)+dist_2d(*r1,b) != d){
    *r1 = *r2;
    res--;
  }
  return res;
}

int main(){
  Circle c;
  Point a, b, r1, r2, r3, r4;
  int res1, res2;
  
  while(scanf("%lf %lf %lf %lf %lf %lf %lf",
	      &c.o.x, &c.o.y, &c.r, &a.x, &a.y, &b.x, &b.y) == 7){
    res1 = circ_iline_isect(c, a, b, &r1, &r2);
    res2 = circ_lineseg_isect(c, a, b, &r3, &r4);
    printf("Infinite line has %d intersection point(s)\n", res1);
    if(res1 >= 1) printf("[%.6f,%.6f]\n", r1.x, r1.y);
    if(res1 == 2) printf("[%.6f,%.6f]\n", r2.x, r2.y);
    printf("Line segment has %d intersection point(s)\n", res2);
    if(res2 >= 1) printf("[%.6f,%.6f]\n", r3.x, r3.y);
    if(res2 == 2) printf("[%.6f,%.6f]\n", r4.x, r4.y);
    printf("\n");
  }
  return 0;
}
