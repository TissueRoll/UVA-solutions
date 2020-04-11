#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const int N = 5001;

ll n, m;

map<ll,ll> prime_factorize (ll x) {
	map<ll,ll> ans;
	while (x%2 == 0) {
		ans[2]++;
		x /= 2;
	}
	for (ll i = 3; i*i <= x; i += 2) {
		while (x%i == 0) {
			ans[i]++;
			x /= i;
		}
	}
	if (x > 2)
		ans[x]++;
	return ans;
}

ll pows(ll x, ll p) {
	ll ans = 0;
	for (ll i = p; i <= x; i *= p)
		ans += x/i;
	return ans;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	// cout.precision(1); cout << fixed;
	while (cin >> n >> m) {
		if (n >= m) {
			cout << m << " divides " << n << "!\n";
		} else {
			// actual shit
			bool ok = 1;
			map<ll,ll> factorized = prime_factorize(m);
			for (auto x : factorized) 
				if (pows(n, x.first) < x.second)
					ok = 0;
			if (ok) {
				cout << m << " divides " << n << "!\n";
			} else {
				cout << m << " does not divide " << n << "!\n";
			}
		}
	}
	return 0;
}