/* 3D Geometry: Sphere from 4 Points
   =================================================================
   Description: Given 4 points in 3D space, determines the 
                parameters of a sphere on which all 4 points lie.
		This only works for non-coplanar points.
   
   Complexity:  O(1)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Nov 1, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>
#include <math.h>

#define EPS 1e-8

typedef struct{
  double x, y, z;
} Point;

double sqr(double x){ return x*x;}

/* Solves the determinant of a n by n matrix recursively */
double solveDet(double m[4][4], int n){
  double s[4][4], res = 0, x;
  int i, j, skip, ssize;

  if(n == 2) return m[0][0]*m[1][1]-m[0][1]*m[1][0];
  for(skip = 0; skip < n; skip++){
    for(i = 1; i < n; i++)
      for(j = 0, ssize = 0; j < n; j++){
	if(j == skip) continue;
	s[i-1][ssize++] = m[i][j];
      }
    x = solveDet(s, n-1);
    if(skip % 2) res -= m[0][skip]*x;
    else res += m[0][skip]*x;
  }
  return res;
}


/* Given 4 points:
   Returns 0 if the points are coplanar 
   Returns 1 if the points are not coplanar with:
             o = center of sphere
	          r = radius of sphere
*/
int sphere_from_4pts(Point p[4], Point *o, double *r){
  double m[4][5], s[4][4], sol[5];
  int ssize, skip, i, j;

  for(i = 0; i < 4; i++){
    s[i][0] = p[i].x;
    s[i][1] = p[i].y;
    s[i][2] = p[i].z;
    s[i][3] = 1;
  }
  if(fabs(solveDet(s, 4)) < EPS) return 0;
  
  for(i = 0; i < 4; i++){
    m[i][0] =   sqr(m[i][1]=p[i].x)
      + sqr(m[i][2]=p[i].y)
      + sqr(m[i][3]=p[i].z);
    m[i][4] = 1;
  }

  for(skip = 0; skip < 5; skip++){
    for(i = 0; i < 4; i++)
      for(j = 0, ssize=0; j < 5; j++){
	if(j == skip) continue;
	s[i][ssize++] = m[i][j];
      }
    sol[skip] = solveDet(s, 4);
  }

  for(i = 1; i < 5; i++)
    sol[i] /= (sol[0] * ((i%2) ? 1 : -1));

  for(i = 1; i < 4; i++)
    sol[4] += sqr(sol[i]/=2);

  o->x = sol[1];
  o->y = sol[2];
  o->z = sol[3];
  *r = sqrt(sol[4]);
  return 1;
}
 
int main(){
  int tnum, i;
  Point p[4], o;
  double r;

  scanf("%d", &tnum);
  
  while(tnum--){
    for(i = 0; i < 4; i++)
      scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].z);
    
    if(sphere_from_4pts(p, &o, &r))
      printf("Centered at [%f, %f, %f] with radius %f\n",
	     o.x, o.y, o.z, r);
    else 
      printf("The points are coplanar\n");
  }
  return 0;
}
