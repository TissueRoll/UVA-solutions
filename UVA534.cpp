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

const int N = 201;
const int NN = 1001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

ll n; double dists[N][N];
pair<double,double> v[N];

double dist (const pair<double,double>& a, const pair<double,double>& b) {
	return sqrt(1.0*(a.fi-b.fi)*(a.fi-b.fi)+1.0*(a.se-b.se)*(a.se-b.se));
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cout.precision(3); cout << fixed;
	
	int T = 1;
	while (cin >> n) {
		if (n == 0)
			break;

		for (int i = 0; i < n; ++i) {
			cin >> v[i].fi >> v[i].se;
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == j) dists[i][j] = 1e10;
				else dists[i][j] = dist(v[i],v[j]);
				// cout << dists[i][j] << ' ';
			}
			// cout << endl;
		}

		for (int k = 0; k < n; ++k) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					dists[i][j] = min(dists[i][j], max(dists[i][k],dists[k][j]));
				}
			}
		}

		cout << "Scenario #" << T++ << endl;
		cout << "Frog Distance = " << dists[0][1] << endl << endl;
	}

	return 0;
}