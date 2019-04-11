#include <bits/stdc++.h>
using namespace std;

#ifdef _DEBUG
#define debug_text(...) printf(__VA_ARGS__)
#else
#define debug_text(...) /*** NOTHING ***/
#endif

typedef pair<int,int> pii;

const int N = 305;

int n;
vector<int> adj[N];
int vis[N];
bool answer;

bool color(int a, int p) {
	queue<pii> q; q.push(pii(a,-1));
	while (not q.empty()) {
		pii u = q.front(); q.pop();
		if (u.second == -1) vis[u.first] = 1;
		else vis[u.first] = (vis[u.second] == 1 ? 2 : 1);
		debug_text("Current node: %d color %d\n", u.first, vis[u.first]);
		for (int v : adj[u.first]) {
            if (v == u.second) continue;
			if (vis[v] == vis[u.first]) return false;
			else if (vis[v] > 0) continue;
			else q.push(pii(v,u.first));
		}
	}
	return true;
}

int main () {
	while (cin >> n) {
		if (n == 0) break;
		memset(vis, 0, sizeof vis);
		int u, v;
		while (cin >> u >> v) {
			if (u == 0 and v == 0) break;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		
        answer = color(1,-1);

		cout << (answer ? "YES" : "NO") << endl;

		for (int i = 0; i <= n; i++) adj[i].clear();
	}
	return 0;
}
