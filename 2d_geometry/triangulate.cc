/* 2-D Geometry: Triangulation of a simple 2D polygon
   =================================================================
   Description: Splits a simple polygon (not necessarily convex)
                of n verticies into n-2 disjoint triangles whose
                verticies are taken from the original polygon.
   
   Complexity:  O(n^2) worst case
   -----------------------------------------------------------------
   Author:      Jason Klaus
   Date:        June 5, 2003
   References:  www.cg.tuwien.ac.at/~theussl/papers/polygons.ps.gz
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       Simplified the documented algorithm somewhat so it
                is not as long but a constant time slower.
*/

#include <cstdio>
#include <list>
#include <vector>

using namespace std;

#define EPS 1e-8

// 1 for clockwise ordering of points, -1 for counter-clockwise
#define ORDER 1

struct Point {
  double x, y;
};

struct Triangle {
  Point p[3];
};

// This function classifies p as either being left of (-1),
// right of (1) or on (0) the line a -> b.

int leftRight(Point &a, Point &b, Point &p){
  double res = ((b.x - a.x)*(p.y - a.y) -
		(p.x - a.x)*(b.y - a.y));
  if (res > EPS)
    return -1;
  else if (res < -EPS)
    return 1;
  return 0;
}

// This function returns non-zero if point b in the sequence a->b->c
// is a concave point or zero if it is convex.
// (If inside angle >= 180 deg, concave, otherwise convex)

int isConcave(Point &a, Point &b, Point &c){
  return (ORDER*leftRight(a, b, c) <= 0);
}

// This function returns non-zero if point p is located on or 
// inside the triangle <a b c>.

int isInsideTriangle(Point &a, Point &b, Point &c, Point &p){
  int r1 = leftRight(a, b, p);
  int r2 = leftRight(b, c, p);
  int r3 = leftRight(c, a, p);
  return ((ORDER*r1 >= 0) && (ORDER*r2 >= 0) && (ORDER*r3 >= 0));
}

// Takes in a list of n ordered points forming the polygon P, and a
// vector of n-2 triangles in T.  P is modified during the
// triangulation. (n >= 3) 

void triangulate(list<Point> &P, vector<Triangle> &T){
  list<Point>::iterator a, b, c, q;
  Triangle t;

  T.clear();
  if (P.size() < 3) return;

  for (a=b=P.begin(), c=++b, ++c; c != P.end(); a=b, c=++b, ++c) {
    if (!isConcave(*a, *b, *c)) {
      for (q = P.begin(); q != P.end(); q++) {
	if (q == a) {
	  ++q;
	  ++q;
	  continue;
	}
	if (isInsideTriangle(*a, *b, *c, *q)) break;
      }
      if (q == P.end()) {
	t.p[0] = *a;
	t.p[1] = *b;
	t.p[2] = *c;
	T.push_back(t);
	
	P.erase(b);
	b = a;
	if (b != P.begin()) b--;
      }
    }
  }
}

int main(){
  int n, i, j;
  Point p;
  list<Point> P;
  vector<Triangle> T;

  scanf("%d", &n);
  P.clear();
  
  for (i = 0; i < n; i++) {
    scanf("%lf %lf", &p.x, &p.y);
    P.push_back(p);
  }
  
  printf("Polygon:\n");
  for (list<Point>::iterator q = P.begin(); q != P.end(); q++){
    printf(" (%.2f, %.2f)\n", q->x, q->y);
  }
  printf("\n");
  
  triangulate(P, T);
  
  printf("Triangles:\n");
  for (i = 0; i < n-2; i++) {
    for (j = 0; j < 3; j++)
      printf(" (%.2f, %.2f)", T[i].p[j].x, T[i].p[j].y);
    printf("\n");
  }
  return 0;
}
