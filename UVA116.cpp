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

const int N = 10000001;
const int NN = 1001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

ll n, m, grid[11][111], dp[11][111], path[11][111];

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed;

	while (cin >> n >> m) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> grid[i][j];
				dp[i][j] = (j != m-1 ? LINF : grid[i][j]);
			}
		}

		for (int c = m-2; c >= 0; --c) {
			for (int r = 0; r < n; ++r) {
				ll tmp = LINF;
				for (int i = -1; i <= 1; ++i) {
					int nx = (r+i+n)%n;
					if (dp[nx][c+1] < tmp or (dp[nx][c+1] == tmp and nx < path[r][c])) {
						tmp = dp[nx][c+1];
						path[r][c] = nx;
					}
				}
				// if (dp[(r-1+n)%n][c+1] > dp[r][c] + grid[(r-1+n)%n][c+1]) {
				// 	dp[(r-1+n)%n][c+1] = dp[r][c] + grid[(r-1+n)%n][c+1];
				// 	path[(r-1+n)%n][c+1] = r*m+c;
				// }
				// if (dp[r][c+1] > dp[r][c] + grid[r][c+1]) {
				// 	dp[r][c+1] = dp[r][c] + grid[r][c+1];
				// 	path[r][c+1] = r*m+c;
				// }
				// if (dp[(r+1)%n][c+1] > dp[r][c] + grid[(r+1)%n][c+1]) {
				// 	dp[(r+1)%n][c+1] = dp[r][c] + grid[(r+1)%n][c+1];
				// 	path[(r+1)%n][c+1] = r*m+c;
				// }
				dp[r][c] = grid[r][c]+tmp;
			}
		}

		// for (int i = 0; i < n; ++i) {
		// 	for (int j = 0; j < m; ++j) {
		// 		cout << path[i][j] << ' ';
		// 	}
		// 	cout << endl;
		// }

		ll mn = LINF;
		ll s = 0;
		for (int i = 0; i < n; ++i) {
			if (mn > dp[i][0]) {
				mn = dp[i][0];
				s = i;
			}
		}

		cout << s+1;
		for (int i = 0; i < m-1; ++i) {
			s = path[s][i];
			cout << " " << s+1;
		}
		cout << endl << mn << endl;
	}

	return 0;
}