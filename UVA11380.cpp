#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 105;
const int M = 205;
const int inf = numeric_limits<int>::max();

using ll = long long;
struct edge { int u, v; ll c, f; };
struct graph {
    int n;
    vector<edge> edges;
    vector<vector<int>> adj;
    graph(int n) : n(n), adj(n + 1) {}
    void add_edge(int u, int v, ll c) {
        if(u != v) {
            adj[u].push_back(edges.size()); edges.push_back({u, v, c, 0});
            adj[v].push_back(edges.size()); edges.push_back({v, u, 0, 0});
        }
    }
};
ll max_flow(graph& g, int s, int t) {
    vector<int> d(g.n + 1), adj_ptr(g.n + 1);
    auto make_level_graph = [&]() {
        fill(d.begin(), d.end(), -1);
        d[s] = 0;
        queue<int> q({s});
        while(not q.empty()) {
            int u = q.front(); q.pop();
            for(int i : g.adj[u]) {
				int u = g.edges[i].u, v = g.edges[i].v;
				ll c = g.edges[i].c, f = g.edges[i].f;
                // auto [u, v, c, f] = g.edges[i];
                if(c - f > 0 and d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d[t] != -1;
    };
    function<ll(int, ll)> augment = [&](int u, ll b) {
        if(u == t) return b;
        for(int& j = adj_ptr[u]; j < g.adj[u].size(); j++) {
            edge& forward = g.edges[g.adj[u][j]];
            edge& reverse = g.edges[g.adj[u][j] ^ 1];
			int uu = forward.u, v = forward.v;
			ll c = forward.c, &f = forward.f;
            // auto& [uu, v, c, f] = forward;
			ll df;
            if(d[v] == d[u] + 1 and c - f > 0 and (df = augment(v, min(b, c - f)))) {
                f += df, reverse.f -= df;
                return df;
            }
        }
        return 0ll;
    };
    ll ans = 0;
    while(make_level_graph()) {
        fill(adj_ptr.begin(), adj_ptr.end(), 0);
        while(ll df = augment(s, numeric_limits<ll>::max())) {
            ans += df;
        }
    }
    return ans;
}

bool acceptable_destination (int x, int y, int n, int m) {
	if (x >= 0 && x < n && y >= 0 && y < m) return true;
	else return false;
}

int main () {
	int x, y, p; 
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    while (cin >> x >> y >> p) {
        string m[x]; for (int i = 0; i < x; i++) cin >> m[i];
        int id[x][y], c = 2;
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                id[i][j] = c++;
            }
        }
        graph g(2*c);
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                int tn = id[i][j];
                if (m[i][j] == '*') {
                    g.add_edge(0,tn, 1);
                    g.add_edge(tn, tn+c, 1);
                } else if (m[i][j] == '#') {
                    g.add_edge(tn, tn+c, inf);
                    g.add_edge(tn+c, 1, p);
                } else if (m[i][j] == '.') {
                    g.add_edge(tn, tn+c, 1);
                } else if (m[i][j] == '@') {
                    g.add_edge(tn, tn+c, inf);
                }
                for (int k = 0; k < 4; k++) {
                    int nx = i+dx[k], ny = j+dy[k];
                    if (!acceptable_destination(nx, ny, x, y)) continue;
                    int nn = id[nx][ny];
                    if (m[i][j] == '*' || m[i][j] == '.') {
                        if (m[nx][ny] != '~' || m[nx][ny] != '*') {
                            g.add_edge(tn+c, nn, 1);
                        }
                    } else if (m[i][j] == '@' || m[i][j] == '#') {
                        if (m[nx][ny] != '~' || m[nx][ny] != '*') {
                            g.add_edge(tn+c, nn, inf);
                        }
                    }
                }
            }
        }
        cout << max_flow(g, 0, 1) << endl;
    }
	return 0;
}