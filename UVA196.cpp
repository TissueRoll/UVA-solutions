#include <bits/stdc++.h>
using namespace std;

#define x() first
#define y() second

typedef long long ll;

const int N = 1001;
const ll MOD = 2000000011;
const ll LINF = (1LL<<62);
const long double EPS = 1e-9;

int dx4[4] = {0,0,1,-1};
int dy4[4] = {-1,1,0,0};
int dx8[8] = {-1,-1,-1,0,0,1,1,1};
int dy8[8] = {-1,0,1,-1,1,-1,0,1};

int T, n, m;
map<string,int> sheet;
map<int,string> rsheet;
vector<pair<int,int>> adj[1000][20000];
string in[1000][20000];
ll ans[1000][20000];
bool complete[1000][20000];

ll dfs(int x, int y) {
	if (complete[x][y])
		return ans[x][y];
	complete[x][y] = 1;
	for (pair<int,int> u : adj[x][y])
		ans[x][y] += dfs(u.x(),u.y());
	return ans[x][y];
}

int main () {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	for (int i = -1; i < 26; ++i) {
		for (int j = (i >= 0 ? 0 : -1); j < 26; ++j) {
			for (int k = 0; k < 26; ++k) {
				string tmp = "";
				if (i >= 0) {
					tmp = "AAA";
					tmp[0] += i; tmp[1] += j; tmp[2] += k;
					sheet[tmp] = 26*26*(i+1) + 26*(j+1) + k;
				} else if (j >= 0) {
					tmp = "AA";
					tmp[0] += j; tmp[1] += k;
					sheet[tmp] = 26*(j+1) + k;
				} else {
					tmp = "A";
					tmp[0] += k;
					sheet[tmp] = k;
				}
				rsheet[sheet[tmp]] = tmp;
			}
		}
	}
	cin >> T;
	while (T--) {
		stack<pair<int,int>> eval;
		cin >> m >> n;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> in[i][j];
				if (in[i][j][0] != '=') {
					ans[i][j] = stoll(in[i][j]);
					complete[i][j] = 1;
				} else {
					ans[i][j] = 0;
					complete[i][j] = 0;
					string tmp = "";
					string tmp2 = "";
					for (int k = 1; k < in[i][j].size(); ++k) {
						if (in[i][j][k] == '+') {
							// eval.push({stoi(tmp2)-1,sheet[tmp]});
							adj[i][j].push_back({stoi(tmp2)-1,sheet[tmp]});
							tmp = ""; tmp2 = "";
						} else if (isdigit(in[i][j][k])) {
							tmp2 += in[i][j][k];
						} else {
							tmp += in[i][j][k];
						}
					}
					if (tmp.size() > 0 and tmp2.size() > 0) {
						// eval.push({stoi(tmp2)-1,sheet[tmp]});
						adj[i][j].push_back({stoi(tmp2)-1,sheet[tmp]});
						tmp = ""; tmp2 = "";
					}
				}
			}
		}
		/*
		while (not eval.empty()) {
			pair<int,int> x = eval.top(); eval.pop();
			if (in[x.x()][x.y()][0] != '=')
				continue;
			if (complete[x.x()][x.y()])
				continue;
			complete[x.x()][x.y()] = 1;
			string tmp = "";
			string tmp2 = "";
			ll tmpa = 0;
			for (int i = 1; i < in[x.x()][x.y()].size(); ++i) {
				if (in[x.x()][x.y()][i] == '+') {
					tmpa += ans[stoi(tmp2)-1][sheet[tmp]];
					tmp = ""; tmp2 = "";
				} else if (isdigit(in[x.x()][x.y()][i])) {
					tmp2 += in[x.x()][x.y()][i];
				} else {
					tmp += in[x.x()][x.y()][i];
				}
			}
			if (tmp.size() > 0 and tmp2.size() > 0) {
				tmpa += ans[stoi(tmp2)-1][sheet[tmp]];
				tmp = ""; tmp2 = "";
			}
			ans[x.x()][x.y()] = tmpa;
		}
		// */
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (not complete[i][j])
					dfs(i,j);
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cout << ans[i][j] << (j+1 == m ? '\n' : ' ');
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				adj[i][j].clear();
			}
		}
	}
	cout.flush();
	return 0;
}
