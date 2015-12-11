/* Dynamic Programming: Maximum Submatrix Sum
   =================================================================
   Description: Given a matrix with n rows and m columns, find
                the rectangular submatrix with the largest sum.
   
   Complexity:  O(n*m^2)
   -----------------------------------------------------------------
   Author:      Ashley Zinyk
   Date:        December 09, 2002
   References:  
   -----------------------------------------------------------------
   Reliability: 3 (Spain 108, 836, 10074)
   Notes: This code can easily be converted to work with a
          matrix of doubles.  Matricies have the coordinate (0,0) in
          the upper left corner and (n-1,m-1) in the lower right.
          Submatricies are inclusive, i.e. the submatrix
          (t=5, b=6, l=3, r=4) contains the elements:
          (5,3), (5,4), (6,3), (6,4).
          The result is not guaranteed to be unique.
*/

/* fix compile warning */

#include <stdio.h>
#define MAXN 100
#define Atype double

typedef struct {
  int top, bot, left, right;
  Atype sum;
} submat_t;

submat_t max_submatrix(Atype vals[MAXN][MAXN], int n, int m) {
  submat_t best, prev[MAXN][MAXN];
  int row, i, j;
  Atype sum;

  for (i = 0; i < n; i++)
    for (j = 0; j <= i; j++) prev[i][j].sum = -1;
  best.sum = vals[0][0];
  best.left = best.right = best.top = best.bot = 0;

  for (row = 0; row < n; row++) {
    for (i = 0; i < m; i++) {
      for (sum = 0, j = i; j < m; j++) {
        sum += vals[row][j];
        if (prev[i][j].sum <= 0) {
          prev[i][j].sum = 0;
          prev[i][j].top = row;
        }
        prev[i][j].sum += sum;
        if (prev[i][j].sum > best.sum) { /* put tie-breaking here */
          best = prev[i][j];
          best.right = j;
          best.left = i;
          best.bot = row;
        }
      }
    }
  }
  return best;
}

/* If you have matricies that are long and skinny (like 7x40 or 100x20)
   call this function instead of max_submatrix.  If the problem can be
   solved faster by transposing the matrix, this function will
   automatically determine that and solve the problem.  It's usage
   is identical to max_submatrix. */

submat_t max_submat_t(Atype mat[MAXN][MAXN], int n, int m) {
  Atype transp[MAXN][MAXN];
  int i, j, tmp;
  submat_t res;

  if (m <= n) return max_submatrix(mat, n, m);
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) transp[j][i] = mat[i][j];
  res = max_submatrix(transp, m, n);
  tmp = res.top;
  res.top = res.left;
  res.left = tmp;
  tmp = res.bot;
  res.bot = res.right;
  res.right = tmp;
  return res;
}

int main() {
  Atype mat[100][100];
  int nrows, ncols, i, j;
  submat_t max;

  while (scanf("%d %d", &nrows, &ncols)==2) {
    for (i = 0; i < nrows; i++)
      for (j = 0; j < ncols; j++)
        scanf("%lf",&mat[i][j]);
    max = max_submatrix(mat,nrows,ncols);
    printf("(%d,%d) (%d,%d) has a sum of %g.\n",
           max.top, max.left, max.bot, max.right, max.sum);
  }
  return 0;
}
