#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const ll LMAX = (1LL<<61);
const int IMAX = (1<<29);
const int BIG = 104206970;
const int PRIME = 104206969;

const int N = 1e5+1;

bitset<N> is; // #include <bitset>
ll pr[N], primes = 0;
void sieve() {
	is[2] = true; pr[primes++] = 2;
	for (int i = 3; i < N; i += 2) 
		is[i] = 1;
	for (int i = 3; i*i < N; i += 2)
		if (is[i])
			for (int j = i*i; j < N; j += i)
				is[j]= 0;
	for (int i = 3; i < N; i += 2)
		if (is[i])
			pr[primes++] = i;
}

ll mod(ll x, ll m) {
	if (m == 0) 
		return 0;
	if (m < 0)
		m *= -1;
	return (x%m + m) % m;
}

ll ext(ll a, ll b, ll& x, ll& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll g = ext(b, a%b, x, y);
	ll z = x - a/b*y;
	x = y;
	y = z;
	return g;
}

ll modinv(ll a, ll m) {
	ll x, y;
	ll g = ext(a,m, x, y);
	if (g == 1 or g == -1)
		return mod(x*g,m);
	return 0;
}

ll modpow (ll a, ll b, ll m) {
	if (b == 1)
		return a;
	ll c = modpow(a,b/2,m);
	c = (c*c)%m;
	return (b&1LL ? (c*a)%m : c);
}

ll n, e, c;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	// cout.precision(2); cout << fixed;
	// sieve();
	while (cin >> n >> e >> c) {
		ll phi = n;
		// for (int i = 1; i < primes; i++)
		// 	for (int j = i; j < primes and pr[i]*pr[j] <= n; j++)
		// 		if (n%pr[i] == 0 and n%pr[j] == 0)
		// 			phi = (pr[i]-1)*(pr[j]-1);
		for (ll i = 3; i*i <= n; i+=2)
			if (n%i == 0)
				phi = (i-1)*(n/i-1);
		ll d = modinv(e,phi);
		cout << modpow(c,d,n) << endl;
	}


	return 0;
}