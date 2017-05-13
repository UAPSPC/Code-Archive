// Intersect of segments a­b and c­d~
//   ­2  ­> not parallel and no intersection
//   ­1  ­> coincide with no common point
//    0  ­> parallel and not coincide
//    1  ­> intersected ('p' is intersection of segments)
//    2  ­> coincide with common points ('p' is one of the end
//          points lying on both segments)
int seg_seg_inter(point a, point b, point c, point d, point &p) 
{
    int s = line_line_inter(a,b,c,d,p);
    if(s==0)
        return 0;
    if(s==­1) {
        // '<­eps' excludes endpoints in the coincide case
        if(dot(a­c,a­d)<eps) {
            p = a;
            return 2;
        }
        if(dot(b­c,b­d)<eps) {
            p=b;
            return 2;
        }
        if(dot(c­a,c­b)<eps) {
            p=c;
            return 2;
        }
        return ­1;
    }
    // '<­eps' excludes endpoints in intersected case
    if(dot(p­a,p­b)<eps && dot(p­c,p­d)<eps) 
        return 1;
    return ­2;
}
