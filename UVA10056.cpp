#include <bits/stdc++.h>
using namespace std;

#define x() real()
#define y() imag()

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ii,int> iii;
typedef complex<double> pt;

const int N = 1e6+7;
const int IMAX = (1 << 30);
const ll LLMAX = (1LL << 60);
const ll MOD = 1000000000;
const double EPS = 1e-9;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// freopen("input.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	
	cout.precision(4); cout << fixed;

	int T; cin >> T;
	while (T--) {
		int n, idx; double p; cin >> n >> p >> idx;
		double running = p, nloss = 1.0;
		for (int i = 1; i <= n; ++i) {
			if (i < idx) running *= 1.0-p;
			nloss *= 1.0-p;
		}

		double ans = 0;

		while (running > EPS) {
			ans += running;
			running *= nloss;
		}

		cout << ans << endl;
	}

	return 0;
}