// Assumes pts.size()>0 and returns ccw convex hull with no~
// 3 collinear points and with duplicated left most side node
int comp(const point &a,const point &b) {
    if(abs(a.real()­b.real())>eps)
        return a.real()<b.real();
    if(abs(a.imag()­b.imag())>eps)
        return a.imag()<b.imag();
    return 0;
}
inline vector<point> convexhull (vector<point> &pts) {
    sort(pts.begin(),pts.end(),comp);
    vector<point> lower, upper;
    for(int i=0; i<(int)pts.size(); i++) {
        // <­eps include all points on border
        while (lower.size() >= 2 && cross(lower.back()­
lower[lower.size()­2], pts[i]­lower.back()) < eps) 
            lower.pop_back();
        // >eps include all points on border
        while (upper.size() >= 2 && cross(upper.back()­
upper[upper.size()­2], pts[i]­upper.back()) > ­eps) 
            upper.pop_back();
        lower.push_back(pts[i]);
        upper.push_back (pts[i]);
    }
    lower.insert (lower.end(), upper.rbegin() + 1, 
upper.rend());
    return lower;
}
