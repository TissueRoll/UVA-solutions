#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 105;
vector<int> adj[N];
int flow[N][N];
int cap[N][N];
bool vis[N];
int parent[N];

/*
 * this works bc it stops when theres no augmenting path
 * if you change this to BFS then its O(E^2V) 
 */

bool bfs (int s, int t) {
	memset(parent,-1,sizeof(parent));
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : adj[u]) {
			if (parent[v] == -1 && cap[u][v] - flow[u][v] > 0) {
				parent[v] = u;
				q.push(v);
			}
		}
	}
	return parent[t] != -1;
}

bool dfs(int s, int t) {
	if (s==t) return true;
	else {
		for (int v : adj[s]) {
			if (!vis[v] && cap[s][v] - flow[s][v] > 0) {
				if (dfs(v,t)) return true; // if found
			}
		}
		return false;
	}
}

int max_flow (int s, int t) {
	memset(flow,0,sizeof(flow));
	int max_flow_value = 0;
	while (true) {
		memset(vis,false,sizeof(vis));
		if (bfs(s,t)) {
			//cout << "oh no" << endl;
			int bottleneck = INF;
			for (int v = t, u = parent[t]; v != s; v = parent[v], u = parent[v]) {
				bottleneck = min(bottleneck, (cap[u][v] - flow[u][v]));
			}
			
			for (int v = t, u = parent[t]; v != s; v = parent[v], u = parent[v]) {
				flow[u][v] += bottleneck;
				flow[v][u] -= bottleneck;
			}
			max_flow_value += bottleneck;
		} else {
			break;
		}
	}
	return max_flow_value;
}

int n, tc;

int main() {
	tc = 1;
	while(cin >> n) {
		if (n == 0) return 0;
		memset(cap,0,sizeof(cap));
		memset(flow,0,sizeof(flow));
		memset(parent,-1,sizeof(parent));
		for (int i = 0; i < N; i++) adj[i].clear();
		int s, t, c; cin >> s >> t >> c;
		for (int i = 0; i < c; i++) {
			int u, v, c2; cin >> u >> v >> c2;
			if (u > v) swap(u,v);
			if (cap[u][v] == 0) {
				adj[u].push_back(v);
				adj[v].push_back(u);
			}
			cap[u][v] += c2;
			cap[v][u] = 0; 
		}

		int ans = max_flow(s,t);
		cout << "Network " << (tc++) << endl;
		cout << "The bandwidth is " << ans << ".\n\n"; 
	}

	return 0;
}