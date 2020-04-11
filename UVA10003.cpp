#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const int N = 55;
const ll MAX = (1LL<<61);

int s, n, a[N], dp[N][N];

int solve (int l, int r) {
	if (dp[l][r] != INT_MAX) {
		return dp[l][r]; 
	}

	dp[l][r] = 0;
	for (int i = l+1; i < r; i++) {
		if (dp[l][r] == 0) {
			dp[l][r] = solve(l,i) + solve(i,r) + a[r] - a[l];
		} else {
			dp[l][r] = min(dp[l][r], solve(l,i) + solve(i,r) + a[r] - a[l]);
		}
	}
	return dp[l][r];
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	while (1) {
		cin >> s;
		if (s == 0) {
			break;
		}
		cin >> n;
		a[0] = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for (int i = 0; i < n+2; i++) {
			for (int j = 0; j < n+2; j++) {
				dp[i][j] = INT_MAX;
			}
		}
		a[n+1] = s;
		cout << "The minimum cutting is " << solve(0,n+1) << "." << endl;
	}
	return 0;
}