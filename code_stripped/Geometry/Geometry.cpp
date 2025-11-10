struct PT { T x, y; };
//  Basic Vector Operations 
// Subtract two points: returns vector b→a
PT sub(PT a, PT b){ return {a.x - b.x, a.y - b.y}; }
// Add two vectors/points
PT add(PT a, PT b){ return {a.x + b.x, a.y + b.y}; }
// Scale vector by scalar s
PT mul(PT a, T s){ return {a.x * s, a.y * s}; }
//Dot, Cross, and Distances
// Dot product: projection magnitude measure
inline T dot(PT a, PT b){ return a.x*b.x + a.y*b.y; }
// 2D cross product: signed area of parallelogram
inline T cross(PT a, PT b){ return a.x*b.y - a.y*b.x; }
// Squared Euclidean distance (avoid sqrt)
inline T dist2(PT a, PT b){ PT d = sub(a,b); return dot(d,d); }
// Euclidean distance between points
inline T dist(PT a, PT b){ return sqrt(dist2(a,b)); }
//  Orientation Test 
// Returns +1 if a→b→c make a CCW turn, -1 if CW, 0 if collinear
int orient(PT a, PT b, PT c){
T z = cross(sub(b,a), sub(c,a));
return (z > eps) - (z < -eps);
}
// Projection & Reflection 
// Project point p orthogonally onto infinite line a→b
PT proj(PT a, PT b, PT p){
PT v = sub(b,a);
T t = dot(sub(p,a), v) / dot(v,v);
return add(a, mul(v,t));
}
// Reflect p across line a→b (mirror image)
PT reflectP(PT a, PT b, PT p){
PT q = proj(a,b,p);
return sub(mul(q,2), p);
}
// Segment Utilities 
// Distance from point p to segment a→b
T distPointSeg(PT a, PT b, PT p){
PT v = sub(b,a), w = sub(p,a);
T c1 = dot(w,v), c2 = dot(v,v);
if(c1 <= 0) return dist(p,a);
if(c1 >= c2) return dist(p,b);
return dist(p, add(a, mul(v, c1/c2)));
}
// Check if p lies exactly on segment a→b
bool onSeg(PT a, PT b, PT p){
return fabs(cross(sub(p,a), sub(b,a)))<eps
&& dot(sub(p,a), sub(p,b)) <= 0;
}
// Line Representation & Intersection
// Infinite line in ax + by + c = 0 form
struct line {
T a,b,c;
line(PT p, PT q){
a = p.y - q.y;
b = q.x - p.x;
c = -a*p.x - b*p.y;
}
// Perpendicular distance from point p to this line
T dist(PT p) const {
return fabs(a*p.x + b*p.y + c) / sqrt(a*a + b*b);
}
};
// Proper intersection of segments a→b and c→d
// Returns true and sets o to intersection point if they cross
bool segInter(PT a, PT b, PT c, PT d, PT &o){
T A = cross(sub(b,a), sub(c,a)), B = cross(sub(b,a), sub(d,a));
if(A*B >= 0) return false;
T C = cross(sub(d,c), sub(a,c)), D = cross(sub(d,c), sub(b,c));
if(C*D >= 0) return false;
o = add(a, mul(sub(b,a), A/(A-B)));
return true;
}
// Intersection of infinite lines a→b and c→d
bool lineInter(PT a, PT b, PT c, PT d, PT &o){
line L1(a,b), L2(c,d);
T det = L1.a*L2.b - L2.a*L1.b;
if(fabs(det) < eps) return false;         
o.x = (L2.b*(-L1.c) - L1.b*(-L2.c)) / det;
o.y = (L1.a*(-L2.c) - L2.a*(-L1.c)) / det;
return true;
}
// Circle Intersections
// Intersection points of line a→b with circle centered at cen, radius r
vector<PT> circleLine(PT cen, T r, PT a, PT b){
vector<PT> R;
PT d = sub(b,a), f = sub(a,cen);
T A = dot(d,d), B = 2*dot(f,d), C = dot(f,f)-r*r, D = B*B-4*A*C;
if(D < -eps) return R;
D = max(D, (T)0);
for(T s: {1.0, -1.0}) R.push_back(add(a, mul(d, (-B + s*sqrt(D))/(2*A))));
if(R.size()==2 && dist2(R[0],R[1])<eps) R.pop_back();
return R;
}
// Intersection points of two circles (0–2 solutions)
vector<PT> circleCircle(PT c1, T r1, PT c2, T r2){
vector<PT> R;
T d = dist(c1,c2);
if(d > r1+r2+eps || d < fabs(r1-r2)-eps) return R;
T x = (d*d + r1*r1 - r2*r2)/(2*d), h = sqrt(max(r1*r1-x*x, (T)0));
PT v = mul(sub(c2,c1), 1/d), m = add(c1, mul(v,x));
R.push_back({m.x - v.y*h, m.y + v.x*h});
if(h > eps) R.push_back({m.x + v.y*h, m.y - v.x*h});
return R;
}
//  Polygon & Utility Routines
// Signed area of a simple polygon (positive if CCW)
T polyArea(const vector<PT>& P){
T A = 0;
for(int i=0,n=P.size(), j=n-1; i<n; j=i++)
A += cross(P[j], P[i]);
return A / 2;
}
// Winding-number point-in-polygon test
// Returns 0 outside, 1 inside (points on edge count as inside)
int inPoly(const vector<PT>& P, PT z){
int wn = 0, n = P.size();
for(int i=0; i<n; i++){
PT a = P[i], b = P[(i+1)%n];
if(onSeg(a,b,z)) return 1;
bool up = a.y <= z.y, vp = b.y > z.y;
if(up != vp && orient(a,b,z) > 0) wn += up ? 1 : -1;
}
return wn != 0;
}
// Rotate point p around the origin by angle t
PT rotate(PT p, T t){
return {p.x*cos(t) - p.y*sin(t),
p.x*sin(t) + p.y*cos(t)};
}
// Sort points by polar angle around origin, CCW
void polarSort(vector<PT>& v){
sort(v.begin(), v.end(), [](PT a, PT b){
bool ha = a.y>0 || (fabs(a.y)<eps && a.x<0);
bool hb = b.y>0 || (fabs(b.y)<eps && b.x<0);
if(ha != hb) return ha > hb;
return cross(a,b) > 0;
});
}
// Closest-Pair of Points (O(n log n)) 
// Returns minimal distance among all pairs in v
T closest(vector<PT>& v){
sort(v.begin(), v.end(), [](PT a, PT b){ return a.x < b.x; });
function<T(int,int)> rec = [&](int l,int r){
if(r-l < 2) return numeric_limits<T>::infinity();
int m = (l+r)/2;
T d = min(rec(l,m), rec(m,r));
inplace_merge(v.begin()+l, v.begin()+m, v.begin()+r,
[](PT a, PT b){ return a.y < b.y; });
vector<PT> buf;
for(int i=l; i<r; i++){
if(fabs(v[i].x - v[m].x) < d){
for(int j=(int)buf.size()-1; j>=0 && v[i].y - buf[j].y < d; --j)
d = min(d, dist(v[i], buf[j]));
buf.push_back(v[i]);
}
}
return d;
};
return rec(0, v.size());
}
