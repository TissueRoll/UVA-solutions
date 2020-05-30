#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 105;
const int IMAX = 1e9+7;

int main () {
	int T; cin >> T;
	while (T--) {
		map<string, vector<pair<int,int>>> parts;
		int n, b; cin >> n >> b;
		for (int i = 0; i < n; ++i) {
			string type, name; int price, quality;
			cin >> type >> name >> price >> quality;
			parts[type].push_back({price,quality});
		}
		// look for the bottleneck
		int l = 0, r = 1000000000+1, mid;
		for (int i = 0, mid = l+(r-l)/2; i < 200; ++i, mid = l+(r-l)/2) {
			int cost = 0;
			for (auto part_list : parts) {
				int best = 1000000000+1;
				for (auto x : part_list.second) {
					if (x.second >= mid) {
						best = min(best, x.first);
					}
				}
				cost += best;
				if (cost > b)
					break;
			}
			if (cost <= b) {
				l = mid;
			} else {
				r = mid;
			}
		}
		cout << l+(r-l)/2 << endl;
	}
	return 0;
}
