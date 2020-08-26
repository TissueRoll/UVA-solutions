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
template <typename T = int>
using lim = numeric_limits<T>;

#define re real()
#define im imag()
#define fi first
#define se second
#define sz(v) (v).size()
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()

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

const int N = 105;
const int NN = 35;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const ll LMAX = 1e15+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};
const int dx8[8] = {-1,-1,-1,0,0,1,1,1};
const int dy8[8] = {-1,0,1,-1,1,-1,0,1};

struct segtree {
  int n;
  int *vals;
  segtree(vector<int> &ar, int n) {
    this->n = n;
    vals = new int[2*n];
    for (int i = 0; i < n; ++i)
      vals[i+n] = ar[i];
    for (int i = n-1; i > 0; --i)
      vals[i] = min(vals[i<<1], vals[i<<1|1]);
  }
  void update(int i, int v) {
    for (vals[i += n] = v; i >>= 1;)
      vals[i] = min(vals[i<<1],vals[i<<1|1]);
  }
  int query(int l, int r) {
    int resL = INF, resR = INF;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l&1)  resL = min(resL,vals[l++]);
      if (r&1)  resR = min(resR,vals[--r]);
    }
    return min(resL,resR);
  }
};

vector<int> get_input(string s, string &command) {
	command = s.substr(0,5);
	string _s = s.substr(6);
	// cout << _s << endl;
	vector<int> vals;
	int tmp = 0;
	for (char c : _s) {
		if (isdigit(c)) {
			(tmp *= 10) += c-'0';
		} else {
			vals.push_back(tmp-1);
			tmp = 0;
		}
	}
	return vals;
}

int n, q;

void solution() {
	vector<int> a(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	segtree st(a, n);
	string s, command;
	while (q--) {
		cin >> s;
		vector<int> vals = get_input(s, command);
		if (command == "shift") {
			vector<pair<int,int>> orig(sz(vals));
			for (int i = 0; i < sz(vals); ++i) {
				orig[(i-1+sz(vals))%sz(vals)] = {vals[(i-1+sz(vals))%sz(vals)],st.vals[n+vals[i]]};
			}
			for (int i = 0; i < sz(orig); ++i) {
				st.update(orig[i].fi, orig[i].se);
			}
		} else {
			cout << st.query(vals[0], vals[1]+1) << endl;
		}
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0); // cout.tie(0);
	// cout.precision(2); cout << fixed;

	int T = 1;
	// cin >> T;
	while (cin >> n >> q) {
		solution();
	}

	return 0;
}