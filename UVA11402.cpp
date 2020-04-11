#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;

#define what_is(x) cerr << #x << " is " << x << endl;

const ll LMAX = (1LL<<61);
const int IMAX = (1<<29);
const int BIG = 104206970;
const int PRIME = 104206969;

const int N = 1024007;

// from franz' library
/*
struct segtree {
	int i, j, val, temp_val = 0;
	segtree *l, *r;
	segtree() {}
	segtree(vector<int> &ar, int _i, int _j) : i(_i), j(_j) {
		if (i == j) {
			val = ar[i];
			l = r = NULL;
		} else {
			int k = (i + j) >> 1;
			l = new segtree(ar, i, k);
			r = new segtree(ar, k+1, j);
			val = l->val + r->val;
		}
	}
	// 1 = turn to 1
	// 2 = turn to 0
	// 3 = flip
	// 0 = normal
	int operation (int x) {
		if (x == 1)
			return 2;
		else if (x == 2)
			return 1;
		else if (x == 3)
			return 0;
		else
			return 3;
	}
	void visit() {
		if (temp_val == 0)
			return;
		if (temp_val == 1)
			val = (j-i+1);
		else if (temp_val == 2)
			val = 0;
		else if (temp_val == 3)
			val = (j-i+1)-val;
		if (l) {
			if (temp_val == 1 or temp_val == 2) {
				l->temp_val = r->temp_val = temp_val;
			} else {
				l->temp_val = operation(l->temp_val);
				r->temp_val = operation(r->temp_val);
			}
		}
		temp_val = 0;
	}
	// to buccaneer pirates
	void one(int _i, int _j) {
		visit();
		if (_i <= i && j <= _j) {
			temp_val = 1;
			visit();
		} else if (_j < i or j < _i) {
			// do nothing
		} else {
			l->one(_i, _j);
			r->one(_i, _j);
			val = l->val + r->val;
		}
	}
	// to barbary pirates
	void zero(int _i, int _j) {
		visit();
		if (_i <= i && j <= _j) {
			temp_val = 2;
			visit();
		} else if (_j < i or j < _i) {
			// do nothing
		} else {
			l->zero(_i, _j);
			r->zero(_i, _j);
			val = l->val + r->val;
		}
	}
	// flip the pirate type
	void flip(int _i, int _j) {
		visit();
		if (_i <= i && j <= _j) {
			temp_val = 3;
			visit();
		} else if (_j < i or j < _i) {
			// do nothing
		} else {
			l->flip(_i, _j);
			r->flip(_i, _j);
			val = l->val + r->val;
		}
	}
	int query(int _i, int _j) {
		visit();
		if (_i <= i and j <= _j) {
			return val;
		} else if (_j < i || j < _i) {
			return 0;
		} else {
			return l->query(_i, _j) + r->query(_i, _j);
		}
	}
};
// */

/*
struct segtree {
	int n, *vals, *deltas;
	segtree(vector<int> &ar) {
		n = ar.size();
		vals = new int[4*n];
		deltas = new int[4*n];
		build(ar, 1, 0, n-1);
	}
	void build(vector<int> &ar, int p, int i, int j) {
		deltas[p] = 0;
		if (i == j)
			vals[p] = ar[i];
		else {
			int k = (i + j) / 2;
			build(ar, p<<1, i, k);
			build(ar, p<<1|1, k+1, j);
			pull(p);
		}
	}
	void pull(int p) {
		vals[p] = vals[p<<1] + vals[p<<1|1];
	}
	int operation (int x) {
		if (x == 1)
			return 2;
		else if (x == 2)
			return 1;
		else if (x == 3)
			return 0;
		else
			return 3;
	}
	void push(int p, int i, int j) { // visit
		if (deltas[p] == 0)
			return;
		if (deltas[p] == 1) {
			vals[p] = j-i+1;
		} else if (deltas[p] == 2) {
			vals[p] = 0;
		} else if (deltas[p] == 3) {
			vals[p] = (j-i+1)-vals[p];
		}

		if (i != j) {
			if (deltas[p] == 1 or deltas[p] == 2) {
				deltas[p<<1] = deltas[p<<1|1] = deltas[p];
			} else {
				deltas[p<<1] = operation(deltas[p<<1]);
				deltas[p<<1|1] = operation(deltas[p<<1|1]);
			}
		}

		deltas[p] = 0;
	}
	void one(int _i, int _j, int p, int i, int j) {
		push(p, i, j);
		if (_i <= i && j <= _j) {
			deltas[p] = 1;
			push(p, i, j);
		} else if (_j < i || j < _i) {
			// do nothing
		} else {
			int k = (i + j) / 2;
			one(_i, _j, p<<1, i, k);
			one(_i, _j, p<<1|1, k+1, j);
			pull(p);
		}
	}
	void zero(int _i, int _j, int p, int i, int j) {
		push(p, i, j);
		if (_i <= i && j <= _j) {
			deltas[p] = 2;
			push(p, i, j);
		} else if (_j < i || j < _i) {
			// do nothing
		} else {
			int k = (i + j) / 2;
			zero(_i, _j, p<<1, i, k);
			zero(_i, _j, p<<1|1, k+1, j);
			pull(p);
		}
	}
	void flip(int _i, int _j, int p, int i, int j) {
		push(p, i, j);
		if (_i <= i && j <= _j) {
			deltas[p] = 3;
			push(p, i, j);
		} else if (_j < i || j < _i) {
			// do nothing
		} else {
			int k = (i + j) / 2;
			flip(_i, _j, p<<1, i, k);
			flip(_i, _j, p<<1|1, k+1, j);
			pull(p);
		}
	}
	int query(int _i, int _j, int p, int i, int j) {
		push(p, i, j);
		if (_i <= i and j <= _j) {
			return vals[p];
		} else if (_j < i || j < _i) {
			return 0;
		} else {
			int k = (i + j) / 2;
			return query(_i, _j, p<<1, i, k) + query(_i, _j, p<<1|1, k+1, j);
		}
	}
};
// */

int vals[4*N], deltas[4*N];
void pull(int p) {
	vals[p] = vals[p<<1] + vals[p<<1|1];
}
void build(vector<int> &ar, int p, int i, int j) {
	deltas[p] = 0;
	if (i == j)
		vals[p] = ar[i];
	else {
		int k = (i + j) / 2;
		build(ar, p<<1, i, k);
		build(ar, p<<1|1, k+1, j);
		pull(p);
	}
}
int operation (int x) {
	if (x == 1)
		return 2;
	else if (x == 2)
		return 1;
	else if (x == 3)
		return 0;
	else
		return 3;
}
void push(int p, int i, int j) { // visit
	if (deltas[p] == 0)
		return;
	if (deltas[p] == 1) {
		vals[p] = j-i+1;
	} else if (deltas[p] == 2) {
		vals[p] = 0;
	} else if (deltas[p] == 3) {
		vals[p] = (j-i+1)-vals[p];
	}

	if (i != j) {
		if (deltas[p] == 1 or deltas[p] == 2) {
			deltas[p<<1] = deltas[p<<1|1] = deltas[p];
		} else {
			deltas[p<<1] = operation(deltas[p<<1]);
			deltas[p<<1|1] = operation(deltas[p<<1|1]);
		}
	}

	deltas[p] = 0;
}
void one(int _i, int _j, int p, int i, int j) {
	push(p, i, j);
	if (_i <= i && j <= _j) {
		deltas[p] = 1;
		push(p, i, j);
	} else if (_j < i || j < _i) {
		// do nothing
	} else {
		int k = (i + j) / 2;
		one(_i, _j, p<<1, i, k);
		one(_i, _j, p<<1|1, k+1, j);
		pull(p);
	}
}
void zero(int _i, int _j, int p, int i, int j) {
	push(p, i, j);
	if (_i <= i && j <= _j) {
		deltas[p] = 2;
		push(p, i, j);
	} else if (_j < i || j < _i) {
		// do nothing
	} else {
		int k = (i + j) / 2;
		zero(_i, _j, p<<1, i, k);
		zero(_i, _j, p<<1|1, k+1, j);
		pull(p);
	}
}
void flip(int _i, int _j, int p, int i, int j) {
	push(p, i, j);
	if (_i <= i && j <= _j) {
		deltas[p] = 3;
		push(p, i, j);
	} else if (_j < i || j < _i) {
		// do nothing
	} else {
		int k = (i + j) / 2;
		flip(_i, _j, p<<1, i, k);
		flip(_i, _j, p<<1|1, k+1, j);
		pull(p);
	}
}
int query(int _i, int _j, int p, int i, int j) {
	push(p, i, j);
	if (_i <= i and j <= _j) {
		return vals[p];
	} else if (_j < i || j < _i) {
		return 0;
	} else {
		int k = (i + j) / 2;
		return query(_i, _j, p<<1, i, k) + query(_i, _j, p<<1|1, k+1, j);
	}
}

int T, n, m, q, counter;
string temp;

int main () {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	// cout.precision(9); cout << fixed;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		cout << "Case " << t << ":\n";
		counter = 1;
		cin >> m;
		vector<int> arr;
		for (int i = 0; i < m; i++) {
			cin >> n >> temp;
			for (int j = 0; j < n; j++)
				for (char c : temp)
					arr.push_back(c-'0');
		}
		n = arr.size();
		// segtree seg(arr);
		build(arr, 1, 0, n-1);
		cin >> q;
		while (q--) {
			char c; int l, r; cin >> c >> l >> r;
			if (c == 'F') {
				one(l, r, 1, 0, n-1);
			} else if (c == 'E') {
				zero(l, r, 1, 0, n-1);
			} else if (c == 'I') {
				flip(l, r, 1, 0, n-1);
			} else {
				cout << 'Q' << (counter++) << ": " << query(l, r, 1, 0, n-1) << endl;
			}
		}
	}

	return 0;
}
