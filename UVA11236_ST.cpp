#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;
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

const int N = 100001;
const int NN = 1000001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const ll LLMAX = (1LL << 60);

int n, q, v[N], st[2*N], f[N], L[N], R[N], cmprs;
map<int,int> mapping;

void build() {
	for (int i = n-1; i > 0; --i) {
		st[i] = max(st[i<<1],st[i<<1|1]);
	}
}

int query(int l, int r) {
	int ans = 0;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) ans = max(ans, st[l++]);
		if (r&1) ans = max(ans, st[--r]);
	}
	return ans;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);

	while (cin >> n) {
		if (n == 0) break;
		
		memset(st, 0, sizeof st);
		memset(f, 0, sizeof f);
		memset(L, -1, sizeof L);
		memset(R, -1, sizeof R);
		mapping.clear();

		cmprs = 1;
		cin >> q;
		for (int i = 1; i <= n; ++i) {
			cin >> v[i];
			if (mapping.count(v[i]) == 0) {
				mapping[v[i]] = cmprs++;
			}
			v[i] = mapping[v[i]];
			f[v[i]]++;
		}

		for (int i = 1; i <= n; ++i) {
			if (L[v[i]] == -1)
				L[v[i]] = i;
			R[v[i]] = i;
			st[n+i-1] = f[v[i]];
		}

		build();

		for (int i = 0; i < q; ++i) {
			int l, r; cin >> l >> r;
			if (v[l] == v[r]) {
				cout << r-l+1 << endl;
			} else if (v[l] != v[l-1] and v[r] != v[r+1]) {
				cout << query(l-1,r) << endl;
			} else if (v[l] == v[l-1] and v[r] != v[r+1]) {
				// cout << "yoink: " << l << ' ' << r << endl;
				// cout << ":: " << R[v[l]]-l+1 << ' ' << query(R[v[l]], r) << endl;
				cout << max(R[v[l]]-l+1, query(R[v[l]], r)) << endl;
			} else if (v[l] != v[l-1] and v[r] == v[r+1]) {
				cout << max(query(l-1,L[v[r]]-1),r-L[v[r]]+1) << endl;
			} else if (v[l] == v[l-1] and v[r] == v[r+1]) {
				cout << max({R[v[l]]-l+1,query(R[v[l]],L[v[r]]-1),r-L[v[r]]+1}) << endl;
			}
		}

	}	

	return 0;
}