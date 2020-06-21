#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

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

#define x() real()
#define y() imag()

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

const int N = 300001;
const int NN = 1001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

int n, m, V[N]; ll u;
vector<ii> s[550];

template<typename T>
int clb(const vector<T>& v, T x) {
	int n = v.size();
	int l = 0, r = n;
	while (l < r) {
		int mid = l + (r-l)/2;
		if (x <= v[mid])
			r = mid;
		else
			l = mid+1;
	}
	return l;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(9); cout << fixed;
	
	while (cin >> n >> m >> u) {
		ll bktsz = sqrt(n);
		for (int i = 0; i < n; ++i) {
			cin >> V[i];
			s[i/bktsz].push_back({V[i],i});
		}

		for (int i = 0; i < n/bktsz+1; ++i)
			sort(s[i].begin(), s[i].end());

		for (int i = 0; i < m; ++i) {
			ll l, r, v, p; cin >> l >> r >> v >> p; l--; r--; p--;
			ll bktl = l/bktsz, bktr = r/bktsz, bktp = p/bktsz;

			// getting number of numbers less than v
			ll cnt = 0;
			for (int j = bktl; j <= bktr; ++j) {
				if (j == bktl or j == bktr) {
					for (int k = 0; k < s[j].size(); ++k) {
						if (l <= s[j][k].second and s[j][k].second <= r and s[j][k].first < v) {
							cnt++;
						}
					}
				} else {
					cnt += clb(s[j], {v,-1});
				}
			}

			// modifying p
			ll pval = u*cnt/(r-l+1LL);
			int where_p = 0;
			while (where_p < s[bktp].size() and s[bktp][where_p].second != p) where_p++;
			for (int i = where_p; i < s[bktp].size()-1; ++i)
				s[bktp][i] = s[bktp][i+1];
			s[bktp][s[bktp].size()-1] = {pval, p};
			for (int i = s[bktp].size()-1; i > 0 and s[bktp][i].first < s[bktp][i-1].first; --i)
				swap(s[bktp][i], s[bktp][i-1]);
			V[p] = pval;
		}

		for (int i = 0; i < n; ++i)
			cout << V[i] << endl;

		for (int i = 0; i < n/bktsz+1; ++i)
			s[i].clear();
	}

	return 0;
}