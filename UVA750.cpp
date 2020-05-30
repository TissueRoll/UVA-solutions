#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 105;
const int IMAX = 1e9+7;

int x[8], y[8], mx, my;
bool vis[8];

set<string> s;

bool diag(int sx, int sy, int pos) {
	for (int i = 0; i < pos; ++i) {
		if (abs(x[i]-sx) == abs(y[i]-sy)) {
			return false;
		}
	}
	return true;
}

void dfs (int pos) {
	if (pos == 8) {
		if (y[my] != mx) return;
		string ans = "";
		for (int i = 0; i < 8; ++i) {
			ans += to_string(y[i]+1) + (i+1 == 8 ? "" : " ");
		}
		s.insert(ans);
		return;
	}

	for (int i = 0; i < 8; ++i) {
		if (not vis[i] and diag(pos, i, pos)) {
			vis[i] = 1;
			x[pos] = pos;
			y[pos] = i;
			dfs(pos+1);
			vis[i] = 0;
		}
	}
}

int main () {
	int T; cin >> T;
	for (int t = 0; t < T; ++t) {
		if (t > 0) cout << endl;
		cout << "SOLN       COLUMN" << endl;
		cout << " #      1 2 3 4 5 6 7 8" << endl << endl;
		memset(vis, 0, sizeof vis);
		memset(x, 0, sizeof x);
		memset(y, 0, sizeof y);
		cin >> mx >> my; mx--; my--;
		dfs(0);
		int soln = 1;
		for (string o : s) {
			printf("%2d      ", soln++);
			cout << o << endl;
		}
		s.clear();
	}
	return 0;
}
