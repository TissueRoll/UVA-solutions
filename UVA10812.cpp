#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1000005;
const ll MOD = 2000000011;

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

ll modpow(ll a, ll b, ll m) {
	if (b <= 0)
		return 1;
	ll c = modpow(a,b/2,m);
	c = (c*c)%m;
	return (b%2 == 0 ? c : (a*c)%m);
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// sieve();
	ll T, s, d;
	cin >> T;
	while (T--) {
		cin >> s >> d;
		ll a = (s+d)/2;
		if (s < d or abs(a-(s-a)) != d) {
			cout << "impossible" << endl;
		} else {
			cout << a << ' ' << s-a << endl;
		}
	}
	return 0;
}
