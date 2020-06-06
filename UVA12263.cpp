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

const int N = 501;
const int NN = 1000001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const ll LLMAX = (1LL << 60);

const int dx[] = {-1,-1,0,1,1,1,0,-1};
const int dy[] = {0,1,1,1,0,-1,-1,-1};

int n, m, vi[N], vis[N];
bool cycle;
set<int> adj[N];
stack<int> ans;

void dfs (int u) {
	// cout << u << endl;
	vis[u] = 1;
	for (int v : adj[u]) {
		if (vis[v] == 0) {
			dfs(v);
		} else if (vis[v] == 1) {
			cycle = 1;
		}
		if (cycle)
			return;
	}
	vis[u] = 2;
	ans.push(u);
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed; 

	int T; cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> vi[i];
		}

		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				adj[vi[i]].insert(vi[j]);
			}
		}

		cin >> m;

		for (int i = 0; i < m; ++i) {
			int a, b; cin >> a >> b;
			if (adj[a].count(b)) {
				adj[a].erase(b);
				adj[b].insert(a);
			} else {
				adj[b].erase(a);
				adj[a].insert(b);
			}
		}

		// for (int i = 0; i < n; ++i) {
		// 	cout << vi[i] << endl;
		// 	for (int v : adj[vi[i]])
		// 		cout << v << ' ';
		// 	cout << endl;
		// }

		cycle = 0;
		for (int i = 0; i < n and not cycle; ++i) {
			if (vis[vi[i]] == 0) {
				dfs(vi[i]);
			}
		}

		if (cycle) {
			cout << "IMPOSSIBLE" << endl;
		} else {
			while (not ans.empty()) {
				cout << ans.top() << (ans.size() == 1 ? '\n' : ' ');
				ans.pop();
			}
		}

		memset(vis, 0, sizeof vis);
		for (int i = 0; i <= n; ++i)
			adj[i].clear();
		while (not ans.empty())
			ans.pop();
	}

	return 0;
}