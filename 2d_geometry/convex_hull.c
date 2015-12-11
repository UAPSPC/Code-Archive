/* Computational Geometry: Convex Hull (minimizing version)
   =================================================================
   Description: 
     Given a list of n (n >= 1) points in an array, this routine
     returns the vertices of the convex hull in counterclockwise
     order.  It also returns the number of vertices in the convex
     hull.

     The convex hull is the smallest convex polygon that encompasses
     or borders all of the points.
   
   Complexity:  O(n lg n)  ->  O(qsort) + O(n)
   -----------------------------------------------------------------
   Author:      Jason Klaus
   Date:        Oct 25, 2002
 
   References:  Based on Graham's Scan, pg.949-955,
                   Introduction to Algorithms (2nd Edition),
                   Cormen, Leiserson, Rivest, Stein 
   -----------------------------------------------------------------
   Reliability: 2 Spain successes with older version.
                0 successes with current version.

   Notes:
   - The hull contains a minimum number of points; all co-linear
     points and non-distinct points are eliminated from the hull.
     The reference algorithm does not do this, and also has a
     restriction that the points must be distinct and not duplicate
     polar angles with respects to the reference.  These restrictions
     have been removed from this implementation.
   - The points in the original polygon will be re-ordered.
   - The hull array must be allocated and contain the required amount
     of space (n in size is sufficient).
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define EPSILON 1E-10

typedef struct {
  double x, y;
} Point;

Point *P0;

enum {CCW, CW, CL};

int cross_prod(Point *p1, Point *p2, Point *p0)
{
  double res, x1, x2, y1, y2;

  x1 = p1->x - p0->x;
  x2 = p2->x - p0->x;
  y1 = p1->y - p0->y;
  y2 = p2->y - p0->y;

  res = x1*y2 - x2*y1;

  if (fabs(res) < EPSILON)
    return CL;
  else if (res > 0.0)
    return CW;
  else
    return CCW;
}

int polar_cmp(Point *p1, Point *p2)
{
  int res;
  double d, x1, x2, y1, y2;

  res = cross_prod(p1, p2, P0);

  if (res == CW)
    return -1;
  else if (res == CCW)
    return 1;
  else {
    x1 = p1->x - P0->x;
    x2 = p2->x - P0->x;
    y1 = p1->y - P0->y;
    y2 = p2->y - P0->y;

    d = ((x1*x1) + (y1*y1)) - ((x2*x2) + (y2*y2));

    if (fabs(d) < EPSILON)
      return 0;
    else if (d < 0.0)
      return -1;
    else
      return 1;
  }
}

int convex_hull(Point *poly, int n, Point *hull)
{
  int i, min, h;

  if (n < 1)
    return 0;

  min = 0;
  P0 = &hull[0];
  *P0 = poly[0];

  for (i = 1; i < n; i++) {
    if ((poly[i].y < P0->y) || 
	((poly[i].y == P0->y) && (poly[i].x < P0->x))) {
      min = i;
      *P0 = poly[i];
    }
  }

  poly[min] = poly[0];
  poly[0] = *P0;
  h = 1;

  if (n == 1)
    return h;

  qsort(poly+1, n-1, sizeof(poly[1]),
        (int (*)(const void *, const void *))polar_cmp);

  for (i = 1; i < n; i++) {
    if ((fabs(poly[i].x - hull[0].x) > EPSILON) ||   
        (fabs(poly[i].y - hull[0].y) > EPSILON))  {
      break;
    }
  }

  if (i == n)
    return h;

  hull[h++] = poly[i++];

  for ( ; i < n; i++) {
    while ((h > 1) &&
	   (cross_prod(&poly[i], &hull[h-1], &hull[h-2]) != CCW)) {
      h--;
    }

    hull[h++] = poly[i];
  }

  return h;
}


int main(void)
{
  Point *polygon, *hull;
  int n, hull_size;
  int i;

  while (scanf("%d", &n) == 1 && n > 0) {
    polygon = (Point *)malloc(n * sizeof(Point));
    hull = (Point *)malloc(n * sizeof(Point));
    assert(polygon && hull);

    for (i = 0; i < n; i++) {
      scanf("%lf %lf", &polygon[i].x, &polygon[i].y);
    }

    hull_size = convex_hull(polygon, n, hull);

    printf("Sorted:\n");
    for (i = 0; i < n; i++) {
      printf("(%4.2f, %4.2f) ", polygon[i].x, polygon[i].y);
    }
    printf("\n");

    printf("Hull size = %d\n", hull_size);
    for (i = 0; i < hull_size; i++) {
      printf("(%4.2f, %4.2f) ", hull[i].x, hull[i].y);
    }
    printf("\n");

    free(polygon);
    free(hull);
  }
  return 0;
}
