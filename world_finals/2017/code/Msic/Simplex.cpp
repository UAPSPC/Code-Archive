// m - number of (less than) inequalities
// n - number of variables
// c - (m+1) by (n+1) array of coefficients:
//   row 0        - objective function coefficients
//   row 1:m      - less-than inequalities
//   column 0:n-1 - inequality coefficients
//   column n     - inequality constants (0 for obj. function) 
// x[n] - result variables
// Returns value - maximum value of objective function
//   (-inf for infeasible, inf for unbounded)
const int maxm = 400;  // leave one extra
const int maxn = 400;  // leave one extra
const double eps = 1e-9;
const double inf = 1.0/0.0; 
double ine[maxm][maxn];
int basis[maxm], out[maxn];
void pivot(int m, int n, int a, int b) {
    int i,j;
    for (i=0;i<=m;i++)
        if (i!=a)
            for (j=0;j<=n;j++)
                if (j!=b)
                    ine[i][j] -= ine[a][j]*ine[i][b]/ine[a][b];
    for (j=0;j<=n;j++)
        if (j!=b) ine[a][j] /= ine[a][b];
    for (i=0;i<=m;i++)
        if (i!=a) ine[i][b] = -ine[i][b]/ine[a][b];
    ine[a][b] = 1/ine[a][b];
    i = basis[a];
    basis[a] = out[b];
    out[b] = i;
}
double simplex(int m, int n, double c[][maxn], double x[]) {
    int i,j,ii,jj;
    for (i=1;i<=m;i++)
        for (j=0;j<=n;j++)
            ine[i][j] = c[i][j];
    for (j=0;j<=n;j++)
        ine[0][j] = -c[0][j];
    for (i=0;i<=m;i++)
        basis[i] = -i;
    for (j=0;j<=n;j++)
        out[j] = j;
    for(;;) {
        for (i=ii=1;i<=m;i++)
            if (ine[i][n]<ine[ii][n] || (ine[i][n]==ine[ii][n]
&& basis[i]<basis[ii]))
                ii=i;
        if (ine[ii][n] >= -eps) break;
        for (j=jj=0;j<n;j++)
            if (ine[ii][j]<ine[ii][jj]-eps || (ine[ii]
[j]<ine[ii][jj]-eps && out[i]<out[j]))
                jj=j;
        if (ine[ii][jj] >= -eps) return -inf;
        pivot(m,n,ii,jj);
    }
    for(;;) {
        for (j=jj=0;j<n;j++)
            if (ine[0][j]<ine[0][jj] || (ine[0][j]==ine[0][jj] 
&& out[j]<out[jj]))
                jj=j;
        if (ine[0][jj] > -eps) break;
        for (i=1,ii=0;i<=m;i++)
            if ((ine[i][jj]>eps) &&
                    (!ii || (ine[i][n]/ine[i][jj] < ine[ii]
[n]/ine[ii][jj]-eps) ||
                     ((ine[i][n]/ine[i][jj] < ine[ii][n]/ine[ii]
[jj]+eps) &&
                      (basis[i] < basis[ii]))))
                ii=i;
        if (ine[ii][jj] <= eps) return inf;
        pivot(m,n,ii,jj);
    }
    for (j=0;j<n;j++)
        x[j] = 0;
    for (i=1;i<=m;i++)
        if (basis[i] >= 0)
            x[basis[i]] = ine[i][n];
    return ine[0][n];
}
