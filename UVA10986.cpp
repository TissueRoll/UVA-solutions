#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldob;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<iii> viii;

// OST
template <typename T>
using ordered_set = __gnu_pbds::tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// from: https://codeforces.com/blog/entry/62393
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

const int INF = ~(1<<31);
const ll LINF = (1LL << 60);
const long double EPS = 1e-9;
const long double PI = acos(-1);

const int N = 300005;
const int NN = 1000007;
const int MOD = 998244353; // 1e9+7;
const int IMAX = 1e9+7;

// from franz library
struct graph {
  int n, *dist;
  vii *adj;
  graph(int n) {
    this->n = n;
    adj = new vii[n];
    dist = new int[n];
  }
  void add_edge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  void dijkstra(int s) {
	  for (int u = 0; u < n; ++u)
	    dist[u] = INF;
	  dist[s] = 0;
	  std::priority_queue<ii, vii, std::greater<ii> > pq;
	  pq.push({0, s});
	  while (!pq.empty()) {
	    int u = pq.top().second;
	    int d = pq.top().first;
	    pq.pop();
	    if (dist[u] < d)
	      continue;
	    dist[u] = d;
	    for (auto &e : adj[u]) {
	      int v = e.first;
	      int w = e.second;
	      if (dist[v] > dist[u] + w) {
	        dist[v] = dist[u] + w;
	        pq.push({dist[v], v});
	      }
	    }
	  }
	}
};

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed;

	int T; cin >> T;
	for (int _t = 1; _t <= T; ++_t) {
		int n, m, s, t; cin >> n >> m >> s >> t;
		graph g(n);
		for (int i = 0; i < m; ++i) {
			int u, v, w; cin >> u >> v >> w;
			g.add_edge(u,v,w);
		}
		g.dijkstra(s);
		cout << "Case #" << _t << ": ";
		if (g.dist[t] == INF) {
			cout << "unreachable\n";
		} else {
			cout << g.dist[t] << '\n';
		}
	}

	return 0;
}