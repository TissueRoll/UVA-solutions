#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef complex<double> point; // 2D point only
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldob;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ii, int> ii_i;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<iii> viii;

#define re real()
#define im imag()
#define fi first
#define se second

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

const int N = 301;
const int NN = 1001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

ll n, m, mat[N][N];

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cout.precision(3); cout << fixed;
	
	int T = 0;
	while (cin >> n) {
		if (n == 0)
			break;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				mat[i][j] = 0;
			}
		}
		
		int big = 0;
		for (int i = 0; i < n; ++i) {
			int u, v; cin >> u >> v;
			big = max(big, max(u,v));
			mat[u][v] = 1;
		}
		big++;

		for (int k = 0; k < big; ++k) {
			for (int i = 0; i < big; ++i) {
				for (int j = 0; j < big; ++j) {
					// if (mat[i][k] + mat[k][j] < mat[i][j])
					// 	mat[i][j] = mat[i][k] + mat[k][j];
					mat[i][j] += mat[i][k]*mat[k][j];
				}
			}
		}

		for (int k = 0; k < big; ++k) {
			if (mat[k][k]) {
				for (int i = 0; i < big; ++i) {
					for (int j = 0; j < big; ++j) {
						if (mat[i][k] and mat[k][j])
							mat[i][j] = -1;
					}
				}
			}
		}

		cout << "matrix for city " << T++ << endl;
		for (int i = 0; i < big; ++i) {
			for (int j = 0; j < big; ++j) {
				cout << mat[i][j] << (j+1 == big ? "\n" : " ");
			}
		}
	}

	return 0;
}