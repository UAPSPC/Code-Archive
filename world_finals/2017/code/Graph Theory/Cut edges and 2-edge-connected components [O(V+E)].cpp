//input (zero based):
//       g[n] should be the adjacency list of the graph
//       g[i] is a vector of int
//output of cut_edge():
//        cut_edges is a vector of pair<int, int>
//        comp[comp_size] contains the 2 connected components
//        comp[i] is a vector of int
const int maxn = 1000;
typedef pair<int, int> edge;
vector<int> g[maxn];
int n, mark[maxn] , d[maxn] , jad[maxn];
vector<edge> cut_edges;
//for components only
vector<int> comp[maxn];
int comp_size;
vector<int> comp_stack;
//
void dfs(int x, int level){
    mark[x] = 1;
    //for components only
    comp_stack.push_back(x);
    //
    int t = 0;
    for (int i=0 ; i<(int)g[x].size() ; i++){
        int u = g[x][i];
        if (!mark[u]){
            jad[u] = d[u] = d[x] + 1;
            dfs(u, level+1);
            jad[x] = std::min(jad[u], jad[x]);
            if (jad[u]==d[u]){
                cut_edges.push_back(edge(u, x));
                //for components only
                while (comp_stack.back() != u){
                   comp[comp_size].push_back(comp_stack.back());
                   comp_stack.pop_back();
                }
                comp[comp_size++].push_back(u);
                comp_stack.pop_back();
                //
            }
        }else{
            if (d[u] == d[x] - 1) t++;
            if (d[u] != d[x] - 1 || t!=1)
                jad[x] = std::min(d[u], jad[x]);
        }
    }
    //for components only
    if (level == 0){
        while (comp_stack.size() > 0){
            comp[comp_size].push_back(comp_stack.back());
            comp_stack.pop_back();
        }
        comp_size++;
    }
    //
}
void cut_edge(){
    memset( mark , 0 , sizeof mark );
    memset( d , 0 , sizeof d );
    memset( jad , 0  , sizeof jad );
    cut_edges.clear();
    //for components only
    for (int i=0 ; i<maxn ; i++) comp[i].clear();
    comp_stack.clear();
    comp_size = 0;
    //
    for (int i=0 ; i<n ; i++)
        if (!mark[i]) dfs(i, 0);
}
