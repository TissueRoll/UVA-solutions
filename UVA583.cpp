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
	ll g;
	while (cin >> g) {
		if (g == 0) break;
		cout << g << " = ";
		bool first = 1;
		if (g < 0) {
			cout << -1;
			g = -g;
			first = 0;
		}
		for (ll i = 2; i*i <= g; ++i) {
			while (g%i == 0) {
				if (not first)
					cout << " x " << i;
				else {
					cout << i;
					first = 0;
				}
				g /= i;
			}
		}
		if (g > 1) {
			if (not first)
				cout << " x " << g;
			else 
				cout << g;
		}
		cout << endl;
	}
	
	return 0;
}