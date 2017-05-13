const int maxn = 1000;//Max # of vertices
int n;//# of vertices
vector <pair<int,int> > v[maxn];//weighted adjacency list
int d[maxn];//distance from source
struct comp {
    bool operator () (int a, int b)
    { return (d[a]!=d[b]) ? d[a]<d[b] : a<b; }
};
set <int,comp> mark;
void dijkstra (int source) {
    memset(d, -1, sizeof d);
    d[source] = 0;
    mark.clear();
    for (int i=0;i<n;++i)
        mark.insert(i);
    while (mark.size()){
        int x = *mark.rbegin();
        mark.erase(x);
        if (d[x]==-1)
            break;
        for (vector<pair<int,int> >::iterator it = v[x].begin()
; it != v[x].end() ; ++it){
            if (d[it->first]==-1 || d[x]+it->second < d[it-
>first]){
                mark.erase(it->first);
                d[it->first] = d[x]+it->second;
                mark.insert (it->first);
            }
        }
    }
}
