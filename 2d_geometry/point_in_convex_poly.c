/* 2D Geometry: Point in convex polygon
   =================================================================
   Description: Given a point an a convex polygon, returns 1 if the
                point is in the polygon
   
		Can also check to see if point is on boundary

   Complexity:  O(N) where N is number of vertices of polygon
   -----------------------------------------------------------------
   Author:      Ashley Zinyk, Gilbert Lee
   Date:        Nov 14, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1E-8  
#define BOUNDARY 1  /* What to return if the point is on the 
                       boundary of the polygon (0 = false, 1 = true) */

typedef struct{
  double x, y;
} Point;

double area_tri(Point a, Point b, Point c){
  double area;
  
  area = (b.x-a.x) * (c.y-a.y)
        -(b.y-a.y) * (c.x-a.x); 
  return (fabs(area))/2;
}

int point_in_convex_poly(Point *poly, int n, Point p){
  double areapoly = 0, areatri = 0, temp;
  int bflag = 0;
  int i, j;
  
  for(i = 0, j = n-1; i < n; j = i++){
    areapoly += area_tri(poly[i], poly[j], poly[0]);
    temp = area_tri(poly[i], poly[j], p);
    if(temp < EPS) bflag = 1;
    areatri += temp;
  }
  if(fabs(areapoly-areatri) < EPS){
    if(bflag) return BOUNDARY;
    else return 1;
  }
  return 0;
}

int main(){
  int i, n;
  Point *poly, p;
  
  printf("How many vertices in the polygon? ");
  scanf("%d", &n);
  poly = (Point *) malloc(n*sizeof(Point));
  for(i = 0; i < n; i++){
    scanf("%lf %lf", &poly[i].x, &poly[i].y);
  }
  printf("Now enter points to test:\n");
  while(scanf("%lf %lf", &p.x, &p.y) == 2){
    if(point_in_convex_poly(poly, n, p)){
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
  return 0;
}
