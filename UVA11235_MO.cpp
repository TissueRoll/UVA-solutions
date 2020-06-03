#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;
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

const int N = 100001;
const int NN = 1000001;
const int MOD = 1e9+7;
const int IMAX = 1e9+7;
const ll LLMAX = (1LL << 60);

int n, q, v[N], bktsz, o[N], cmprs, cnt[N], ccnt[N], f;
struct query {
	int a, b, idx;
} queries[N];
map<int,int> mapping;

// add
void add(int idx) {
	int x = v[idx];
	if (cnt[x] > 0)
		ccnt[cnt[x]]--;
	cnt[x]++;
	f = max(f,cnt[x]);
	ccnt[cnt[x]]++;
}

// remove
void remove(int idx) {
	int x = v[idx];
	if (f == cnt[x] and ccnt[cnt[x]] == 1)
		f--;
	ccnt[cnt[x]]--;
	cnt[x]--;
	ccnt[cnt[x]]++;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);

	while (cin >> n) {
		if (n == 0) break;
		bktsz = int(sqrt(n));
		cmprs = 0;
		mapping.clear();
		memset(cnt, 0, sizeof cnt);
		memset(ccnt, 0, sizeof ccnt);
		cin >> q;
		for (int i = 0; i < n; ++i) {
			cin >> v[i];
			if (mapping.count(v[i]) == 0) {
				mapping[v[i]] = cmprs++;
			}
			v[i] = mapping[v[i]];
		}

		for (int i = 0; i < q; ++i) {
			int l, r; cin >> l >> r; l--; r--;
			queries[i] = {l,r,i};
		}

		sort(queries,queries+q,[&](const query& a, const query& b){
			if (a.a/bktsz != b.a/bktsz)
				return a.a/bktsz < b.a/bktsz;
			return a.b < b.b;
		});

		int cl = 1, cr = 0; f = 0;
		for (int i = 0; i < q; ++i) { // for each query
			while (cr < queries[i].b) add(++cr);
			while (cr > queries[i].b) remove(cr--);
			while (cl < queries[i].a) remove(cl++);
			while (cl > queries[i].a) add(--cl);
			o[queries[i].idx] = f;
		}

		for (int i = 0; i < q; ++i) {
			cout << o[i] << endl;
		}

	}	

	return 0;
}