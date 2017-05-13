const int inf=(int)1e9;
const int maxn = 300;
int x[maxn][maxn],m;
int c[maxn][maxn],n;
int f[maxn][maxn];
int flow_k,flow_t,mark[maxn];
int dfs(int v,int m){
    if (v==flow_t) return m;
    for (int i=0,x;i<n;++i)
        if ((c[v][i]-f[v][i]>=flow_k) && !mark[i]++)
            if (x=dfs(i,min(m,c[v][i]-f[v][i])))
                return (f[i][v]=-(f[v][i]+=x)),x;
    return 0;
}
// Input: n(# of vertices),s(source),t(sink),c[n][n](capacities)
// Finds flow from i to j (i.e. f[i][j]) in the maximum flow
// where f[i][j]=-f[j][i]
// Requirements: f[i][j] should be filled with initial flow
// before calling the function and c[i][j] >= f[i][j]
void flow(int s,int t){
    int flow_ans =0;
    flow_t = t;
    flow_k = 1;
    for (int i=0;i<n;++i)
        for (int j=0;j<n;++j)
            for (;flow_k<c[i][j];flow_k*=2);
    for (;flow_k;flow_k/=2){
        memset(mark,0,sizeof mark);
        for (;dfs(s,inf);)
            memset(mark,0,sizeof mark);
    }
}
// Input: m(# of vertices), x[m][m](capacities)
// Finds f[i][j] in a circular flow satisfying x[i][j]
// If you have a real sink and source set x[sink][source]=inf
// x[i][j]<0 means capacity of i->j is zero and a flow of at
// least abs(x[i][j]) should go from j to i.
// If you have two capacities for i->j and j->i and some
// min flow for at least one of them you should resolve this
// before calling the function by filling some flow in f[i][j]
// and f[j][i]
// Returns false when can't satisfy x and returns false when
// x[i][j] and x[j][i] are both negative. Check this if needed
bool negative_flow(){
    for (int i=0;i<m;++i)
        for (int j=0;j<m;++j){
            if (x[i][j]<0){
                if (x[j][i]<0) return false;
                continue;
            }
            if (x[j][i]>=0){
                c[i][j]=x[i][j];
                continue;
            }
            c[i][j]=x[i][j]+x[j][i];
            c[j][i]=0;
            c[i][m+1]-=x[j][i];
            c[m][j]-=x[j][i];
            if (c[i][j]<0) return false;
        }
    n=m+2;
    flow(n-2,n-1);
    for (int i=0;i<m;++i)
        if (c[m][i]!=f[m][i])
            return false;
    for (int i=0;i<m;++i)
        for (int j=0;j<m;++j)
            if (x[i][j]<0){
                f[i][j]+=x[i][j];
                f[j][i]-=x[i][j];
            }
    return true;
}
