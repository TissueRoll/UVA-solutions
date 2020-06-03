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
	ll k;
	while (cin >> k) {
		vector<ii> ans;
		for (ll x = k+1; x <= 2*k; ++x) {
			ll y = k*x/(x-k);
			if (x*y/(x+y) == k) {
				ans.push_back({y,x});
			}
		}
		sort(ans.begin(), ans.end());
		cout << ans.size() << endl;
		for (int i = ans.size()-1; i >= 0; --i) {
			cout << "1/" << k << " = 1/" << ans[i].first << " + 1/" << ans[i].second << endl;
		}
	}

	return 0;
}