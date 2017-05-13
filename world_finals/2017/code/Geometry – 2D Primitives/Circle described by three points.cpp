// Returns whether they form a circle or not.~
// 'center' and 'r' contain the circle if there is one
bool get_circle(point p1, point p2, point p3, point &center, 
double &r) {
    double g = 2*imag(conj(p2­p1)*(p3­p2));
    if (abs(g) < eps) return false;
    center = p1*(norm(p3)­norm(p2));
    center += p2*(norm(p1)­norm(p3));
    center += p3*(norm(p2)­norm(p1));
    center /= point(0, g); r = abs(p1­center);
    return true;
}
