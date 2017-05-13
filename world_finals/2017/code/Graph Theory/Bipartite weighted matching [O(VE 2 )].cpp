// Input: n, m, w[n][m] (n <= m)~
//        w[i][j] is the weight between the i­th vertex of part1
//        and the j­th vertex of part2. w[i][j] can be any
//        integer (including negative values)
// Output: res, size of res is n
const int inf = 1e7;
const int maxn=200,maxm=200;
int n, m, w[maxn][maxm],u[maxn], v[maxm];
int mark[maxn],mate[maxm], matched[maxn];
int dfs(int x){
    if (x<0) return 1;
    if (mark[x]++) return 0;
    for (int i=0 ; i<m ; i++)
        if (u[x]+v[i]­w[x][i]==0)
            if (dfs(mate[i]))
                return matched[mate[i]=x]=1;
    return 0;
}
void _2matching(){
    memset( mate , ­1 , sizeof mate );
    memset( mark , 0 , sizeof mark );
    memset( matched , 0 , sizeof matched );
    for (int i=0 ; i<n ; i++)
        for (int j=0 ; j<m ; j++)
            if (mate[j]<0 && u[i]+v[j]­w[i][j]==0){
                matched[mate[j]=i]=1;
                break;
            }
    for (int i=0 ; i<n ; i++)
        if (!matched[i])
            if (dfs(i))
                memset( mark , 0 , sizeof mark );
}
void wmatching(vector <pair<int, int> > &res){
    for (int i=0 ; i<m ; i++)
        v[i] = 0;
    for (int i=0 ; i<n ; i++){
        u[i] = ­inf;
        for (int j=0 ; j<m ; j++)
            u[i] = max(u[i],w[i][j]);
    }
    memset( mate , ­1 , sizeof mate );
    memset( matched , 0 , sizeof matched );
    int counter = 0;
    while (counter!=n){
        for (int flag = 1; flag ; ){
            flag = 0;
            memset( mark , 0 , sizeof mark );
            for (int i=0 ; i<n ; i++)
                if (!matched[i] && dfs(i)){
                    counter++;
                    flag = 1;
                    memset(mark,0,sizeof mark);
                }
        }
        int epsilon = inf;
        for (int i=0 ; i<n ; i++)
            for (int j=0 ; j<m ; j++){
                if (!mark[i]) continue;
                if (mate[j]>=0)
                    if (mark[mate[j]]) continue;
                epsilon = min(epsilon, u[i] + v[j] ­ w[i][j]);
            }
        for (int i=0 ; i<n ; i++)
            if (mark[i])
                u[i] ­= epsilon;
        for (int j=0 ; j<m ; j++)
            if (mate[j]>=0)
                if (mark[mate[j]])
                    v[j] += epsilon;
    }
    res.clear();
    for (int i=0 ; i<m ; i++)
        if (mate[i]!=­1)
            res.push_back(pair<int,int>(mate[i],i));
}
