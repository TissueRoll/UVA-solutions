#include <bits/stdc++.h>
using namespace std;

#ifdef _DEBUG
#define debug_text(...) printf(__VA_ARGS__)
#else
#define debug_text(...) /*** NOTHING ***/
#endif

typedef pair<int,int> pii;

const int N = 205;

int T = 0, n, m, a;
vector<int> adj[N];
int vis[N];
bool answer;

bool color(int u, int p) {
	queue<pii> q; q.push({u,-1});
	while (not q.empty()) {
		pii u = q.front(); q.pop();
		if (u.second == -1) vis[u.first] = 1;
		else vis[u.first] = (vis[u.second] == 1 ? 2 : 1);
		debug_text("Current node: %d color %d\n", u.first, vis[u.first]);
		for (int v : adj[u.first]) {
			if (vis[v] == vis[u.first]) return false;
			else if (vis[v] > 0) continue;
			else q.push({v,u.first});
		}
	}
	return true;
}

int main () {
	cin >> T;
	while (T--) {
		a = 0;
		answer = 1;
		memset(vis, 0, sizeof vis);
		cin >> n >> m;
		for (int i = 0; i < m; i++) {
			int u, v; cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		
		for (int i = 0; i < n; i++) {
			if (vis[i] == 0) {
				answer &= color(i,-1);
				if (answer) {
					int l = 0, r = 0;
					for (int j = 0; j < n; j++) {
						if (vis[j] == 1) l++;
						else if (vis[j] == 2) r++;
						if (vis[j] > 0) vis[j] += 2;
					}
					debug_text("number of 1's: %d\nnumber of 2's: %d\n", l, r);
					a += (min(l,r) == 0 ? max(l,r) : min(l,r));
				}
			}
		}

		cout << (answer ? a : -1) << endl;

		for (int i = 0; i < n; i++) adj[i].clear();
	}
	return 0;
}