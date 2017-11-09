#include "Basics.cpp"
// Is z to left of line a-b?
bool IsLeftOf(point a, point b, point z, bool includeStraight) {
    double res = cross(b - a, z - a);
    if (includeStraight && res > -eps)
        return true;
    else return res > eps;
}