#include <bits/stdc++.h>
using namespace std;

#define x() real()
#define y() imag()

typedef long long ll;
typedef complex<double> pt;

const int N = 100000;
const int IMAX = (1 << 30);
const ll LLMAX = (1LL << 60);
const ll MOD = 1000000000;

vector<ll> szs;

void pregen() {
	for (ll i = 1; i < N; i += 2) {
		szs.push_back(i*i);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	pregen();
	ll sz, p;
	while (cin >> sz >> p) {
		if (sz == 0 and p == 0)
			break;
		int mid = sz/2+1;
		int idx = int(lower_bound(szs.begin(), szs.end(), p)-szs.begin());
		int width = 2*idx;
		ll up = szs[idx];
		if (up == 1) {
			cout << "Line = " << mid << ", column = " << mid << ".\n";
		} else {
			int q = -1;
			for (int i = 1; i <= 4; ++i) {
				if (up-i*width < p and p <= up-(i-1)*width) {
					q = i;
				}
			}
			int pos = up-(q-1)*width-p;
			if (q == 1) {
				cout << "Line = " << mid+idx-pos << ", column = " << mid+idx << ".\n";
			} else if (q == 2) {
				cout << "Line = " << mid-idx << ", column = " << mid+idx-pos << ".\n";
			} else if (q == 3) {
				cout << "Line = " << mid-idx+pos << ", column = " << mid-idx << ".\n";
			} else if (q == 4) {
				cout << "Line = " << mid+idx << ", column = " << mid-idx+pos << ".\n";
			}
		}
		



	}
	
	return 0;
}