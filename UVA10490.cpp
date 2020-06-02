#include <bits/stdc++.h>
using namespace std;

#define x() real()
#define y() imag()

typedef long long ll;
typedef complex<double> pt;

const int N = 1001;
const int IMAX = (1 << 30);
const ll LLMAX = (1LL << 60);
const ll MOD = 1000000000;

ll pow2[60];

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	pow2[0] = 1;
	for (int i = 1; i < 60; ++i) {
		pow2[i] = pow2[i-1]*2LL;
	}
	ll n;
	while (cin >> n) {
		if (n == 0) break;
		bool is_prime = 1;
		for (ll i = 2; i*i <= n and is_prime; ++i) {
			is_prime &= not (n%i == 0);
		}
		if (is_prime) {
			ll p = pow2[n-1]*(pow2[n]-1);
			ll factors = 0, tmp = p;
			for (ll i = 2; i*i <= tmp; ++i) {
				while (tmp%i == 0) {
					factors++;
					tmp /= i;
				}
			}
			factors += (tmp != 1 ? 1 : 0);
			if (factors == n) {
				cout << "Perfect: " << p << "!\n";
			} else {
				cout << "Given number is prime. But, NO perfect number is available.\n";
			}
		} else {
			cout << "Given number is NOT prime! NO perfect number is available.\n";
		}
	}
	
	return 0;
}