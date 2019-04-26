#include <bits/stdc++.h>
using namespace std;

const int N = 30;
const int M = (1<<3)-1;
// dp contains how many times this can occur
long long dp[N+3][M+1]; // level, config

int main () {
	dp[2][7] = 1;
	dp[2][1] = 1;
	dp[2][4] = 1;
	for (int level = 2; level <= N; level++) {
		for (int configuration = 0; configuration <= M; configuration++) {
			if (configuration == 2 || configuration == 5) continue;
			if (dp[level][configuration] <= 0) continue;
			int bit_count = __builtin_popcount(configuration);
			if (bit_count == 0) {
				dp[level+1][7] += dp[level][configuration];
				dp[level+1][1] += dp[level][configuration];
				dp[level+1][4] += dp[level][configuration];
			} else if (bit_count == 1) {
				dp[level][7] += dp[level][configuration];
				dp[level+1][configuration^M] += dp[level][configuration];
			} else if (bit_count == 2) {
				dp[level+1][configuration^M] += dp[level][configuration];
			} else {
				dp[level+1][0] += dp[level][configuration];
			}
		}
	}
	int n;
	while (cin >> n) {
		if (n == -1) break;
		if (n == 0) cout << 1 << endl;
		else cout << dp[n][M] << endl;
	}
	return 0;
}