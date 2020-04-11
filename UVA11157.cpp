#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const int N = 55;

int T, ans, n, d;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cin >> n >> d;

		bool small[n+1], vis[n+1];
		int rock[n+1];
		for (int i = 0; i < n; i++) {
			char s, trash; int x; cin >> s >> trash >> rock[i];
			small[i] = (s=='S');
			vis[i] = 0;
		}
		rock[n] = d;
		small[n] = 0;
		vis[n] = 0;

		ans = rock[0]; // it doesnt make sense to choose something farther, regardless if its small or not

		for (int i = 0; i < n; i++) {
			vis[i] = 1;
			if (not small[i+1]) { // skip as much small rocks as you can
				ans = max(ans, rock[i+1]-rock[i]);
			} else {
				ans = max(ans, (i+2 > n ? rock[n] : rock[i+2])-rock[i]);
				i++;
			}
		}

		for (int i = n; i > 0; i--) { // just go back, choosing the nearest possible rock
			if ((not vis[i-1]) or (not small[i-1])) {
				ans = max(ans, rock[i]-rock[i-1]);
			} else {
				ans = max(ans,rock[i]-(i-2 < 0 ? 0 : rock[i-2]));
				i--;
			}
		}

		cout << "Case " << t << ": " << ans << endl;
	}
	return 0;
}