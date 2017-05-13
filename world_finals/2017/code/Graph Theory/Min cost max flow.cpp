//Input (zero based, non­negative edges):~
// n = |V|, e = |E|, s = source, t = sink 
// cost[v][u] = cost for each unit of flow from v to u
// cap[v][u] = copacity
//Output of mcf():
// Flow contains the flow value
// Cost contains the minimum cost
// f[n][n] contains the flow
const int maxn = 300;
const int inf = 1e9;
int cap[maxn][maxn],cost[maxn][maxn], f[maxn][maxn];
int p[maxn], d[maxn] , mark[maxn], pi[maxn];
int n , s , t, Flow , Cost;
int pot(int u,int v){
    return d[u] + pi[u] ­ pi[v];
}
int dijkstra(){
    memset( mark , 0 , sizeof mark );
    memset( p , ­1 , sizeof p );
    for( int i = 0; i <= n; i++ )
        d[i] = inf;
    d[s] = 0;
    while(1){
        int u = n;
        for( int i=0; i<n; i++ )
            if( !mark[i] && d[i] < d[u] )
                u = i;
        if(u==n) break;
        mark[u] = 1;
        for (int v=0 ; v<n ; v++){
            if(!mark[v] && f[v][u] && d[v]>pot(u,v)­cost[v][u]){
                d[v] = pot(u,v) ­ cost[v][u];
                p[v] = u;
            }
            if( !mark[v] && f[u][v] < cap[u][v] && d[v] > 
pot(u,v) + cost[u][v] ){
                d[v] = pot(u,v) + cost[u][v];
                p[v] = u;
            }
        }
    }
    for( int i = 0; i < n; i++ )
        if( pi[i] < inf )
            pi[i] += d[i];
    return mark[t];
}
void mcf(){
    memset( f , 0 , sizeof f );
    memset( pi , 0 , sizeof pi );
    Flow = Cost = 0;
    while(dijkstra()){
        int min = inf;
        for (int x = t ; x!=s ; x=p[x])
            if (f[x][p[x]])
                min = std::min(f[x][p[x]], min);
            else
                min = std::min(cap[p[x]][x] ­ f[p[x]][x], min);
        for (int x = t ; x!=s ; x=p[x])
            if (f[x][p[x]]){
                f[x][p[x]] ­= min;
                Cost ­= min*cost[x][p[x]];
            }else{
                f[p[x]][x] += min;
                Cost += min*cost[p[x]][x];
            }
        Flow += min;
    }
}
