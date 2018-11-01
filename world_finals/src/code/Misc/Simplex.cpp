/*The LP should be in standard maximization form.
  maximize:   <c,x>
  subject to: A*x <= b, x >= 0
  Use global variables A, b, and c.
  If n = # vars, m = # constraints (apart from nonnegativity) then
   A : m by n constraint matrix
   b : m-dimensional array of constants in the constraints
   c : n-dimensional array of coefficients in the objective function
  Once A, b, and c are constructed, simply call simplex(n, m).
  Returns: -1 == unbounded, 0 == infeasible, 1 == optimum solution found
  If an optimum is found: x = one such optimum, val = its value
  (x and val are global variables)
  Running time: O(n * m * I) where I = # iterations. In the worst case
  this can be exponential, but it is usually *much* better. Can probably
  be used safely in a programming contest where n*m ~ 10,000.
  This is just a heuristic statement.
  Uses Bland's pivot selection rule to avoid cycles.
  CAUTION:
   - Many loops go from 0 up to *and including* n or m. But some do not.
     Pay careful attention toward the inequalities used.
   - Make sure you adjust MAXN and MAXC appropriately. */
#define MAXN 1000 // max # of variables
#define MAXC 1000 // max # of constraints
#define EPS  1e-8
// This is the A, b, and c matrix you should populate before calling
// simplex().  If an optimum solution was found, it is stored in x[] and
// has value "val".
double A[MAXC+1][MAXN+1], b[MAXC], c[MAXN], x[MAXN], val;
int xB[MAXC], xN[MAXN]; // For internal use only.
// Variable xB[r] exits the basis, xN[c] enters the basis.
void pivot(int n, int m, int r, int c) {
  for (int j = 0; j <= n; ++j)
    if (j != c)
      A[r][j] /= A[r][c];
  for (int i = 0; i <= m; ++i)
    if (i != r && fabs(A[i][c]) > EPS)
      for (int j = 0; j <= n; ++j)
        if (j != c)
          A[i][j] -= A[r][j]*A[i][c];
  for (int i = 0; i <= m; ++i)
    if (i != r)
      A[i][c] = -A[i][c]/A[r][c];
  A[r][c] = 1/A[r][c];
  swap(xB[r], xN[c]);
}
// Bland's rule: if two indices are valid choices for the pivot, choose
// the one with the lexicographically smallest variable
void bland(int a, int& b, int* v) {
  if (b < 0 || v[a] < v[b]) b = a;
}
// Returns true if a feasible basis is found, false if LP is infeasible.
// Idea: Try the all-0 solution (i.e. basis where the x >= 0 constraints
// are tight). Repeatedly pivot out any row with a negative b-entry.
bool phase1(int n, int m) {
  while (true) { // pivot while some b-value is negative
    int r = -1, c = -1;
    for (int i = 0; i < m; ++i)
      if (A[i][n] < -EPS)
        bland(i, r, xB);
    if (r == -1) return true;
    for (int j = 0; j < n; ++j)
      if (A[r][j] < -EPS)
        bland(j, c, xN);
    if (c == -1) return false;
    pivot(n, m, r, c);
  }
}
// Assumes A[i][n] >= 0 for all 0 <= i < m (i.e. current basis is
// feasible). Returns true if an optimum is found, false if the LP is
// unbounded.
bool phase2(int n, int m) {
  while (true) { // pivot until no improvement
    int r = -1, c = -1;
    // find a column with negative c-coefficient
    // yes, it should be A[m][j] > EPS even though we said "negative",
    // this is because row A[m] is storing -c
    for (int j = 0; j < n; ++j)
      if (A[m][j] > EPS)
        bland(j, c, xN);
    if (c == -1) return true;
    for (int i = 0; i < m; ++i)
      if (A[i][c] > EPS) {
        if (r == -1) r = i;
        else {
          double lhs = A[i][c]*A[r][n], rhs = A[r][c]*A[i][n];
          if (lhs > rhs + EPS) r = i;
          else if (fabs(lhs-rhs) < EPS) bland(i, r, xB);
        }
      }
    if (r == -1) return false;
    pivot(n, m, r, c);
  }
}
// Returns: 1 - opt found (x is this opt and val is its value)
//          0 - infeasible, -1 - unbounded
int simplex(int n, int m) {
  //add b to the end of A and c to the bottom of A
  for (int j = 0; j < n; ++j) {
    A[m][j] = c[j];
    xN[j] = j;
  }
  // prepare initial (possibly infeasible) basis
  for (int i = 0; i < m; ++i) {
    A[i][n] = b[i];
    xB[i] = i+n;
  }
  A[m][n] = 0; //this will be -(value of x)
  if (!phase1(n, m)) return 0; // pivot to a feasible basis
  if (!phase2(n, m)) return -1; // then pivot to an optimum basis
  // recover x and val
  val = -A[m][n];
  for (int i = 0; i < n; ++i) x[i] = 0;
  for (int i = 0; i < m; ++i)
    if (xB[i] < n)
      x[xB[i]] = A[i][n];
  return 1;
}
