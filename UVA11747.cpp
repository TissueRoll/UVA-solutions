// UVA11747

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

int n, m;
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
	while (1) {
		cin >> n >> m;
		if (n == 0 and m == 0)
			break;
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			vis[i] = 0;
		}

		for (int i = 0; i < m; i++) {
			int u, v, w; cin >> u >> v >> w;
			adj[u].push_back(edge(u,v,w));
			adj[v].push_back(edge(v,u,w));
		}
		vector<edge> res;
		for (int i = 0; i < n; i++) {
			if (vis[i])
				continue;
			pq.push(edge(i,i,0));
			while (not pq.empty()) {
				edge ce = pq.top(); pq.pop();
				if (vis[ce.v]) 
					continue;
				if (not (ce.u == 0 and ce.v == 0 and ce.w == 0))
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
		}
		vector<edge> ans;
		for (int i = 0; i < n; i++) {
			for (edge e : adj[i]) {
				bool ok = 1;
				for (edge x : res)
					if (x == e)
						ok = 0;
				for (edge x : ans)
					if (x == e)
						ok = 0;
				if (ok)
					ans.push_back(e);
			}
		}
		sort(ans.begin(), ans.end(), [](const edge& a, const edge& b) {
			return a.w < b.w;
		});
		if (ans.empty()) {
			cout << "forest" << endl;
		} else {
			for (int i = 0; i < ans.size(); i++)
				cout << ans[i].w << (i+1 == ans.size() ? "\n" : " ");
		}
	}
	return 0;
}