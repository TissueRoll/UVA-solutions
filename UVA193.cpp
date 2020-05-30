#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 105;
const int IMAX = 1e9+7;

vector<int> adj[N], ans;
int vis[N], best;
int m, n, k;

void splat(int u, int black, int white) {
	
	// if last node
	if (black+white == n or u == n+1) {
		if (black > best) {
			ans.clear();
			best = black;
			for (int i = 1; i <= n; ++i) {
				if (vis[i] == 1)
					ans.push_back(i);
			}
		}
		return;
	}

	bool ok = (vis[u] != 2 ? 1 : 0);
	for (int v : adj[u]) {
		if (vis[v] == 1) {
			ok = 0;
		}
	}

	if (ok) {
		vis[u] = 1;
		for (int v : adj[u])
			vis[v] = 2;
		splat(u+1,black+1,white+adj[u].size());
		vis[u] = 0;
		for (int v : adj[u])
			vis[v] = 0;
	}
	
	splat(u+1,black,white+(vis[u] == 2 ? 1 : 0));
}

int main () {
	cin >> m;
	while (m--) {
		best = 0;
		cin >> n >> k;
		for (int i = 1; i <= n; ++i)
			adj[i].clear();
		for (int i = 0; i < k; ++i) {
			int u, v; cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		splat(1,0,0);
		cout << ans.size() << endl;
		for (int i = 0; i < ans.size(); ++i) {
			cout << ans[i] << (i+1 == ans.size() ? '\n' : ' ');
		}
	}
	return 0;
}
