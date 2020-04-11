#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const ll LMAX = (1LL<<61);
const int IMAX = (1<<29);
const int BIG = 104206970;
const int PRIME = 104206969;

const int N = 1001;

int n, dist[N], weight[N];
bool vis[N];
vector<int> adj[N];

bool dfs(int u) {
	if (u == n)
		return true;
	vis[u] = 1;
	for (int& v : adj[u]) {
		if ((not vis[v]) and dfs(v))
			return true;
	}
	return false;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	// cout.precision(2); cout << fixed;
	while (1) {
		memset(vis, 0, sizeof vis);
		cin >> n;
		if (n == -1)
			break;

		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			dist[i] = -IMAX;
			int m; cin >> weight[i] >> m;
			for (int j = 0; j < m; j++) {
				int v; cin >> v;
				adj[i].push_back(v);
			}
		}

		dist[1] = 100;

		for (int i = 0; i < n-1; i++) {
			for (int u = 1; u <= n; u++) {
				for (int& v : adj[u]) {
					if (dist[u] > 0)
						dist[v] = max(dist[v], dist[u] + weight[v]);
				}
			}
		}

		bool ok = 0;
		for (int u = 1; u <= n; u++) {
			for (int& v : adj[u]) {
				if (dist[u] > 0)
					ok |= ((dist[v] < dist[u] + weight[v]) and dfs(u));
			}
		}

		if (dist[n] > 0 or ok) {
			cout << "winnable" << endl;
		} else {
			cout << "hopeless" << endl;
		}

	}

	return 0;
}