#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;
typedef long double ldob;
typedef pair<int,int> ii;
typedef vector<int> vi;

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

const int N = 2005;
const int NN = 1000007;
const int MOD = 998244353; // 1e9+7;
const int IMAX = 1e9+7;
const ll IAMAX = (1LL << 32);
const ll LLMAX = (1LL << 60);

ll n, Q, d, m, dp[205][25][15], v[205];

void reset() {
	memset(dp, -1, sizeof dp);
}

ll solve (int pos, int x, int c) {
	
	if (c == m)
		if (x == 0)
			return 1;
		else
			return 0;

	if (pos == n)
		if (c == m)
			if (x == 0)
				return 1;
			else
				return 0;
		else
			return 0;

	ll &ans = dp[pos][x][c];
	if (ans != -1) 
		return ans;
	ans = 0;
	
	ans += solve(pos+1, (x+v[pos]+IAMAX*d)%d, c+1)+solve(pos+1, x, c);

	return ans;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed;

	int T = 1;
	while (cin >> n >> Q) {
		if (n == 0 and Q == 0) break;
		for (int i = 0; i < n; ++i) {
			cin >> v[i];
		}
		cout << "SET " << T++ << ":\n";
		for (int q = 1; q <= Q; ++q) {
			cout << "QUERY " << q << ": ";
			reset();
			cin >> d >> m;
			cout << solve(0,0,0) << endl;
		}
	}

	return 0;
}