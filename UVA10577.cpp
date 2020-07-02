#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef complex<double> point; // 2D point only
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldob;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ii, int> ii_i;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<iii> viii;

#define re real()
#define im imag()
#define fi first
#define se second

// OST
template <typename T>
using ordered_set = __gnu_pbds::tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// from: https://codeforces.com/blog/entry/62393
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

const int INF = ~(1<<31);
const ll LINF = (1LL << 60);
const long double EPS = 1e-9;
const long double PI = acos(-1);

const int N = 1000001;
const int NN = 1001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

template <typename T>
struct vector3D {
	T x, y, z;
	vector3D<T>(T _x = 0, T _y = 0, T _z = 0): x(_x), y(_y), z(_z) {}
	vector3D<T> operator+(const vector3D& rhs) const {
		return vector3D<T>(x+rhs.x,y+rhs.y,z+rhs.z);
	}
	vector3D<T> operator-(const vector3D& rhs) const {
		return vector3D<T>(x-rhs.x,y-rhs.y,z-rhs.z);
	}
	vector3D<T> operator*(const T& r) const {
		return vector3D<T>(x*r,y*r,z*r);
	}
	vector3D<T> operator/(const T& r) const {
		return vector3D<T>(x/r,y/r,z/r);
	}
	T operator*(const vector3D<T>& rhs) const {
		return x*rhs.x+y*rhs.y+z*rhs.z;
	}
	vector3D<T> operator%(const vector3D<T>& rhs) const {
		return vector3D<T>(y*rhs.z-rhs.y*z, z*rhs.x-rhs.z*x, x*rhs.y-rhs.x*y);
	}
	bool operator==(const vector3D<T>& rhs) const {
		return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
	}
	bool operator!=(const vector3D<T>& rhs) const {
		return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
	}
	bool operator<(const vector3D<T>& rhs) const {
		if (x != rhs.x) return x < rhs.x;
		if (y != rhs.y) return y < rhs.y;
		return z < rhs.z;
	}
};

template <typename T>
struct vector2D {
	T x, y;
	vector2D<T>(T _x = 0, T _y = 0): x(_x), y(_y) {}
	vector2D<T> operator+(const vector2D& rhs) const {
		return vector2D<T>(x+rhs.x,y+rhs.y);
	}
	vector2D<T> operator-(const vector2D& rhs) const {
		return vector2D<T>(x-rhs.x,y-rhs.y);
	}
	vector2D<T> operator*(const T& r) const {
		return vector2D<T>(x*r,y*r);
	}
	vector2D<T> operator/(const T& r) const {
		return vector2D<T>(x/r,y/r);
	}
	T operator*(const vector2D<T>& rhs) const {
		return x*rhs.x+y*rhs.y;
	}
	T operator%(const vector2D<T>& rhs) const {
		return x*rhs.y-rhs.x*y;
	}
	bool operator==(const vector2D<T>& rhs) const {
		return (x == rhs.x) and (y == rhs.y);
	}
	bool operator!=(const vector2D<T>& rhs) const {
		return (x != rhs.x) or (y != rhs.y);
	}
	bool operator<(const vector2D<T>& rhs) const {
		if (x != rhs.x) return x < rhs.x;
		return y < rhs.y;
	}
	vector2D<T> perp() {
		return vector2D<T>(y,-x);
	}
};

template <typename T>
istream& operator>>(istream& i, vector2D<T>& v) {
	i >> v.x >> v.y;
	return i;
}

template <typename T>
ostream& operator<<(ostream& o, const vector2D<T>& v) {
	o << '(' << v.x << ',' << v.y << ')';
	return o;
}

template <typename T>
istream& operator>>(istream& i, vector3D<T>& v) {
	i >> v.x >> v.y;
	return i;
}

template <typename T>
ostream& operator<<(ostream& o, const vector3D<T>& v) {
	o << v.x << ' ' << v.y << ' ' << v.z;
	return o;
}

int convex2D_tests(const vector<vector2D<double>>& points, bool pt = 0, vector2D<double> ref = vector2D<double>()) {
	int n = points.size(), t = -2, dir = -2;
	if (n < 3)
		return -2;
	double res = 0;
	bool zr = 0;
	for (int i = 0; i < n; ++i) {
		res = (pt ? 
			(points[i]-ref)%(points[(i+1)%n]-ref) : 
			(points[i]-points[(i-1+n)%n])%(points[(i+1)%n]-points[i]));
		t = (res > 0 ? 1 : (res < 0 ? -1 : 0));
		dir = (i == 0 ? t : (t == 0 ? dir : (dir == 0 ? t : (dir == t ? dir : -2))));
		if (pt)
			zr = (zr ? 1 : (t == 0));
	}
	return (not pt ? dir : (not zr ? dir : (dir != -2 ? 0 : -2)));
}

double area2D(const vector<vector2D<double>>& points) {
	int n = points.size();
	if (n < 3)
		return 0;
	double ans = 0;
	for (int i = 0, j = n-1; i < n; j = i++)
		ans += points[i]%points[j];
	return abs(ans)/2.0;
}

double perimeter2D(const vector<vector2D<double>>& points) {
	int n = points.size();
	if (n < 2)
		return 0;
	if (n == 2)
		return sqrt((points[1]-points[0])*(points[1]-points[0]));
	double ans = 0;
	for (int i = 1; i <= n; ++i)
		ans += sqrt((points[i%n]-points[i-1])*(points[i%n]-points[i-1]));
	return ans;
}

vector<vector2D<double>> convex_hull(vector<vector2D<double>> pts) {
	sort(pts.begin(), pts.end());
	int top = 0;
	vector<vector2D<double>> stk(2*pts.size());
	for (int i = 0; i < pts.size(); ++i) {
		while (top >= 2 and (stk[top-1]-stk[top-2])%(pts[i]-stk[top-2]) <= 0) top--;
		stk[top++] = pts[i];
	}
	for (int i = pts.size()-2, t = top+1; i >= 0; --i) {
		while (top >= t and (stk[top-1]-stk[top-2])%(pts[i]-stk[top-2]) <= 0) top--;
		stk[top++] = pts[i];
	}
	stk.resize(top-1);
	return stk;
}

vector2D<double> rotate(const vector2D<double>& pt, double rad) {
	return vector2D<double>(pt.x*cos(rad)-pt.y*sin(rad), pt.x*sin(rad)+pt.y*cos(rad));
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cout.precision(3); cout << fixed;

	int T = 1, n;
	while (cin >> n) {
		if (n == 0)
			break;
		vector2D<double> tA, tB, tC;
		cin >> tA >> tB >> tC;
		
		vector3D<double> mAB((tA.x+tB.x)/2.0,(tA.y+tB.y)/2.0,1), mAC((tA.x+tC.x)/2.0,(tA.y+tC.y)/2.0,1);
		vector3D<double> v0(tA.y-tB.y,tB.x-tA.x,0), v1(tA.y-tC.y,tC.x-tA.x,0);

		vector3D<double> L1 = mAB%v0, L2 = mAC%v1;
		vector3D<double> intersection = L1%L2;
		vector2D<double> O(intersection.x/intersection.z, intersection.y/intersection.z);

		vector2D<double> v = tA-O;

		double deg = 2.0*PI/n, minx = tA.x, maxx = tA.x, miny = tA.y, maxy = tA.y;
		for (int i = 0; i <= n; ++i) {
			vector2D<double> tmp = O + rotate(v, deg*i);
			minx = min(minx, tmp.x);
			maxx = max(maxx, tmp.x);
			miny = min(miny, tmp.y);
			maxy = max(maxy, tmp.y);
		}
		cout << "Polygon " << T++ << ": " << (maxx-minx)*(maxy-miny) << '\n';
	}

	return 0;
}