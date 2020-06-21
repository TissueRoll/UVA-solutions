#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldob;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef vector<ll> vi;
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

const int N = 102;
const int NN = 1000007;
const int MOD = 998244353; // 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

// from franz library
struct graph {
  ll n, *dist;
  vii *adj;
  graph(int n) {
    this->n = n;
    adj = new vii[n];
    dist = new ll[n];
  }
  void add_edge(int u, int v, int w) {
    adj[u].push_back({v, w});
    // adj[v].push_back({u, w});
  }
  void dijkstra(int s) {
	  for (int u = 0; u < n; ++u)
	    dist[u] = LINF;
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

vector<int> adj[150], v;
bool vis[150];

void reset () {
	memset(vis, 0, sizeof vis);
	v.clear();
	for (int i = 0; i < 150; ++i)
		adj[i].clear();
}

bool ok (int u) {
	for (int v : adj[u])
		if (vis[v])
			return false;
	return true;
}

bool dfs (string path) {
	if (path.size() == v.size()) {
		for (int i = 0; i < v.size(); ++i) {
			cout << path[i] << (i+1 == v.size() ? "\n" : " ");
		}
		return true;
	} else {
		bool ans = 0;
		for (int e : v) {
			if (not vis[e] and ok(e)) {
				vis[e] = 1;
				ans |= dfs(path+char(e));
				vis[e] = 0;
			}
		}
		return ans;
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed;

	string s;
	int T; cin >> T;
	getline(cin,s);
	for (int t = 1; t <= T; ++t) {
		reset();
		getline(cin,s);
		getline(cin,s);
		stringstream ss(s);
		char c0, c1, c2;
		while (ss >> c0)
			v.push_back(c0);
		getline(cin,s);
		ss = stringstream(s);
		while (ss >> c0 >> c1 >> c2) {
			adj[c0].push_back(c2);
		}
		
		if (t > 1) cout << endl;
		if (dfs("")) {
			// nothing
		} else {
			cout << "NO\n";
		}
	}


	return 0;
}