const double eps = 1e­7;~
bool zero(double a){return (a<eps) && (a>­eps);}
// m = number of equations, n = number of variables, 
// a[m][n+1] = coefficients matrix
// Returns double ans[n] containing the solution, if there is no
// solution returns NULL
double* solve(double **a, int m, int n){
    int cur=0;
    for (int i=0;i<n;++i){
        for (int j=cur;j<m;++j)
            if (!zero(a[j][i])){
                if (j!=cur) swap(a[j],a[cur]);
                for (int sat=0;sat<m;++sat){
                    if (sat==cur) continue;
                    double num=a[sat][i]/a[cur][i];
                    for (int sot=0;sot<=n;++sot)
                        a[sat][sot]­=a[cur][sot]*num;
                }
                cur++;
                break;
            }
    }
    for (int j=cur;j<m;++j)
        if (!zero(a[j][n]))
            return NULL;
    double* ans = new double[n];
    for (int i=0,sat=0;i<n;++i){
        ans[i] = 0;
        if (sat<m && !zero(a[sat][i])){
            ans[i] = a[sat][n] / a[sat][i];
            sat++;
        }
    }
    return ans;
}
