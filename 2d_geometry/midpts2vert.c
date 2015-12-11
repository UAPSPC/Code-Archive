/*  2D Geometry:  Polygon Midpoints to Verticies
   =================================================================
   Description: Consider a polygon with n sides.  Given the
                midpoints of each side, this code will find the
		vertices of the polygon.

   Complexity:  O(n)
   -----------------------------------------------------------------
   Author:      Ashley Zinyk
   Date:        Nov 19, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       This only works when n is odd; the answer is not
                unique  for polygons with an even number of vertices.
		The polygon does not need to be convex. The points
		can be in clockwise or counterclockwise order. 
*/

#include <stdio.h>

typedef struct {
  double x, y;
} Point;

void midpts2vert(Point *midpts, int n, Point *poly) {
  int i;
  
  poly[0] = midpts[0];
  for (i = 1; i < n; i += 2) {
    poly[0].x += midpts[i+1].x - midpts[i].x;
    poly[0].y += midpts[i+1].y - midpts[i].y;
  }
  for (i = 1; i < n; i++) {
    poly[i].x = 2.0*midpts[i-1].x - poly[i-1].x;
    poly[i].y = 2.0*midpts[i-1].y - poly[i-1].y;
  }  
}

int main() {
  Point midpts[1000], poly[1000];
  int i, n;

  while (scanf("%d",&n)==1) {
    for (i = 0; i < n; i++)
      scanf("%lf %lf", &midpts[i].x, &midpts[i].y);
    midpts2vert(midpts, n, poly);
    for (i = 0; i < n; i++)
      printf("%0.3f %0.3f\n", poly[i].x, poly[i].y);
  }
  return 0;
}
