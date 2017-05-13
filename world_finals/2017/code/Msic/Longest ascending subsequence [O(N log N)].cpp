typedef pair<int,int> pii;
int comp(const pii &a, const pii &b) {
    if(a.first!=b.first)    
        return a.first<b.first;
    return a.second<b.second; // return 0 to find strictly ascending subsequence
}
vector<int> lis(const vector<int> &in) {
    vector<pii> l;
    vector<int> par(in.size(),­1);
    for(int i=0;i<in.size();i++) {
        int ind = lower_bound(l.begin(),l.end(),pii(in[i],i),comp)-l.begin();
        if(ind==l.size())
            l.push_back(pii(0,0));
        l[ind] = pii(in[i],i);
        if(ind!=0)
            par[i] = l[ind-1].second;
    }
    vector<int> ans;
    int ind = l.back().second;
    while(ind!=-1) {
        ans.push_back(in[ind]);
        ind = par[ind];
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
