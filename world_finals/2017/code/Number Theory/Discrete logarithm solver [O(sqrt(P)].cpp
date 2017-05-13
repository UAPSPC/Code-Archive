// Given prime P, B>0, and N, finds least L ~
// such that B^L==N (mod P)
// Returns ­1, if no such L exist.
map<int,int> mow;
int times(int a, int b, int m) {
    return (long long) a * b % m;
}
int power(int val, int power, int m) {
    int res = 1;
    for (int p = power; p; p >>= 1) {
        if (p & 1)
            res = times(res, val, m);
        val = times(val, val, m);
    }
    return res;
}
int discrete_log(int p, int b, int n) {
    int jump = sqrt(double(p));
    mow.clear();
    for (int i = 0; i < jump && i < p­1; ++i)
        mow[power(b,i,p)] = i+1;
    for (int i = 0, j; i < p­1; i += jump)
        if (j = mow[times(n,power(b,p­1­i,p),p)])
            return (i+j­1)%(p­1);
    return ­1;
}
