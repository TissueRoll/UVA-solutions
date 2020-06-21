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

const int N = 31;
const int NN = 1001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int n, h, f[N], d[N], t[N], dp[N][20*12][20*12], stayed[N];

int solve (int lake, int rt, int tt) {
	if (lake > n)
		return 0;
	int &ans = dp[lake][rt][tt];
	if (ans != -1)
		return ans;
	int stay = 0, move = 0;
	if (rt > 0) {
		int fishe = max(0, f[lake] - tt*d[lake]);
		stay = solve(lake, rt-1, tt+1) + fishe;
	}
	if (rt >= t[lake]) {
		move = solve(lake+1, rt-t[lake], 0);
	}
	ans = max(stay, move);
	return ans;
}

void get_path(int lake, int rt, int tt) {
	if (lake > n)
		return;
	int stay = -1, move = -1;
	if (rt > 0) {
		int fishe = max(0, f[lake] - tt*d[lake]);
		stay = solve(lake, rt-1, tt+1) + fishe;
	}
	if (rt >= t[lake]) {
		move = solve(lake+1, rt-t[lake], 0);
	}

	int ans = solve(lake, rt, tt);
	if (ans == stay) {
		stayed[lake]++;
		get_path(lake, rt-1, tt+1);
	} else if (move != -1) {
		get_path(lake+1, rt-t[lake], 0);
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed;

	int T = 1;
	while (cin >> n >> h) {
		if (n == 0 and h == 0)
			break;
		h *= 12;
		memset(dp, -1, sizeof dp);
		memset(stayed, 0, sizeof stayed);
		memset(t, 0, sizeof t);
		for (int i = 1; i <= n; ++i)
			cin >> f[i];
		for (int i = 1; i <= n; ++i)
			cin >> d[i];
		for (int i = 1; i < n; ++i) {
			cin >> t[i];
		}

		int ans = solve(1,h,0);
		get_path(1,h,0);
		if (T++ > 1) cout << endl;
		for (int i = 1; i <= n; ++i) {
			cout << 5*stayed[i] << (i == n ? "\n" : ", ");
		}
		cout << "Number of fish expected: " << ans << endl;
	}

	return 0;
}