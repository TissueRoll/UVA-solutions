#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 105;
const int IMAX = 1e9+7;

int in[5];
bool found, vis[5];

void possible (int pos, int val) {
	if (pos == 5 and val == 23) {
		found = 1;
		return;
	} else {
		for (int i = 0; i < 5; ++i) {
			if (vis[i])
				continue;
			vis[i] = 1;
			possible(pos+1, val+in[i]);
			possible(pos+1, val-in[i]);
			possible(pos+1, val*in[i]);
			vis[i] = 0;
		}
	}
}

int main () {
	while (true) {
		bool end = 1;
		for (int i = 0; i < 5; ++i) {
			cin >> in[i];
			end = (in[i] != 0 ? 0 : 1);
			vis[i] = 0;
		}
		if (end)
			break;
		found = 0;
		for (int i = 0; i < 5; ++i) {
			vis[i] = 1;
			possible(1, in[i]);
			vis[i] = 0;
		}
		if (found) {
			cout << "Possible" << endl;
		} else {
			cout << "Impossible" << endl;
		}
	}
	return 0;
}
