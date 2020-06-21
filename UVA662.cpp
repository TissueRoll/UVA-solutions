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

int n, k, v[201], dp[31][201], path[201][201], ps[201][201];

void print_ans (int wh, int r) {
	if (wh == 1) {
		if (wh == r)
			cout << "Depot " << wh << " at restaurant " << wh+(r-wh)/2 << " serves restaurant " << r << endl;	
		else
			cout << "Depot " << wh << " at restaurant " << wh+(r-wh)/2 << " serves restaurants " << wh << " to " << r << endl;
	} else {
		for (int l = wh; l <= r; ++l) {
			if (dp[wh][r] == dp[wh-1][l-1] + ps[l][r]) {
				print_ans(wh-1, l-1);
				if (l == r)
					cout << "Depot " << wh << " at restaurant " << l+(r-l)/2 << " serves restaurant " << r << endl;	
				else
					cout << "Depot " << wh << " at restaurant " << l+(r-l)/2 << " serves restaurants " << l << " to " << r << endl;
				break;
			}
		}
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed;

	int T = 1;
	while (cin >> n >> k) {
		if (n == 0 and k == 0)
			break;
		for (int i = 0; i <= k; ++i)
			for (int j = 0; j <= n; ++j)
				dp[i][j] = dp[i][j] = IMAX;
		for (int i = 1; i <= n; ++i) {
			cin >> v[i];
		}

		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				int tmp = 0, m = i + (j-i)/2;
				for (int kk = i; kk <= j; ++kk) {
					tmp += abs(v[kk]-v[m]);
				}
				ps[i][j] = tmp;
			}
		}

		for (int i = 1; i <= n; ++i)
			dp[1][i] = ps[1][i];

		// choosing the cutoff for some segment
		for (int wh = 2; wh <= k; ++wh) {
			for (int r = wh; r <= n; ++r) {
				for (int l = wh; l <= r; ++l) {
					dp[wh][r] = min(dp[wh][r], dp[wh-1][l-1] + ps[l][r]);
				}
			}
		}

		cout << "Chain " << T++ << endl;
		print_ans(k, n);
		cout << "Total distance sum = " << dp[k][n] << endl << endl;
	}

	return 0;
}