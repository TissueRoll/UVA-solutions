#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 10000005;

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

void bf_solve(int n) {
	if (n < 2) {
		cout << "Impossible." << endl;
	   return;	
	}
	bool ok = 0;
	if (n%2 == 1) {
		for (int i = 1; i < primes and not ok and pr[i] <= n; ++i) {
			for (int j = 1; j < primes and not ok and pr[j] <= n; ++j) {
				if (n-2-pr[i]-pr[j] >= 0 and is[n-2-pr[i]-pr[j]]) {
					cout << 2 << ' ' << pr[i] << ' ' << pr[j] << ' ' << n-2-pr[i]-pr[j] << endl;
					ok = 1;
				} else if (n-2-2-pr[j] >= 0 and is[n-2-2-pr[j]]) {
					cout << 2 << ' ' << 2 << ' ' << pr[j] << ' ' << n-2-2-pr[j] << endl;
					ok = 1;
				}
			}
		}
	} else {
		for (int i = 0; i < primes and not ok and pr[i] <= n; ++i) {
			for (int j = 0; j < primes and not ok and pr[j] <= n; ++j) {
				for (int k = 0; k < primes and not ok and pr[k] <= n; ++k) {
					if (n-pr[i]-pr[j]-pr[k] >= 0 and is[n-pr[i]-pr[j]-pr[k]]) {
						cout << pr[i] << ' ' << pr[j] << ' ' << pr[k] << ' ' << n-pr[i]-pr[j]-pr[k] << endl;
						ok = 1;
					}
				}
			}
		}
	}
	if (not ok) {
		cout << "Impossible." << endl;
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	sieve();
	int n;
	while (cin >> n) {
		bf_solve(n);
	}
	return 0;
}
