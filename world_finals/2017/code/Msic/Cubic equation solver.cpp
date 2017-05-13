//Solves ax^3 + bx^2 + cx + d = 0
vector<double> solve_cubic(double a, double b, double c, double
d) {
    long double a1 = b/a, a2 = c/a, a3 = d/a;
    long double q = (a1*a1 - 3*a2)/9.0, sq = -2*sqrt(q);
    long double r = (2*a1*a1*a1 - 9*a1*a2 + 27*a3)/54.0;
    double z = r*r-q*q*q, theta;
    vector <double> res; res.clear();
    if (z<=0) {
        theta = acos(r/sqrt(q*q*q));
        res.push_back(sq*cos(theta/3.0) - a1/3.0);
        res.push_back(sq*cos((theta+2.0*M_PI)/3.0) - a1/3.0);
        res.push_back(sq*cos((theta+4.0*M_PI)/3.0) - a1/3.0);
        return res;
    }
    double v = pow(sqrt(z)+fabs(r),1/3.0);
    v += q/v;
    v *= (r < 0) ? 1 : -1;
    v -= a1 / 3.0;
    res.push_back(v);
    return res;
}
