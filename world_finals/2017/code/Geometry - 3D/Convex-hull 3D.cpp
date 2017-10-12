#include "Primitives.cpp"
// vector<hullFinder::hullFace> hull=hullFinder(pts).findHull();
// 'hull' will have triangular faces of convex-hull of the given
// points 'pts'. Some of them might be co-planar.
// There are O(pts.size()) of those disjoint triangles that
// cover all surface of convex hull
// Each element of hull is a hullFace which has indices of three
// vertices of a triangle
bool operator==(const point3 &p, const point3 &q) { return abs(p.x - q.x) < eps && abs(p.y - q.y) < eps && abs(p.z - q.z) < eps; }
point3 triNormal(const point3 &a, const point3 &b, const point3 &c) { return cross(a, b) + cross(b, c) + cross(c, a); }
class hullFinder {
  const vector<point3> &pts;
public:
  hullFinder(const vector<point3> &pts_) : pts(pts_), halfE(pts.size(), -1) {}
  struct hullFace {
    int u, v, w;
    point3 n;
    hullFace(int u_, int v_, int w_, const point3 &n_) : u(u_), v(v_), w(w_), n(n_) {}
  };
  vector<hullFinder::hullFace> findHull() {
    vector<hullFace> hull;
    int n = pts.size();
    if(n < 4) return hull;
    int p3 = 2;
    point3 tNorm;
    while(p3 < n && (tNorm = triNormal(pts[0], pts[1], pts[p3])) == point3()) ++p3;
    int p4 = p3 + 1;
    while(p4 < n && abs(dot(tNorm, pts[p4] - pts[0])) < eps) ++p4;
    if(p4 >= n) return hull;
    edges.clear();
    edges.push_front(hullEdge(0, 1));
    setF1(edges.front(), p3);
    setF2(edges.front(), p3);
    edges.push_front(hullEdge(1, p3));
    setF1(edges.front(), 0);
    setF2(edges.front(), 0);
    edges.push_front(hullEdge(p3, 0));
    setF1(edges.front(), 1);
    setF2(edges.front(), 1);
    addPt(p4);
    for(int i = 2; i < n; ++i)
      if(i != p3 && i != p4) addPt(i);
    for(list<hullEdge>::const_iterator e = edges.begin(); e != edges.end(); ++e) {
      if(e->u < e->v && e->u < e->f1)
        hull.push_back(hullFace(e->u, e->v, e->f1, e->n1));
      else if(e->v < e->u && e->v < e->f2)
        hull.push_back(hullFace(e->v, e->u, e->f2, e->n2));
    }
    return hull;
  }
private:
  struct hullEdge {
    int u, v, f1, f2;
    point3 n1, n2;
    hullEdge(int u_, int v_) : u(u_), v(v_), f1(-1), f2(-1) {}
  };
  list<hullEdge> edges;
  vector<int> halfE;
  void setF1(hullEdge &e, int f1) {
    e.f1 = f1;
    e.n1 = triNormal(pts[e.u], pts[e.v], pts[e.f1]);
  }
  void setF2(hullEdge &e, int f2) {
    e.f2 = f2;
    e.n2 = triNormal(pts[e.v], pts[e.u], pts[e.f2]);
  }
  void addPt(int i) {
    for(list<hullEdge>::iterator e = edges.begin(); e != edges.end(); ++e) {
      bool v1 = dot(pts[i] - pts[e->u], e->n1) > eps;
      bool v2 = dot(pts[i] - pts[e->u], e->n2) > eps;
      if(v1 && v2)
        e = --edges.erase(e);
      else if(v1) {
        setF1(*e, i);
        addCone(e->u, e->v, i);
      } else if(v2) {
        setF2(*e, i);
        addCone(e->v, e->u, i);
      }
    }
  }
  void addCone(int u, int v, int apex) {
    if(halfE[v] != -1) {
      edges.push_front(hullEdge(v, apex));
      setF1(edges.front(), u);
      setF2(edges.front(), halfE[v]);
      halfE[v] = -1;
    } else
      halfE[v] = u;
    if(halfE[u] != -1) {
      edges.push_front(hullEdge(apex, u));
      setF1(edges.front(), v);
      setF2(edges.front(), halfE[u]);
      halfE[u] = -1;
    } else
      halfE[u] = v;
  }
};
