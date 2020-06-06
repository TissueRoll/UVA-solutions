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

int m, w, c;
ldob pascal[N][N];

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cout.precision(7); cout << fixed; 

	pascal[0][1] = 0;
	for (int i = 0; i < N; ++i)
		pascal[i][0] = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j <= i; ++j) {
			pascal[i][j] = pascal[i-1][j-1]+pascal[i-1][j];
		}
	}

	while (true) {
		cin >> m >> w >> c;
		if (m == 0 and w == 0) break;
		ldob pm = ldob(m)/ldob(m+w);
		ldob pw = 1.0-pm;
		ldob ans = 0;
		for (int cc = 0; cc <= c; cc += 2) {
			ans += pascal[c][cc]*pow(pm,cc)*pow(pw,c-cc);
		}
		cout << ans << endl;
	}
	

	return 0;
}