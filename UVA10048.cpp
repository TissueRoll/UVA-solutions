#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const ll MAX = (1LL<<61);

const int N = 1000;

struct edge {
	int u, v; ll w;
	edge(int _u = -1, int _v = -1, int _w = -1): u(_u), v(_v), w(_w) {}
	bool operator<(const edge& rhs) const {
		return w > rhs.w;
	}
	friend ostream& operator<<(ostream& o, const edge& e) {
		return o << '(' << e.u << ',' << e.v << ',' << e.w << ')';
	}
};

ll shortest_path (int s, int t, int sz, vector<vector<edge>>& adj) {
	ll dist[sz]; bool vis[sz]; int p[sz];
	for (int i = 0; i < sz; i++) {
		dist[i] = MAX;
		vis[i] = 0;
		p[i] = -1;
	}
	priority_queue<edge> pq;
	dist[s] = 0;
	pq.push(edge(s,s,0));
	while (not pq.empty()) {
		int u = pq.top().v; pq.pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		for (edge& e : adj[u]) {
			if (not vis[e.v] and (dist[e.v] > max(dist[u],e.w) or dist[e.v] == MAX)) {
				dist[e.v] = max(dist[u], e.w);
				p[e.v] = u;
				pq.push(edge(e.u,e.v,dist[e.v]));
			}
		}
	}

	return dist[t];
}

int n, m, q;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	// cout.precision(2); cout << fixed;
	int counter = 1;
	while (1) {
		cin >> n >> m >> q;
		if (n == 0 and m == 0 and q == 0)
			break;
		if (counter > 1)
			cout << endl;
		n++;
		vector<vector<edge>> adj(n);
		for (int i = 0; i < m; i++) {
			int u, v, w; cin >> u >> v >> w;
			adj[u].push_back(edge(u,v,w));
			adj[v].push_back(edge(v,u,w));
		}

		cout << "Case #" << counter << endl;
		counter++;
		for (int i = 0; i < q; i++) {
			int u, v; cin >> u >> v;
			ll ans = shortest_path(u, v, n, adj);
			if (ans == MAX)
				cout << "no path" << endl;
			else
				cout << ans << endl;
		}
	}

	return 0;
}