const int maxn = 1<<20; //must be a power of 2
long long seg[2*maxn];
// Add the value 'val' to the index 'num'
void add(int num, long long val) {
    num+=maxn;
    while(num>0) {
        seg[num]+=val;
        num>>=1;    
    }
}
// returns sum of the elements in range [0,num]
long long get(int num) {
    num+=maxn;
    long long ans = 0;
    ans=seg[num]; // Comment this to change the range to [0,num)
    while(num>0) {
        if(num&1) {
            ans+=seg[num&(~1)];
        }
        num>>=1;
    }
    return ans;
}
