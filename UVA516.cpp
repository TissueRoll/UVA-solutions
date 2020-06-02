#include <bits/stdc++.h>
using namespace std;

#define x() real()
#define y() imag()

typedef long long ll;
typedef complex<double> pt;

const int N = 36767+1;
const int IMAX = (1 << 30);
const ll LLMAX = (1LL << 60);
const ll MOD = 1000000000;

bitset<N> is;
int pr[N], primes = 0;

void sieve () {
	is[2] = 1; pr[primes++] = 2;
	for (int i = 3; i < N; i += 2)
		is[i] = 1;
	for (int i = 3; i*i < N; i += 2)
		if (is[i])
			for (int j = i*i; j < N; j += i)
				is[j] = 0;
	for (int i = 3; i < N; i += 2)
		if (is[i])
			pr[primes++] = i;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	sieve();
	string line;
	while (getline(cin, line) and line != "0") {
		istringstream sin(line);
		ll p, v, x = 1;
		while (sin >> p >> v)
			x *= pow(p,v);
		x--;
		vector<int> ans;
		for (int i = primes-1; i >= 0; --i) {
			if (x%pr[i] == 0) {
				ans.push_back(pr[i]);
				ll nums = 0;
				while (x%pr[i] == 0) {
					nums++;
					x /= pr[i];
				}
				ans.push_back(nums);
			}
		}
		for (int i = 0; i < ans.size(); ++i) {
			cout << ans[i] << (i+1 == ans.size() ? '\n' : ' ');
		}
	}
	
	return 0;
}