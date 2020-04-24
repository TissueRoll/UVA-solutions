#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 55;

bitset<N> is;
int pr[N], primes = 0;
void sieve() {
	is[2] = true; 	
	for (int i = 3; i < N; i += 2)
		is[i] = 1;
	for (int i = 3; i*i < N; i += 2)
		if (is[i])
			for (int j = i*i; j < N; j += i)
				is[j] = 0;

	pr[primes++] = 2;
	for (int i = 3; i < N; i += 2)
		if (is[i])
			pr[primes++] = i;
	// */
}

ll lcm (ll a, ll b) {
	return a*b/__gcd(a,b);
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// sieve();
	ll n, t, a[N], x;
	ll ans0 = 0, ans1 = 0;
	while (cin >> n >> t) {
		if (n == 0 and t == 0)
			break;
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		while (t--) {
			cin >> x;
			ans0 = 0; ans1 = 1e12+69;
			for (int i = 0; i < n; ++i) {
				for (int j = i+1; j < n; ++j) {
					for (int k = j+1; k < n; ++k) {
						for (int l = k+1; l < n; ++l) {
							ll common = lcm(a[i], lcm(a[j], lcm(a[k], a[l])));
							ll close = x/common*common;
							ans0 = max(ans0, close);
							ans1 = min(ans1, close + (x > close ? common : 0));
						}
					}
				}
			}
			cout << ans0 << ' ' << ans1 << endl;
		}
	}
	return 0;
}
