#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector <int> dsu, r, sz;
int n;

inline int leader(vector <int> &dsu, int i) {
	return dsu[i] = (dsu[i] == i ? i : leader(dsu, dsu[i]));
}

inline bool get(int u, int v) {
	return leader(dsu, u) == leader(dsu, v);
}

inline void makeUnion(int u, int v) {
	u = leader(dsu, u);
	v = leader(dsu, v);
	if (u == v)
		return;
	if (sz[u] > sz[v])
		swap(u, v);
	dsu[u] = v;
	sz[v] += sz[u];
}

inline void makeGreatUnion(int u, int v) {
	while (u < v) {
		r[u] = r[u + 1];
		makeUnion(u, r[u]);
		u = r[u];
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int m;
	cin >> n >> m;
	dsu.resize(n);
	r.resize(n);
	sz.resize(n, 1);
	for (int i = 0; i < n; ++i) {
		dsu[i] = i;
		r[i] = i;
	}
	for (int i = 0; i < m; ++i) {
		int id;
		cin >> id;
		int u, v;
		cin >> u >> v;
		u--, v--;
		u = leader(r, u);
		v = leader(r, v);
		if (id == 1) {
			makeUnion(u, v);
		} else if (id == 2) {
			makeGreatUnion(u, v);
		} else {
			cout << (get(u, v) ? "YES" : "NO") << endl;
		}
	}
	return 0;
}
