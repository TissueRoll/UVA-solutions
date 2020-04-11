#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const int N = 200001;

struct edge {
	int u, v, w;
	edge(int _u = -1, int _v = -1, int _w = -1): u(_u), v(_v), w(_w) {}
	bool operator<(const edge& o) const {
		return w > o.w;
	}
	bool operator==(const edge& o) const {
		return ((u == o.u or u == o.v) and (v == o.v or v == o.u) and w == o.w);
	}
};

int T, n, m;
vector<edge> adj[N];
bool vis[N];
priority_queue<edge> pq;

void dfs (int u, const edge& tr) {
	vis[u] = 1;
	for (edge e : adj[u]) {
		if (not vis[e.v] and (not (tr == e))) {
			dfs(e.v, tr);
		}
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> T;
	while (T--) {
		cin >> n >> m;

		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			vis[i] = 0;
		}
		while (not pq.empty()) {
			pq.pop();
		}

		for (int i = 0; i < m; i++) {
			int u, v, w; cin >> u >> v >> w;
			adj[u].push_back(edge(u,v,w));
			adj[v].push_back(edge(v,u,w));
		}
		vector<edge> res;
		int tot = 0;
		pq.push(edge(1,1,0));
		while (not pq.empty()) {
			edge ce = pq.top(); pq.pop();
			if (vis[ce.v]) 
				continue;
			tot += ce.w;
			if (not (ce.u == 1 and ce.v == 1 and ce.w == 0))
				res.push_back(ce);
			vis[ce.v] = 1;
			for (edge e : adj[ce.v]) {
				if (e.v == ce.v)
					continue;
				if (vis[e.v])
					continue;
				pq.push(e);
			}
		}
		cout << tot << ' ';

		tot = INT_MAX;
		for (int i = 0; i < res.size(); i++) {
			edge to_remove = res[i];
			memset(vis, 0, sizeof vis);
			dfs(1, to_remove);
			bool ok = 1;
			for (int i = 1; i <= n; i++) {
				if (not vis[i]) {
					ok = 0;
					break;
				}
			}
			if (not ok)
				continue;
			memset(vis, 0, sizeof vis);
			int running = 0;
			pq.push(edge(1,1,0));
			while (not pq.empty()) {
				edge ce = pq.top(); pq.pop();
				if (vis[ce.v]) 
					continue;
				running += ce.w;
				vis[ce.v] = 1;
				for (edge e : adj[ce.v]) {
					if (e.v == ce.v)
						continue;
					if (vis[e.v])
						continue;
					if (to_remove == e)
						continue;
					pq.push(e);
				}
			}
			tot = min(tot, running);
		}
		cout << tot << endl;
	}
	return 0;
}