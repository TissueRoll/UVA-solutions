#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldob;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<iii> viii;

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

const int N = 50001;
const int NN = 1000007;
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
	bool operator==(const vector3D& rhs) const {
		return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
	}
	bool operator!=(const vector3D& rhs) const {
		return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
	}
	bool operator<(const vector3D& rhs) const {
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
	vector2D<T> perp() {
		return vector2D<T>(y,-x);
	}
};

// convert 2 pt or parametric to implicit
// p1 cross p2 or p1 cross v1
// remember points have z = 1 and vectors have z = 0

int sign (int x) {
	if (x > 0) return 1;
	if (x == 0) return 0;
	return -1;
}

// VECTORS ONLY
template <typename T>
T proj(const T& u, const T& v) {
	return v*((u*v)/(v*v));
}

// VECTORS ONLY
template <typename T>
T perp(const T& u, const T& v) {
	return u-proj(u,v);
}

template <typename T>
istream& operator>>(istream& i, vector2D<T>& v) {
	i >> v.x >> v.y;
	return i;
}

template <typename T>
ostream& operator<<(ostream& o, const vector2D<T>& v) {
	o << v.x << ' ' << v.y;
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

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cout.precision(9); cout << fixed;

	int T = 1, n;
	while (cin >> n) {
		double sqr = double(2*n-1)/2.0;
		sqr *= sqr;
		int partial = 0, full = 0;
		for (int i = -n; i < n; ++i) {
			for (int j = n; j > -n; --j) {
				int count = 0;
				count += double(i*i+j*j) <= sqr;
				count += double((i+1)*(i+1)+j*j) <= sqr;
				count += double(i*i+(j-1)*(j-1)) <= sqr;
				count += double((i+1)*(i+1)+(j-1)*(j-1)) <= sqr;
				if (0 < count and count < 4) partial++;
				if (count == 4) full++;
			}
		}
		if (T++ > 1) cout << endl;
		cout << "In the case n = " << n << ", " << partial << " cells contain segments of the circle.\n";
		cout << "There are " << full << " cells completely contained in the circle.\n";
	}

	return 0;
}