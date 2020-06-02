#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 301;
const ll MOD = 1000000000;

string s;
ll dp[N][N];

// Check the chosen substring if it's valid, then treat the rest as a separate problem

ll solve (int l, int r) {
	if (l == r)
		return 1;
	ll& ans = dp[l][r];
	if (ans != -1)
		return ans;
	if (s[l] != s[r])
		return 0;
	ans = 0;
	for (int i = l+2; i <= r; ++i) {
		if (s[l] == s[i])
			ans = (ans + solve(l+1,i-1)*solve(i,r))%MOD; 
	}
	return ans;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	while (cin >> s) {
		memset(dp, -1, sizeof dp);
		cout << solve(0,s.size()-1) << endl;
	}
	return 0;
}