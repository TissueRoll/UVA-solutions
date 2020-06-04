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

double cowcow (double a, double b, double c) {
	return (a/(a+b))*((a-c-1)/(a-c-1+b));
}

double carcow (double a, double b, double c) {
	return (b/(a+b))*((a-c)/(a-c+b-1));
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// freopen("input.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	
	cout.precision(5); cout << fixed;

	int ncows, ncars, nshow;

	while (cin >> ncows >> ncars >> nshow) {
		cout << 1.0 - cowcow(ncows,ncars,nshow) - carcow(ncows,ncars,nshow) << endl;
	}

	return 0;
}