#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector <int> dsu, sz, mn, mx;

inline int leader(int i) {
	return dsu[i] = (dsu[i] == i ? i : leader(dsu[i]));
}

inline void get(int i) {
	i = leader(i);
	cout << mn[i] << ' ' << mx[i] << ' ' << sz[i] << endl;
}

inline void makeUnion(int u, int v) {
	u = leader(u);
	v = leader(v);
	if (u == v)
		return;
	dsu[u] = v;
	sz[v] += sz[u];
	mn[v] = min(mn[u], mn[v]);
	mx[v] = max(mx[u], mx[v]);
}

int main() {
	int n;
	cin >> n;
	dsu.resize(n);
	sz.resize(n, 1);
	mn.resize(n);
	mx.resize(n);
	for (int i = 0; i < n; ++i) {
		dsu[i] = i;
		mn[i] = i + 1;
		mx[i] = i + 1;
	}
	string s;
	while (cin >> s) {
		if (s[0] == 'g') {
			int x;
			cin >> x;
			x--;
			get(x);
		} else {
			int x, y;
			cin >> x >> y;
			x--, y--;
			makeUnion(x, y);
		}
	}
	return 0;
}
