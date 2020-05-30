#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
typedef long long ll;

// OST
template <typename T>
using ordered_set = __gnu_pbds::tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// ordered_set<int> t; t.insert(...);
// t.find_by_order(index); // 0-based
// t.order_of_key(key); --> STRICTLY LESS THAN KEY

const int N = 200001;
const int NN = 10000001;
const int IMAX = 1e9+7;

int n, t[2*N];

void build() {
	for (int i = n-1; i > 0; --i)
		t[i] = t[i<<1] + t[i<<1|1];
}

void update(int p, int v) {
	for (t[p += n] = v; p > 1; p >>= 1)
		t[p>>1] = t[p] + t[p^1];
}

int query (int l, int r) {
	int ans = 0;
	for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
		if (l&1) ans += t[l++];
		if (r&1) ans += t[--r];
	}
	return ans;
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0);
	int T = 1;
	while (true) {
		cin >> n;
		if (n == 0) break;
		if (T > 1) cout << endl;
		cout << "Case " << T++ << ":\n";
		for (int i = 0; i < n; ++i)
			cin >> t[n+i];
		build();
		string command;
		cin >> command;
		while (command != "END") {
			if (command == "S") {
				int x, r; cin >> x >> r; x--;
				update(x,r);
			} else {
				int x, y; cin >> x >> y; x--;
				cout << query(x,y) << endl;
			}
			cin >> command;
		}
	}
	return 0;
}