#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;
typedef long double ldob;
typedef pair<int,int> ii;

// OST
template <typename T>
using ordered_set = __gnu_pbds::tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// ordered_set<int> t; t.insert(...);
// t.find_by_order(index); // 0-based
// t.order_of_key(key); --> STRICTLY LESS THAN KEY

// from: https://codeforces.com/blog/entry/62393
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

const int N = 101;
const int NN = 1000001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const ll LLMAX = (1LL << 60);

int T, n, r;
ldob pascal[N][N], p[N], ans[N];

void pregen () {
	pascal[0][1] = 0;
	for (int i = 0; i < N; ++i)
		pascal[i][0] = 1;
	for (int i = 1; i < N; ++i)
		for (int j = 1; j <= i; ++j)
			pascal[i][j] = pascal[i-1][j-1]+pascal[i-1][j];
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cout.precision(7); cout << fixed; 

	// pregen();

	T = 1;
	while (true) {
		cin >> n >> r;
		if (n == 0 and r == 0) break;
		for (int i = 0; i < n; ++i) {
			cin >> p[i];
			ans[i] = 0.0; // probability of this element as part of the r chosen elements
		}
		ldob not_chosen = 0.0; // probability of choosing r elements
		for (int i = 0; i < (1<<n); ++i) {
			if (__builtin_popcount(i) != r) continue;
			ldob tmp = 1.0; // probability of this specific configuration
			for (int j = 0; j < n; ++j) {
				if (i&(1<<j)) {
					tmp *= p[j];
				} else {
					tmp *= (1-p[j]);
				}
			}

			not_chosen += tmp;
			for (int j = 0; j < n; ++j) {
				if (i&(1<<j)) {
					ans[j] += tmp; 
				}
			}
		}
		cout << "Case " << T++ << ":\n";
		for (int i = 0; i < n; ++i) {
			cout << ans[i]/not_chosen << endl;
		}
	}
	
	

	return 0;
}