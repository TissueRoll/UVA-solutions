#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;
typedef long double ldob;
typedef pair<int,int> ii;

#define f() first
#define s() second

// OST
template <typename T>
using ordered_set = __gnu_pbds::tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

const int N = 10000001;
const int NN = 101;
const int MOD = 1e9+7;
const int IMAX = 2e9+7;
const ll LLMAX = (1LL << 60);

const int dx[] = {-1,-1,0,1,1,1,0,-1};
const int dy[] = {0,1,1,1,0,-1,-1,-1};

ll solve(ll a, ll b) {
	if (b == 0)
		return 0; // stop
	if (a/b > 1)
		return 1; // checkmate
	return 1+solve(b,a-b);
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed; 

	ll a, b;

	while (cin >> a >> b) {
		if (a == 0 and b == 0)
			break;
		if (a < b)
			swap(a,b);
		if (solve(a,b)&1)
			cout << "Stan wins" << endl;
		else
			cout << "Ollie wins" << endl;
	}

	return 0;
}