// outside ­> 0, inside ­> 1, on the border ­> 2~
int pt_in_poly(const vector<point> &p, const point &a) {
    int n = p.size(); int inside = false;
    for (int i=0, j=n­1; i<n; j=i++) {
        if (abs(cross(a­p[i],a­p[j]))<eps && dot(a­p[i],a­
p[j])<eps)
            return 2;
        if (((imag(p[i])<=imag(a)) && (imag(a)<imag(p[j]))) || 
((imag(p[j])<=imag(a))) && (imag(a)<imag(p[i])))
            if (real(a)­real(p[i]) < (real(p[j])­
real(p[i]))*(imag(a)­imag(p[i])) / (imag(p[j])­imag(p[i])))
                inside = !inside;
    }
    return inside;
}
