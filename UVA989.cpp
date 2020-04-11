#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const ll LMAX = (1LL<<61);
const int IMAX = (1<<29);
const int BIG = 104206970;
const int PRIME = 104206969;

const int N = 10;
const ll MOD = 1e9+7;

int n, maxn, grid[N][N];
bool row[N][N], col[N][N], square[N][N], ok;

void dfs (int pos) {
	if (ok)
		return;
	if (pos == maxn*maxn) {
		ok = 1;
		for (int i = 0; i < maxn; i++) {
			for (int j = 0; j < maxn; j++) {
				cout << grid[i][j] << (j+1 == maxn ? '\n' : ' ');
			}
		}
		return;
	}
	
	int r = pos/maxn, c = pos%maxn;
	if (grid[r][c] > 0) { // already put something here
		dfs(pos+1);
	} else { // have to put something
		for (int i = 1; i <= maxn; i++) { // just try everything
			if (row[r][i] == 0 and col[c][i] == 0 and square[(r/n)*n+(c/n)][i] == 0) {
				row[r][i] = col[c][i] = square[(r/n)*n+(c/n)][i] = 1;
				grid[r][c] = i;
				dfs(pos+1);
				grid[r][c] = 0;
				row[r][i] = col[c][i] = square[(r/n)*n+(c/n)][i] = 0;
			}
		}
	}
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	// cout.precision(9); cout << fixed;
	int counter = 0;
	while (cin >> n) {
		if ((counter++) > 0)
			cout << endl;
		ok = 0;
		maxn = n*n;
		memset(row, 0, sizeof row);
		memset(col, 0, sizeof col);
		memset(square, 0, sizeof square);
		for (int i = 0; i < maxn; i++) {
			for (int j = 0; j < maxn; j++) {
				int temp; cin >> temp;
				grid[i][j] = temp;
				row[i][temp] = col[j][temp] = square[(i/n)*n+(j/n)][temp] = 1;
			}
		}

		dfs(0);

		if (not ok) {
			cout << "NO SOLUTION" << endl;
		}
	}
	return 0;
}
