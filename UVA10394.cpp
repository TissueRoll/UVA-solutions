#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 20000001;

bitset<N> is;
// int pr[N], primes = 0;
void sieve() {
	is[2] = true; 	
	for (int i = 3; i < N; i += 2)
		is[i] = 1;
	for (int i = 3; i*i < N; i += 2)
		if (is[i])
			for (int j = i*i; j < N; j += i)
				is[j] = 0;
	/*
	pr[primes++] = 2;
	for (int i = 3; i < N; i += 2)
		if (is[i])
			pr[primes++] = i;
	*/
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	sieve();
	vector<pair<int,int>> v(100000);
	int validnums = 0;
	for (int i = 3; i < N-2 and validnums < 100000; i += 2) {
		if (is[i] and is[i+2]) {
			v[validnums++] = {i,i+2};
		}
	}
	int n;
	while (cin >> n) {
		cout << "(" << v[n-1].first << ", " << v[n-1].second << ")\n";
	}
	return 0;
}
