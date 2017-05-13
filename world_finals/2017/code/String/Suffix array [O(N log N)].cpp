// Calculate the order of suffix starting from j­th character~
// with length 2^i compared to other starting points
// order[i][j]>=0: order of suffix starting from j­th character 
// with length 2^i
// suffix(j1,i)=suffix(j2,i) ­> order[i][j1]=order[i][j2]
// suffix(j1,i)<suffix(j2,i) ­> order[i][j1]<order[i][j2]
typedef pair<int,int> pii;
typedef pair<pii,int> p3i;
int order[maxlog][maxn]; 
// if N*log^2(N) is good enough don't write the next function
vector<p3i> buck[maxn];
void radix(vector<p3i> &a, int n, int t){
    for (int i=0 ; i<=n ; i++)
        buck[i].clear();
    for (int i=0 ; i<a.size() ; i++){
        int x;
        switch(t){
            case 1: x = a[i].first.first; break;
            case 2: x = a[i].first.second; break;
            case 3: x = a[i].second; break;
        }
        buck[x+1].push_back(a[i]);
    }
    a.clear();
    for (int i=0 ; i<=n ; i++)
        for (int j=0 ; j<buck[i].size() ; j++)
            a.push_back(buck[i][j]);
}
void suffix_array(vector<int> in) {
    int n = in.size();
    vector<p3i> sorted;
    for(int i=0;i<n;i++)
        sorted.push_back(p3i(pii(in[i],in[i]),i));
    sort(sorted.begin(), sorted.end());
    for(int k=0;k<maxlog;k++) {
        int cur = 0;z
        for (int i=0;i<n;i++) {
            if(i>0 && sorted[i­1].first!=sorted[i].first)
                cur++;
            order[k][sorted[i].second] = cur;
        }
        for(int i=0;i<n;i++) {
            int o1 = order[k][i];
            int o2 = ­1;
            // Uncomment next line for non­circular sorting
            // if (i+(1<<k)<n)
                o2 = order[k][(i+(1<<k))%n];
            sorted[i] = p3i(pii(o1,o2),i);
        }
        // if n*log^2(n) is good enough use the following line 
instead of the three radixes
        // sort(sorted.begin(), sorted.end());
        radix(sorted, n, 3);
        radix(sorted, n, 2);
        radix(sorted, n, 1);
    }
}
int common_prefix(int n, int i, int j) {
    int ans = 0;
    // Uncomment next line for non­circular sorting
    // if(i==j) return n­i­1; 
    for(int k=maxlog­1;k>=0;k­­) {
        if(order[k][i]==order[k][j]) {
            i=(i+(1<<k))%n;
            j=(j+(1<<k))%n;
            ans+=1<<k;
        }
    }
    return min(ans,n);
}
