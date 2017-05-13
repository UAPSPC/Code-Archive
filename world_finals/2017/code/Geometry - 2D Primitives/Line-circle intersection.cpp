// Intersects (infinite) line a-b with circle c
// Intersection points are in 'inter'
// 0 -> no intersection, 1 -> tangent, 2 -> two intersections
int line_circ_inter(point a, point b, circle c, vector<point> &inter) {
    c.c -= a; b -= a;
    point m = b*real(c.c/b);
    double d2 = norm(m-c.c);
    if (d2 > c.r*c.r) return 0;
    double l = sqrt((c.r*c.r-d2)/norm(b));
    inter.push_back(a + m + l*b);
    if(abs(l)>eps)
        inter.push_back(a + m - l*b);
    return inter.size();
}
