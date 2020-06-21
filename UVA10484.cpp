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

const int N = 101;
const int NN = 1000007;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const int dx[4] = {0,0,-1,1};
const int dy[4] = {-1,1,0,0};

bitset<N> is; // #include <bitset>
int pr[N], primes = 0;
void sieve() {
    is[2] = true; pr[primes++] = 2;
    for (int i = 3; i < N; i += 2) is[i] = 1;
    for (int i = 3; i*i < N; i += 2)
        if (is[i])
            for (int j = i*i; j < N; j += i)
                is[j]= 0;
    for (int i = 3; i < N; i += 2)
        if (is[i])
            pr[primes++] = i;}

vector<vector<int>> PF(N,vector<int>(N,0));

void pregen() {
	sieve();
	for (int i = 2; i < N; ++i) {
		int ti = i;
		for (int j = 0; j < primes; ++j) {
			while (ti%pr[j] == 0) {
				PF[i][j]++;
				ti /= pr[j];
			}
		}
	}
	for (int i = 3; i < N; ++i) {
		for (int j = 0; j < primes; ++j) {
			PF[i][j] += PF[i-1][j];
		}
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	// cout.precision(3); cout << fixed;

	pregen();
	ll n, d, td, ans;
	while (cin >> n >> d) {
		d = abs(d);
		if (n == 0 and d == 0) break;
		if (n == 0 and d == 1) {
			cout << 1 << endl;
			continue;
		} else if (n == 1 and d == 1) {
			cout << 1 << endl;
			continue;
		}
		bool ok = 1;
		vector<int> pf = PF[n];
		td = d;
		for (int i = 0; i < primes; ++i) {
			while (td%pr[i] == 0) {
				pf[i]--;
				td /= pr[i];
			}
			if (pf[i] < 0)
				ok = 0;
		}
		if (td != 1)
			ok = 0;

		if (ok) {
			ans = 1;
			for (int i = 0; i < primes; ++i)
				ans *= (pf[i]+1);
			cout << ans << endl;
		} else {
			cout << 0 << endl;
		}
	}

	return 0;
}