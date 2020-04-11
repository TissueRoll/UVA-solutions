#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const ll LMAX = (1LL<<61);
const int IMAX = (1<<29);
const int BIG = 104206970;
const int PRIME = 104206969;

const int N = 251;
const ll MOD = 1e9+7;

int a[N], pf[N], dp[N][N];

int solve (int l, int r) {
	if (r < l)
		return 0;
	if (l == r)
		return 0;
	if (dp[l][r] != -1)
		return dp[l][r];
	dp[l][r] = IMAX;
	for (int i = l; i <= r; i++) {
		dp[l][r] = min(dp[l][r], solve(l,i-1)+solve(i+1,r)+pf[r]-pf[l-1]-a[i]);
	}
	return dp[l][r];
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	// cout.precision(9); cout << fixed;
	int n;
	while (cin >> n) {
		pf[0] = a[0] = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			pf[i] = pf[i-1]+a[i];
		}

		memset(dp, -1, sizeof dp);

		cout << solve(1,n) << endl;
	}

	return 0;
}
