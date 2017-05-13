// Returns all prime numbers in [0,n]
int isnprime[maxn];
vector<int> sieve(int n) {
    memset(isnprime,0,sizeof isnprime);
    isnprime[0] = isnprime[1] = 1;
    vector<int> ps;
    for(int i=2;i<n;i++)
        if(!isnprime[i]) {
            ps.push_back(i);
            if(n/i>=i)
                for(int j=i*i;j<=n;j+=i)
                    isnprime[j]=1;
        }
    return ps;
}
