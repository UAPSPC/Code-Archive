// Can rectangle with dims x*y fit inside box with dims w*h?
// Returns true for a "tight fit", if false is desired then swap
// strictness of inequalities.
bool rect_in_rect(double x, double y, double w, double h) {
    if (x > y) swap(x, y);
    if (w > h) swap(w, h);
    if (w < x) return false;
    if (y <= h) return true;
    double a = y*y - x*x;
    double b = x*h - y*w;
    double c = x*w - y*h;
    return a*a <= b*b + c*c;
}
