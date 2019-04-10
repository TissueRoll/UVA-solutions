#include <bits/stdc++.h>
using namespace std;

#ifdef _DEBUG
#define debug_text(...) printf(__VA_ARGS__)
#else
#define debug_text(...) /*** NOTHING ***/
#endif

typedef pair<int,int> pii;

const int N = 205;

string out_text[2] = {"NOT BICOLORABLE.", "BICOLORABLE."};

int n, l;
vector<int> adj[N];
int vis[N];
bool answer;

bool color(int u, int p) {
	queue<pii> q; q.push({0,-1});
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
	while (cin >> n) {
		if (n == 0) break;
		answer = 1;
		memset(vis, 0, sizeof vis);
		cin >> l;
		for (int i = 0; i < l; i++) {
			int u, v; cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		
		for (int i = 0; i < n; i++) {
			if (vis[i] == 0) answer &= color(i,-1);
		}

		cout << out_text[answer] << endl;

		for (int i = 0; i < n; i++) adj[i].clear();
	}
	return 0;
}