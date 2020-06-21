#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define x() real()
#define y() imag()

typedef complex<double> point; // 2D point only
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldob;
typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;
typedef pair<ii, ll> ii_i;
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

const int N = 100007;
const int NN = 1000000;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

ll n, m, distT[420], distD[420];
vector<iii> adj[420];

void add_edge (int u, int v, ii w) {
	adj[u].push_back({v,w});
	adj[v].push_back({u,w});
}

void dijkstra (int s) {
	for (int u = 0; u < n; ++u) {
		distT[u] = LINF;
		distD[u] = LINF;
	}
	distT[s] = 0;
	distD[s] = 0;
	priority_queue<ii_i, vector<ii_i>, greater<ii_i>> pq;
	pq.push({{0,0},s});
	while (not pq.empty()) {
		int u = pq.top().second;
		int t = pq.top().first.first;
		int d = pq.top().first.second;
		pq.pop();
		if (distT[u] < t and distD[u] < d) continue;
		// distT[u] = t;
		// distD[u] = d;
		for (auto &e : adj[u]) {
			int v = e.first;
			int wt = e.second.first;
			int wd = e.second.second;
			if (distT[v] > distT[u] + wt) {
				distT[v] = distT[u] + wt;
				distD[v] = distD[u] + wd;
				pq.push({{distT[v],distD[v]}, v});
			} else if (distT[v] == distT[u] + wt and distD[v] > distD[u] + wd) {
				distT[v] = distT[u] + wt;
				distD[v] = distD[u] + wd;
				pq.push({{distT[v],distD[v]}, v});
			}
		}
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(3); cout << fixed;

	int T; cin >> T;
	for (int t = 1; t <= T; ++t) {
		cin >> n >> m;
		for (int i = 0; i < m; ++i) {
			ll a, b, c, d; cin >> a >> b >> c >> d; --a; --b;
			add_edge(a,b,{c,d});
		}
		if (t > 1) cout << endl;
		int q; cin >> q;
		while (q--) {
			int u, v; cin >> u >> v; --u; --v;
			dijkstra(u);
			if (distT[v] == LINF and distD[v] == LINF) {
				cout << "No Path.\n";
			} else {
				cout << "Distance and time to reach destination is " << distD[v] << " & " << distT[v] << ".\n";
			}
		}
		for (int i = 0; i < n; ++i)
			adj[i].clear();
	}

	return 0;
}