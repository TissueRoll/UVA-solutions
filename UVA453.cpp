#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

template <typename T = double>
using point = complex<T>; // 2D point only

using ll = long long;
using ull = unsigned long long;
using ldob = long double;

template <typename T = int>
using ii = pair<T,T>;
template <typename T = int>
using iii = pair<T,ii<T>>;
template <typename T = int>
using ii_i = pair<ii<T>,T>;
template <typename T = int>
using vi = vector<T>;
template <typename T = int>
using vvi = vector<vi<T>>;
template <typename T = int>
using vii = vector<ii<T>>;
template <typename T = int>
using viii = vector<iii<T>>;

#define re real()
#define im imag()
#define fi first
#define se second

// OST
template <typename T>
using ordered_set = __gnu_pbds::tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// from: https://codeforces.com/blog/entry/62393
// struct custom_hash {
// 	static uint64_t splitmix64(uint64_t x) {
// 		// http://xorshift.di.unimi.it/splitmix64.c
// 		x += 0x9e3779b97f4a7c15;
// 		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
// 		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
// 		return x ^ (x >> 31);
// 	}

// 	size_t operator()(uint64_t x) const {
// 		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
// 		return splitmix64(x + FIXED_RANDOM);
// 	}
// };

const int INF = ~(1<<31);
const ll LINF = (1LL << 60);
const long double EPS = 1e-9;
const long double PI = acos(-1);

const int N = 1005;
const int NN = 1001;
const int MOD = 998244353;
const int IMAX = 1e9+7;
const ll LMAX = 1e15+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

template <typename T>
struct vector2D {
	T x, y;
	vector2D(T _x = 0, T _y = 0): x(_x), y(_y) {}
	vector2D& operator+=(const vector2D& rhs) { x += rhs.x; y += rhs.y; return *this; }
	vector2D& operator-=(const vector2D& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
	vector2D& operator*=(const T& rhs) { x *= rhs; y *= rhs; return *this; }
	vector2D& operator/=(const T& rhs) { x /= rhs; y /= rhs; return *this; }
	vector2D operator-() const { return vector2D(-x,-y); }
	vector2D operator+(const vector2D& rhs) const { return vector2D(*this) += rhs; }
	vector2D operator-(const vector2D& rhs) const { return vector2D(*this) -= rhs; }
	vector2D operator*(const T& rhs) const { return vector2D(*this) *= rhs; }
	vector2D operator/(const T& rhs) const { return vector2D(*this) /= rhs; }
	T operator*(const vector2D& rhs) const { return x*rhs.x+y*rhs.y; } // dot
	T operator%(const vector2D& rhs) const { return x*rhs.y-rhs.x*y; } // cross
	bool operator==(const vector2D& rhs) const { return abs(x-rhs.x) < EPS and abs(y-rhs.y) < EPS; }
	bool operator!=(const vector2D& rhs) const { return not (*this == rhs); }
	bool operator<(const vector2D& rhs) const { return x < rhs.x-EPS or (abs(x-rhs.x) < EPS and y < rhs.y-EPS); }
	vector2D perp() const { return vector2D(-y,x); }
	T angle() const {return atan2(y,x);}
	T squared_norm() const { return (*this)*(*this); }
	T norm() const {return sqrt(squared_norm()); }
	T scalar_project(const vector2D& v) const {return (*this)*v/v.norm();}
	vector2D vector_project(const vector2D& v) const {return v*(((*this)*v)/(v*v));}
	vector2D normalized() const {return *this/norm(); }
	vector2D rotate(const T& a) const {return vector2D(cos(a)*x-sin(a)*y,sin(a)*x+cos(a)*y); }
	friend vector2D operator*(const T& lhs, const vector2D& rhs) {return rhs*lhs; }
	friend ostream& operator<<(ostream& o, const vector2D& v) {return o << "(" << v.x << "," << v.y << ")"; }
	friend istream& operator>>(istream& i, vector2D& v) {return i >> v.x >> v.y;}
};

template <typename T = double>
using P = vector2D<T>;

template <typename T>
struct vector3D {
	T x, y, z;
	vector3D(T _x = 0, T _y = 0, T _z = 0): x(_x), y(_y), z(_z) {}
	vector3D(vector2D<T> xy, T _z = 1): x(xy.x), y(xy.y), z(_z) {}
	vector3D& operator+=(const vector3D& rhs) {x += rhs.x; y += rhs.y; z += rhs.z; return *this;}
	vector3D& operator-=(const vector3D& rhs) {x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this;}
	vector3D& operator*=(const T& rhs) {x *= rhs; y *= rhs; z *= rhs; return *this;}
	vector3D& operator/=(const T& rhs) {x /= rhs; y /= rhs; z /= rhs; return *this;}
	vector3D operator-() const {return vector3D(-x,-y,-z);}
	vector3D operator+(const vector3D& rhs) const { return vector3D(*this) += rhs; }
	vector3D operator-(const vector3D& rhs) const { return vector3D(*this) -= rhs; }
	vector3D operator*(const T& rhs) const { return vector3D(*this) *= rhs; }
	vector3D operator/(const T& rhs) const { return vector3D(*this) /= rhs; }
	T operator*(const vector3D& rhs) const { return x*rhs.x+y*rhs.y+z*rhs.z; }
	vector3D operator%(const vector3D& rhs) const { return vector3D(y*rhs.z-rhs.y*z, z*rhs.x-rhs.z*x, x*rhs.y-rhs.x*y); }
	bool operator==(const vector3D& rhs) const { return abs(x-rhs.x) < EPS and abs(y-rhs.y) < EPS and abs(z-rhs.z) < EPS; }
	bool operator!=(const vector3D& rhs) const { return not (*this == rhs); }
	bool operator<(const vector3D& rhs) const {
		if (abs(x-rhs.x) > EPS) return x < rhs.x;
		if (abs(y-rhs.y) > EPS) return y < rhs.y;
		return z < rhs.z;
	}
	T squared_norm() const {return (*this)*(*this);}
	T norm() const {return sqrt(squared_norm()); }
	T scalar_project(const vector3D& v) const {return (*this)*v/v.norm();}
	vector3D vector_project(const vector3D& v) const {return v*(((*this)*v)/(v*v));}
	vector3D normalized() const {return *this / norm();}
	friend vector3D operator*(const T& lhs, const vector3D& rhs) {return rhs*lhs;}
	friend ostream& operator<<(ostream& o, const vector3D& v) {return o << "(" << v.x << "," << v.y << "," << v.z << ")";}
	friend istream& operator>>(istream& i, vector3D& v) {return i >> v.x >> v.y >> v.z;}
};

template <typename T = double>
using V3 = vector3D<T>;

int sign (int x) {return x >= 0 ? x ? 1 : 0 : -1;}
int dcmp (double x, double y) {return abs(x-y) < EPS ? 0 : x > y ? 1 : -1;}

template <typename T = double>
T squared_dist(P<T> u, P<T> v) {return (v-u).squared_norm();}

template <typename T = double>
T dist(P<T> u, P<T> v) {return (v-u).norm();}

template <typename T = double>
T fixangle(T t) {return t > 1 ? 1 : t < -1 ? -1 : t;}

template <typename T>
struct line2D {
	P<T> p0, p1, v;
	V3<T> implicit;
	line2D(P<T> _p0 = P<T>(), P<T> _p1 = P<T>(), bool is_2pt = 1) {
		p0 = _p0;
		(is_2pt ? p1 : v) = _p1;
		(is_2pt ? v : p1) = (is_2pt ? _p0-_p1 : _p0+_p1);
		implicit = V3<T>(_p0,1)%V3<T>(_p1,is_2pt);
	}
	line2D(V3<T> u) {
		implicit = u;
		T d = -u.z/(u*u-u.z*u.z);
		p0 = P<T>(u.x*d, u.y*d);
		v = P<T>(u.y,-u.x);
		p1 = p0+v;
	}
	T turn(const P<T>& p) const {return v%(p-p0);}
	bool contains(const P<T>& p) const {return turn(p) == 0;}
	T dist(const P<T>& p) const {return implicit.normalized()*V3<T>(p,1);}
	T squared_dist(const P<T>& p) const {return dist(p)*dist(p);}
	line2D perp(const P<T>& p) const {return line2D(p, v.perp(), 0);}
	P<T> closest_to_origin() const {
		T f = implicit.z/(implicit*implicit-implicit.z*implicit.z); 
		return P<T>(-implicit.x*f,-implicit.y*f);
	}
	bool operator==(const line2D& rhs) const {return abs(v%rhs.v) < EPS and contains(rhs.p0);}
	bool operator!=(const line2D& rhs) const {return not (*this == rhs);}
	bool intersects(const line2D& rhs) const {return abs(v%rhs.v) > EPS or *this == rhs;}
	pair<bool,P<T>> intersection(const line2D& rhs) const {
		V3<T> res = implicit%rhs.implicit;
		return res.z == 0 ? make_pair(0,p0) : make_pair(1,P<T>(res.x/res.z,res.y/res.z));
	}
	friend ostream& operator<<(ostream& o, const line2D& l) {
		return o << "p0: " << l.p0 << "\np1: " << l.p1 << "\nv: " << l.v << "\nimplicit: " << l.implicit;
	}
};

template <typename T = double>
int CLintersection(const P<T>& c1, const double& r1,
	const line2D<T>& ln,
	P<T>& res1, P<T>& res2) {
	if (abs(ln.dist(c1)) > r1+EPS)
		return 0;
	if (abs(abs(ln.dist(c1))-r1) < EPS) {
		res1 = ln.p0+(c1-ln.p0).vector_project(ln.v);
		return 1;
	}
	P<T> near = ln.p0+(c1-ln.p0).vector_project(ln.v);
	T vd = (c1-near).squared_norm();
	T f = sqrt(r1*r1-vd);
	P<T> u = ln.v.normalized()*f;
	res1 = near+u;
	res2 = near-u;
	return 2;
}

double get_angle(double a, double b, double c) {
	double t = b*b+c*c-a*a;
	t /= (2*b*c);
	return acos(fixangle<double>(t));
}

// from https://github.com/MeGaCrazy/CompetitiveProgramming/blob/c099628e643065a7bae09af22c4cbce1216e4db9/UVA/UVA_453.cpp
// thank you for ending my suffering
template <typename T = double>
vector<P<T>> CCintersection2(const P<T>& c1, const double& r1,
	const P<T>& c2, const double& r2) {
	if (c1 == c2 and dcmp(r1,r2) == 0 and r1 > EPS)
		return vector<P<T>>();
	double a1 = (c2-c1).angle(), a2 = get_angle(r2,(c2-c1).norm(),r1);
	if (isnan(a2))
		a2 = 0;
	P<T> v(r1*cos(a1+a2),r1*sin(a1+a2));
	vector<P<T>> ret;
	ret.push_back(v+c1);
	if (dcmp(r1*r1,(ret[0]-c1).squared_norm()) != 0 or dcmp(r2*r2,(ret[0]-c2).squared_norm()) != 0)
		return vector<P<T>>(3,P<T>());
	v = P<T>(r1*cos(a1-a2),r1*sin(a1-a2));
	ret.push_back(v+c1);
	if (ret[0] == ret[1])
		ret.pop_back();
	return ret;
}

template <typename T = double>
int CCintersection (const P<T>& c1, const T& r1, 
	const P<T>& c2, const T& r2, 
	P<T>& res1, P<T>& res2) {

	// infinite intersections
	if (c1 == c2 and dcmp(r1,r2) == 0 and r1 > EPS)
		return 3;
	// same point, no intersections
	if (c1 == c2 and dcmp(r1,r2) != 0 and r1 > EPS)
		return 0;
	// same point, same redius, zero radius
	if (c1 == c2 and dcmp(r1,r2) == 0 and r1 < EPS) {
		res1 = c1;
		return 1;
	}
	// circles too far from each other
	if ((c2-c1).norm() < max(r1,r2)-min(r1,r2) or (c2-c1).norm() > max(r1,r2)+min(r1,r2))
		return 0;
	
	P<T> tc2 = c2-c1;
	V3<T> converted(-2*tc2.x,-2*tc2.y,tc2*tc2+r1*r1-r2*r2);
	line2D<T> ln(converted);
	int ans = CLintersection(P<T>(), r1, ln, res1, res2);
	res1 += c1;
	res2 += c1;
	return ans;
}

const P<double> fix(EPS,EPS);

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cout.precision(3); cout << fixed;

	P<double> c1, c2, res1, res2; double r1, r2;
	while (cin >> c1 >> r1 >> c2 >> r2) {
		vector<P<double>> ans = CCintersection2<double>(c1,r1,c2,r2);
		if (ans.size() == 0) {
			cout << "THE CIRCLES ARE THE SAME\n";
		} else if (ans.size() == 3) {
			cout << "NO INTERSECTION\n";
		} else {
			sort(ans.begin(), ans.end());
			for (auto p : ans)
				cout << p+fix;
			cout << '\n';
		}
		// res1 = res2 = P<double>();
		// int ans = CCintersection(c1,r1,c2,r2,res1,res2);
		// if (ans == 0) {
		// 	cout << "NO INTERSECTION\n";
		// } else if (ans == 1) {
		// 	cout << res1+fix << endl;
		// } else if (ans == 2) {
		// 	if (res2 < res1)
		// 		swap(res1,res2);
		// 	cout << res1+fix << res2+fix << endl;
		// } else {
		// 	cout << "THE CIRCLES ARE THE SAME\n";
		// }
	}

	return 0;
}