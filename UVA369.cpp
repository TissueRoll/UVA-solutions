#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 20;

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

ll n, m;
ll pascal[101][101];

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// sieve();
	pascal[0][0] = pascal[0][1] = pascal[0][1] = 1;
	for (int i = 1; i < 101; ++i) {
		pascal[i][0] = pascal[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			pascal[i][j] = pascal[i-1][j-1]+pascal[i-1][j];
		}
	}
	while (cin >> n >> m) {
		if (n == 0 and m == 0)
			break;
		cout << n << " things taken " << m << " at a time is " << pascal[n][m] << " exactly." << endl;
	}
	return 0;
}
