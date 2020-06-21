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
		return vector2D<T>(x*r,y*r);
	}
	T operator*(const vector2D<T>& rhs) const {
		return x*rhs.x+y*rhs.y;
	}
	T operator%(const vector2D<T>& rhs) const {
		return x*rhs.y-rhs.x*y;
	}
};

int sign (int x) {
	if (x > 0) return 1;
	if (x == 0) return 0;
	return -1;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed;

	int T; cin >> T;
	for (int t = 1; t <= T; ++t) {
		int n; cin >> n;
		vector<pair<vector2D<int>,vector2D<int>>> v;
		for (int i = 0; i < n; ++i) {
			int x0, y0, x1, y1; cin >> x0 >> y0 >> x1 >> y1;
			v.push_back({vector2D<int>(x0,y0),vector2D<int>(x1,y1)});
		}

		int ans = n;
		vector2D<int> A, B, C, D;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				A = v[i].first;
				B = v[i].second;
				C = v[j].first;
				D = v[j].second;
				if (i != j and sign((B-A)%(C-A)) != sign((B-A)%(D-A)) and sign((D-C)%(A-C)) != sign((D-C)%(B-C))) {
					ans++;
				} 
			}
		}
		if (t > 1) cout << endl;
		cout << ans << endl;
	}
	

	return 0;
}