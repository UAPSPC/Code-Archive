/* 2-D Geometry: Area of intersection between two general polygons
   =================================================================
   Description: Takes in two general simple polygons
                (not necessarily convex) and computes the area of
		their intersection.
   
   Complexity:  O(n^2) worst case
   -----------------------------------------------------------------
   Author:      Jason Klaus
   Date:        November 3, 2003
   References:  www.cg.tuwien.ac.at/~theussl/papers/polygons.ps.gz
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       Simplified the documented triangulation algorithm
                somewhat so it is not as long but a constant time
                slower.
*/

#include <cstdio>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

#define EPS 1e-8

// 1 for clockwise ordering of points, -1 for counter-clockwise
#define ORDER 1

struct Point {
  double x, y;

  bool operator < (const Point &p) const {
    return (y + EPS < p.y) || ((y - EPS < p.y) && (x + EPS < p.x));
  } 
  bool operator == (const Point &p) const {
    return !(*this < p) && !(p < *this);
  } 
};

struct Triangle {
  Point p[3];
};

//2D cross product of vectors a->b, c->d
inline double cross(const Point &a, const Point &b,
                    const Point &c, const Point &d){
  return ((b.x - a.x)*(d.y - c.y) - (d.x - c.x)*(b.y - a.y));
}

// This function classifies p as either being "left of" [-1],
// "right of" [+1] or "on" [0] the line a -> b.

int leftRight(const Point &a, const Point &b, const Point &p){
  double res = cross(a, b, a, p);

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

// Takes in a list of n ordered points forming the polygon P, and
// a vector of n-2 triangles in T.  P is modified during the
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

//Finds the pt of intersection between line segments a->b and c->d
//Returns 1 if there is one point of intersection, stored in p.
//Returns 0 if there is no point of intersection, or infinitely many
int isectLineSegs(Point &a, Point &b, Point &c, Point &d, Point &p)
{
  double r, s, dn, n1, n2;

  n1 =  cross(c, d, c, a);
  n2 = -cross(a, b, a, c);
  dn =  cross(a, b, c, d);

  if ((dn > EPS) || (dn < -EPS)) {
    r = n1/dn;
    s = n2/dn;
    if ((-EPS < r) && (r < 1+EPS) &&
	(-EPS < s) && (s < 1+EPS)) {
      p.x = a.x + r*(b.x - a.x);
      p.y = a.y + r*(b.y - a.y);
      return 1;
    }
  }
  return 0;
}

double areaPoly(vector<Point> &P){
  double area = 0.0;
  vector<Point>::iterator p, q;

  for (p = P.end()-1, q = P.begin(); q != P.end(); p = q++) {
    area += p->x*q->y - p->y*q->x;
  }
  return area/2.0;
}

Point P0;

bool radialLessThan(const Point &a, const Point &b){
  return (ORDER == leftRight(P0, a, b));
}

double isectAreaTriangles(Triangle &a, Triangle &b){
  vector<Point> P;
  vector<Point>::iterator s, e, ne;
  Point p;
  Triangle T[2] = { a, b };
  int i, j, r, t, u, v;
  double area = 0;

  P.clear();
  
  for(r=1, t=0; t < 2; r = t++) for(i = 2, j = 0; j < 3; i = j++){
    if(isInsideTriangle(T[r].p[0],T[r].p[1],T[r].p[2],T[t].p[i]))
      P.push_back(T[t].p[i]);
    for (u = 2, v = 0; v < 3; u = v++)
      if(isectLineSegs(T[t].p[i],T[t].p[j],T[r].p[u],T[r].p[v],p))
	P.push_back(p);
  }

  if (!P.empty()) {
    s = P.begin();
    e = P.end();
    sort(s, e);
    ne = unique(s, e);
    P.erase(ne, e);
    
    if (P.size() >= 3) {
      P0 = P[0];
      sort(s+1, ne, radialLessThan);
      area = areaPoly(P);
    }
  }
  return area;
}

double isectAreaGpoly(list<Point> &P, list<Point> &Q){
  double area = 0.0;
  vector<Triangle> S, T;
  vector<Triangle>::iterator s, t;

  triangulate(P, S);
  triangulate(Q, T);

  for (s = S.begin(); s != S.end(); s++)
    for (t = T.begin(); t != T.end(); t++)
      area += isectAreaTriangles(*s, *t);

  return -ORDER*area;
}


int main(){
  int n, i, j; Point p; list<Point> P[2];

  for (j = 0; j < 2; j++) {
    scanf("%d", &n);
    P[j].clear();
    
    for (i = 0; i < n; i++) {
      scanf("%lf %lf", &p.x, &p.y);
      P[j].push_back(p);
    }

    printf("Polygon %d:\n", j+1);
    for (list<Point>::iterator q=P[j].begin();q != P[j].end(); q++)
      printf(" (%.2f, %.2f)\n", q->x, q->y);
    printf("\n");
  }
  printf("Area of Intersection: %.6f\n", isectAreaGpoly(P[0],P[1]));
  return 0;
}
