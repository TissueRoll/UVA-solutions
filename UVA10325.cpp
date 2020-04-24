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

ll n, m, nums[N];
map<ll,ll> mp;

void try_all(int pos, ll cur, int count) {
	if (pos == m) {
		mp[count] += n/cur;
	} else {
		try_all(pos+1, cur, count); // don't include
		try_all(pos+1, lcm(cur,nums[pos]), count+1); // include
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// sieve();
	while (cin >> n >> m) {
		for (int i = 0; i < m; ++i) {
			cin >> nums[i];
		}
		try_all(0,1,0);

		ll ans = 0;
		for (int i = 0; i <= m; ++i) {
			ans += (i%2 == 0 ? mp[i] : -mp[i]);
		}
		cout << ans << endl;
		mp.clear();
	}
	return 0;
}
