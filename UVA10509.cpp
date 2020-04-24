#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e6+1;
const ll MOD = 2000000011;
const long double EPS = 1e-9;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cout.precision(4);
	cout << fixed;
	long double n;
	while (cin >> n) {
		if (n == 0)
			break;
		long double a = floor(pow(n,1/3.0)+EPS);
		long double dx = (n-a*a*a)/3.0/a/a;
		cout << a+dx << endl;
	}
	return 0;
}
