#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 500001;
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

map<ll,int> vis;
set<ll> dead;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// sieve();
	ll n, a, b;
	while (cin >> n) {
		if (n == 0)
			break;
		cin >> a >> b;
		ll cur = b%n;
		while (vis[cur] < 2) {
			vis[cur]++;
			if (vis[cur] == 2)
				dead.insert(cur);
			cur = (((a*((cur*cur)%n))%n)+b)%n;
		}
		cout << n - dead.size() << endl;
		vis.clear();
		dead.clear();
	}
	return 0;
}
