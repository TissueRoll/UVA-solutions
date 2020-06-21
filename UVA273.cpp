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

const int N = 20;
const int NN = 1001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

ll n, m, mat[N][N];

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

double norm(vector2D<double> x) {
	return sqrt(x*x);
}

int ccw (vector2D<double> a, vector2D<double> b, vector2D<double> c) {
	vector2D<double> u = b-a, v = c-a;
	if (u%v > EPS) return 1;
	if (u%v < -EPS) return -1;
	if (u.x*v.x < -EPS or u.y*v.y < -EPS) return -1;
	if (norm(u) < norm(v)-EPS) return 1;
	return 0;
}

bool ssint (vector2D<double> A, vector2D<double> B, vector2D<double> C, vector2D<double> D) {
	// vector2D<double> u = B-A, v = D-C;
	bool Asame = (A == B), Csame = (C == D);
	if (Asame and Csame) return A == C;
	if (Asame) return ccw(C,D,A) == 0;
	if (Csame) return ccw(A,B,C) == 0;
	return ccw(A,B,C)*ccw(A,B,D) <= 0 and ccw(C,D,A)*ccw(C,D,B) <= 0;
	// return sign((B-A)%(C-A)) != sign((B-A)%(D-A)) and sign((D-C)%(A-C)) != sign((D-C)%(B-C));
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cout.precision(3); cout << fixed;
	
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> n;
		vector<pair<vector2D<double>,vector2D<double>>> in(n);
		for (int i = 0; i < n; ++i) {
			cin >> in[i].fi >> in[i].se;
		}
		
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				mat[i][j] = LINF;
			}
		}
		
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == j) mat[i][j] = 0;
				else mat[i][j] = ssint(in[i].fi, in[i].se, in[j].fi, in[j].se) ? 1 : LINF;
			}
		}

		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					if (mat[i][k] + mat[k][j] < mat[i][j])
						mat[i][j] = mat[i][k] + mat[k][j];
					// mat[i][j] += mat[i][k]*mat[k][j];
				}
			}
		}

		if (t > 0) cout << endl;
		int u, v;
		while (cin >> u >> v) {
			if (u == 0 and v == 0)
				break;
			u--; v--;
			if (mat[u][v] != LINF) cout << "CONNECTED\n";
			else cout << "NOT CONNECTED\n";
		}
		
	}

	return 0;
}