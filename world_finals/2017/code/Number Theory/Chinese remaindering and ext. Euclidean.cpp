typedef long long int LLI;
LLI mod(LLI a, LLI m) { return ( (a%m) + m) % m; }
// Assumes non-negative input. Returns d such that d=a*ss+b*tt
LLI gcdex(LLI a, LLI b, LLI &ss, LLI &tt) {
    if (b==0){
        ss = 1;
        tt = 0;
        return a;
    }
    LLI g = gcdex(b,a%b,tt,ss);
    tt = tt - (a/b) * ss;
    return g;
}
// Returns x such that 0<=x<lcm(m_0, ..., m_(n-1)) and
// x==a_i (mod m_i), if such an x exists. If x does not exist -1
// is returned.
LLI chinese_rem(vector<LLI> &a, vector<LLI> &m) {
    LLI g, s, t, a_tmp, m_tmp;
    a_tmp = mod(a[0], m[0]);
    m_tmp = m[0];
    for (int i = 1; i < a.size(); ++i) {
        g = gcdex(m_tmp, m[i], s, t);
        if ((a_tmp - a[i]) % g) return -1;
        a_tmp = mod(a_tmp + (a[i] - a_tmp) / g * s * m_tmp,
m_tmp/g*m[i]);
        m_tmp = m[i] * m_tmp / gcdex(m[i], m_tmp, s, t);
    }
    return a_tmp;
}
