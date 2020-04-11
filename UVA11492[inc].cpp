#include <bits/stdc++.h>
using namespace std;

// UNSOLVED
// UNSOLVED
// UNSOLVED
// UNSOLVED
// UNSOLVED

typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const ll MAX = (1LL<<61);

const int N = 1000;

struct edge {
	int u, v; ll w; char c;
	edge(int _u = -1, int _v = -1, ll _w = -1, char _c = '0'): u(_u), v(_v), w(_w), c(_c) {}
	bool operator<(const edge& rhs) const {
		return w > rhs.w;
	}
	friend ostream& operator<<(ostream& o, const edge& e) {
		return o << '(' << e.u << ',' << e.v << ',' << e.w << ')';
	}
};

ll shortest_path (int s, int t, int sz, vector<vector<edge>>& adj) {
	ll dist[sz]; bool vis[sz]; // int p[sz];
	for (int i = 0; i < sz; i++) {
		dist[i] = MAX;
		vis[i] = 0;
		// p[i] = -1;
	}
	priority_queue<edge> pq;
	dist[s] = 0;
	pq.push(edge(s,s,0,'0'));
	while (not pq.empty()) {
		char c = pq.top().c;
		int u = pq.top().v; pq.pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		for (edge& e : adj[u]) {
			if (not vis[e.v] and ((dist[e.v] > dist[u] + e.w and c != e.c) or dist[e.v] == MAX)) {
				dist[e.v] = dist[u] + e.w;
				// p[e.v] = u;
				pq.push(edge(e.u,e.v,dist[e.v],e.c));
			}
		}
	}

	return dist[t];
}

int n, m;
string s, t;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	// cout.precision(2); cout << fixed;
	while (1) {
		cin >> m;
		if (m == 0)
			break;
		n = 1;
		map<string, int> ass;
		cin >> s >> t;
		ass[s] = n++;
		ass[t] = n++;
		tuple<string,string,string> a[m];
		for (int i = 0; i < m; i++) {
			string u, v, w; cin >> u >> v >> w;
			a[i] = {u,v,w};
			if (ass[u] == 0)
				ass[u] = n++;
			if (ass[v] == 0)
				ass[v] = n++;
		}
		vector<vector<edge>> adj(n);
		for (int i = 0; i < m; i++) {
			string u, v, w; tie(u,v,w) = a[i];
			adj[ass[u]].push_back(edge(ass[u],ass[v],w.size(),w[0]));
			adj[ass[v]].push_back(edge(ass[v],ass[u],w.size(),w[0]));
		}

		ll ans = shortest_path(ass[s], ass[t], n, adj);
		if (ans == MAX) {
			cout << "impossivel" << endl;
		} else {
			cout << ans << endl;
		}

	}

	return 0;
}