// Returns number of circles that pass through point p and are~
// tangent to the lines a­b and c­d
// 'ans' has all possible circles with radius greater than zero
int get_circle(point p, point a, point b, point c, point d, 
vector<circle> &ans) {
    point inter;
    int st = line_line_inter(a,b,c,d,inter);
    if(st==­1) return 0;
    d­=c;
    b­=a;
    vector<point> ta;
    if(st==0) {
        point pa = point(0,imag((a­c)/d)/2)*d+c;
        point pb = b+pa;
        parabola_line_inter(p,a,a+b,pa,pb,ta);
    } else {
        if(abs(inter­p)>eps) {
            point bi;
            bi = polar(1.0,(arg(b)+arg(d))/2)+inter;
            vector<point> temp;
            parabola_line_inter(p,a,a+b,inter,bi,temp);
            ta.insert(ta.end(),temp.begin(),temp.end());
            temp.clear();
            bi = polar(1.0,(arg(b)+arg(d)+M_PI)/2)+inter;
            parabola_line_inter(p,a,a+b,inter,bi,temp);
            ta.insert(ta.end(),temp.begin(),temp.end());
        }
    }
    for(int i=0;i<ta.size();i++)
        ans.push_back(circle(ta[i],abs(p­ta[i])));
    return ans.size();
}
