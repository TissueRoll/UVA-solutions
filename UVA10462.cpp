#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;
typedef long double ldob;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef pair<ii,ii> iiii;

#define f() first
#define s() second

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

const int N = 101;
const int NN = 101;
const int MOD = 1e9+7;
const int IMAX = 2e9+7;
const ll LLMAX = (1LL << 60);

const int dx[] = {-1,-1,0,1,1,1,0,-1};
const int dy[] = {0,1,1,1,0,-1,-1,-1};

struct graph {
  int n;
  std::vector<iiii> edges;
  graph(int n) : n(n) {}
  void add_edge(int u, int v, int w, int i) {
    edges.push_back({{w, i}, {u, v}});
  }
  void sort_edges() {
  	sort(edges.begin(), edges.end());
  }
};

struct union_find {
  vector<int> p; union_find(int n) : p(n, -1) { }
  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  bool unite(int x, int y) {
    int xp = find(x), yp = find(y);
    if (xp == yp)       return false;
    if (p[xp] > p[yp])  std::swap(xp,yp);
    p[xp] += p[yp], p[yp] = xp;
    return true;
  }
  int size(int x) { return -p[find(x)]; }
};

void kruskal(vector<iiii> &res,const graph& g, int ex) {
  res.clear();
  std::priority_queue<iiii, vector<iiii>, std::greater<iiii> > pq;
  for (auto &edge : g.edges)
    pq.push(edge);
  union_find uf(g.n);
  while (!pq.empty()) {
    auto node = pq.top();   pq.pop();
    if (node.first.second == ex)
    	continue;
    int u = node.second.first;
    int v = node.second.second;
    if (uf.unite(u, v))
      res.push_back(node);
  }
}

int T, n, m;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed; 

	cin >> T;
	for (int t = 1; t <= T; ++t) {
		cout << "Case #" << t << " : ";
		cin >> n >> m;
		graph g(n+1);
		for (int i = 0; i < m; ++i) {
			int u, v, w; cin >> u >> v >> w;
			g.add_edge(u,v,w,i);
			// g.add_edge({w,{v,u}});
		}

		g.sort_edges();

		vector<iiii> res;
		kruskal(res, g, -1);

		if (res.size() != n-1) {
			cout << "No way" << endl;
		} else {
			int ans = IMAX;
			vector<iiii> tmp; bool ok = 0;
			for (int i = 0; i < res.size(); ++i) {
				kruskal(tmp,g,res[i].first.second);
				if (tmp.size() == n-1) {
					ok = 1;
					int tans = 0;
					for (int j = 0; j < tmp.size(); ++j) {
						tans += tmp[j].first.first;
					}
					ans = min(ans,tans);
				}
			}

			if (ok) {
				cout << ans << endl;
			} else {
				cout << "No second way" << endl;
			}
		}
	}

	return 0;
}