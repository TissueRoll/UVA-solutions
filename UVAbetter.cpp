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

int prevprime[N];

void bf_solve(int n) {
	if (n < 8) {
		cout << "Impossible." << endl;
	   return;	
	}
	bool ok = 0;
	for (int i = 3; i > -1; --i) {
		cout << prevprime[n-2*i] << (i == 0 ? '\n' : ' ');
		n -= prevprime[n-2*i];
	}	
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	sieve();
	prevprime[0] = prevprime[1] = -1;
	int prevp = 2;
	for (int i = 2; i < N; ++i) {
		if (is[i]) {
			prevprime[i] = i;
			prevp = i;
		} else {
			prevprime[i] = prevp;
		}
	}
			
	int n;
	while (cin >> n) {
		bf_solve(n);
	}
	return 0;
}
