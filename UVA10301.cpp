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

#define x() real()
#define y() imag()
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

const int N = 31;
const int NN = 1001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

struct union_find {
  vi p; union_find(int n) : p(n, -1) { }
  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  bool unite(int x, int y) {
    int xp = find(x), yp = find(y);
    if (xp == yp)       return false;
    if (p[xp] > p[yp])  std::swap(xp,yp);
    p[xp] += p[yp], p[yp] = xp;
    return true;
  }
  int size(int x) { return -p[find(x)]; }
};


double dist (pair<double,double> a, pair<double,double> b) {
	return sqrt((b.fi-a.fi)*(b.fi-a.fi) + (b.se-a.se)*(b.se-a.se));
}

int n;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed;

	while (cin >> n) {
		if (n == -1)
			break;
		vector<pair<pair<double,double>,double>> v(n);
		vector<int> collide(n, 0);
		union_find uf(n);
		for (int i = 0; i < n; ++i)
			cin >> v[i].fi.fi >> v[i].fi.se >> v[i].se;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == j) continue;
				double d = dist(v[i].fi, v[j].fi);
				if (max(v[i].se,v[j].se)-min(v[i].se,v[j].se) <= d and d <= v[i].se+v[j].se) {
					uf.unite(i,j);
					// collide[i]++;
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < n; ++i)
			ans = max(ans, uf.size(i));
		cout << "The largest component contains " << ans << (ans == 1 ? " ring.\n" : " rings.\n");
	}

	return 0;
}