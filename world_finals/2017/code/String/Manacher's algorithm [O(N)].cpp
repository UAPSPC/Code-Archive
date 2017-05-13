// Returns half of length of largest panlindrome centered at
// every position in the string
vector<int> manacher(string s) {
    vector<int> ans(s.size(),0);
    int maxi = 0;
    for(int i=1;i<s.size();i++) {
        int k = 0;
        if(maxi+ans[maxi]>=i)
            k = min(ans[maxi]+maxi-i,ans[2*maxi-i]);
        for(;s[i+k]==s[i-k] && i-k>=0 && i+k<s.size();k++);
        ans[i] = k-1;
        if(i+ans[i]>maxi+ans[maxi])
            maxi = i;
    }
    return ans;
}
