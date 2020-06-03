#include <bits/stdc++.h>
using namespace std;

#define x() real()
#define y() imag()

typedef long long ll;
typedef pair<int,int> ii;
typedef pair<ii,int> iii;
typedef complex<double> pt;

const int N = 20001;
const int IMAX = (1 << 30);
const ll LLMAX = (1LL << 60);
const ll MOD = 1000000000;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// freopen("input.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	ll a, b;
	ll tc = 1;
	while (cin >> a >> b) {
		if (a == 0 and b == 0)
			break;
		cout << "Case " << tc++ << ": " << (a*(a-1LL)/2LL)*(b*(b-1LL)/2LL) << endl;
	}

	return 0;
}