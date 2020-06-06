#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;
typedef long double ldob;
typedef pair<int,int> ii;

// OST
template <typename T>
using ordered_set = __gnu_pbds::tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// ordered_set<int> t; t.insert(...);
// t.find_by_order(index); // 0-based
// t.order_of_key(key); --> STRICTLY LESS THAN KEY

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

const int N = 1001;
const int NN = 1000001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const ll LLMAX = (1LL << 60);

const int dx[] = {-1,-1,0,1,1,1,0,-1};
const int dy[] = {0,1,1,1,0,-1,-1,-1};

int n, m, grid[N][N], vis[N][N], q, sx, sy, ex, ey;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed; 

	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			char c; cin >> c;
			grid[i][j] = int(c-'0');
		}
	}

	cin >> q;
	while (q--) {
		cin >> sx >> sy >> ex >> ey;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				vis[i][j] = IMAX;
			}
		}
		deque<ii> d;
		d.push_back({sx,sy});
		vis[sx][sy] = 0;
		while (not d.empty()) {
			int ux = d.front().first;
			int uy = d.front().second;
			d.pop_front();
			// cout << ux << ' ' << uy << endl;
			for (int i = 0; i < 8; ++i) {
				int nx = ux+dx[i], ny = uy+dy[i];
				if (not (1 <= nx and nx <= n and 1 <= ny and ny <= m)) continue;
				if (i == grid[ux][uy] and vis[ux][uy] < vis[nx][ny]) {
					vis[nx][ny] = vis[ux][uy];
					d.push_front({nx,ny});
				} else if (vis[ux][uy] + 1 < vis[nx][ny]) {
					vis[nx][ny] = vis[ux][uy]+1;
					d.push_back({nx,ny});
				}
			}
		}
		cout << vis[ex][ey] << endl;
	}

	return 0;
}