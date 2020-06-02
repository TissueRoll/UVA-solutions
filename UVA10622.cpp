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

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	ll x;
	while (cin >> x) {
		if (x == 0) break;
		bool neg = x < 0;
		x = abs(x);
		ll p = 1;
		for (ll b = 2; b*b <= x; ++b) {
			ll tmp = x, nums = 0;
			while (tmp%b == 0) {
				nums++;
				tmp /= b;
			}
			if (tmp == 1) {
				if (not neg or (neg and nums&1LL)) {
					p = max(p, nums);
				}
			}
		}
		cout << p << endl;
	}
	
	return 0;
}