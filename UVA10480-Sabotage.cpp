#include <bits/stdc++.h>
using namespace std;

#define meme(x,y) memset(x, y, sizeof x)

#ifdef _DEBUG
#define debug_text(...) printf(__VA_ARGS__)
#else
#define debug_text(...) /* --- NOTHING --- */
#endif

const int MAX_N = 55;
const int INF = 0x3f3f3f3f;

int n, m, s, t;
set<int> adj[MAX_N];
int f[MAX_N][MAX_N], c[MAX_N][MAX_N], p[MAX_N];

bool bfs() {
	queue<int> q({s});
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : adj[u]) {
			if (p[v] == -1 && c[u][v] - f[u][v] > 0) {
				p[v] = u; // v came from u
				q.push(v); // push v into queue
			}
		}
	}
	return p[t] != -1;
}

bool find_augmenting_path() {
	meme(p,-1);
	p[s] = 0;
	return bfs();
}

void get_cut() { // call this only when no more augmenting path
	meme(p,-1);
	p[s] = 0;
	queue<int> q({s});
	while (!q.empty()) {
		int u = q.front(); q.pop();
		debug_text("Current node: %d\n", u);
		for (int v : adj[u]) {
			debug_text("Checking node: %d\n", v);
			if (p[v] == -1) {
				debug_text("%d is unvisited\n", v);
				debug_text("Flow from (%d,%d) = %d\n", u, v, f[u][v]);
				debug_text("Capacity from (%d,%d) = %d\n", u, v, c[u][v]);
				debug_text("Backward flow from (%d,%d) = %d\n", v, u, f[v][u]);
				if (c[u][v] - f[u][v] == 0) {
					debug_text("This is a cut edge (%d,%d)\n\n", u, v);
					// cout << u << ' ' << v << endl;
				} else {
					debug_text("%d is pushed into queue\n\n", v);
					p[v] = u;
					q.push(v);
				}
			}
		}
	}
	for (int u = 1; u <= n; u++) {
		if (p[u] != -1) {
			for (int v : adj[u]) {
				if (p[v] == -1 && c[u][v] - f[u][v] == 0) cout << u << ' ' << v << endl;
			}
		}
	}
}

int main () {
	int uu, vv, cap, mf;
	s = 1; t = 2;
	while (cin>>n>>m) {
		if (n==0 && m==0) break;
		mf = 0;
		meme(c,0);
		meme(f,0);
		for (int i = 0; i < m; i++) {
			cin >> uu >> vv >> cap;
			c[uu][vv] += cap;
			c[vv][uu] += cap;
			adj[uu].insert(vv);
			adj[vv].insert(uu);
		}
		while (find_augmenting_path()) {
			int b = INF;
			for (int v = t, u = p[v]; v != s; v = u, u = p[v]) b = min(b, c[u][v]-f[u][v]);
			for (int v = t, u = p[v]; v != s; v = u, u = p[v]) f[u][v] += b, f[v][u] -= b;
			mf += b;
		}
		get_cut();
		cout << endl;
		for (int i = 0; i <= n; i++) adj[i].clear();
	}
	
	return 0;
}