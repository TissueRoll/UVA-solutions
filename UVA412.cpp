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

ll modpow(ll a, ll b, ll m) {
	if (b == 0)
		return 1LL;
	ll c = modpow(a,b/2LL,m);
	c = (c*c)%m;
	return (b%2LL == 0 ? c : (a*c)%m);
}

int n, in[N];

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cout.precision(6); cout << fixed;
	// sieve();
	while (cin >> n) {
		if (n == 0)
			break;
		for (int i = 0; i < n; ++i)
			cin >> in[i];
		int rel_pr = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				if (__gcd(in[i],in[j]) == 1) {
					rel_pr++;
				}
			}
		}
		if (rel_pr == 0) {
			cout << "No estimate for this data set." << endl;
		} else {
			cout << sqrt(double(6*n*(n-1)/2)/double(rel_pr)) << endl;
		}
	}
	return 0;
}
