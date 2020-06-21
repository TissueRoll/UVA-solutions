#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef complex<double> point; // 2D point only
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldob;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef pair<ii, ll> ii_i;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<iii> viii;

#define x() real()
#define y() imag()

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

const int N = 1001;
const int NN = 1001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int n, dp[N][N], tmp;
string s, o;

int solve (int l, int r) {
	if (l >= r)
		return 0;
	int &ans = dp[l][r];
	if (ans != -1)
		return ans;
	if (s[l] == s[r]) ans = solve(l+1,r-1);
	else ans = 1+min(solve(l+1,r), solve(l,r-1));

	return ans;
}

void path (int l, int r) {
	if (l == r) {
		o += s[l]; tmp = 1;
	}
	if (l >= r)
		return;
	if (s[l] == s[r]) {
		o += s[l];
		path(l+1,r-1);
	} else if (solve(l,r) == 1+solve(l+1,r)) {
		o += s[l];
		path(l+1,r);
	} else if (solve(l,r) == 1+solve(l,r-1)) {
		o += s[r];
		path(l,r-1);
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed;

	while (cin >> s) {
		n = s.size();
		o = "";
		tmp = 0;
		memset(dp, -1, sizeof dp);
		int ans = solve(0,n-1);
		path(0,n-1);
		cout << ans << ' ' << o;
		reverse(o.begin(), o.end());
		cout << o.substr(tmp) << endl;

	}

	return 0;
}