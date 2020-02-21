#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
vector <int> dsu, sz;
vector <string> ans;

inline int leader(int i) {
	return dsu[i] = (dsu[i] == i ? i : leader(dsu[i]));
}

inline void get(int u, int v) {
	u = leader(u);
	v = leader(v);
	ans.push_back(u == v ? "YES" : "NO");
}

inline void makeUnion(int u, int v) {
	u = leader(u);
	v = leader(v);
	if (u == v)
		return;
	if (sz[u] > sz[v])
		swap(u, v);
	dsu[u] = v;
	sz[v] += sz[u];
}

int main() {
	int n, m, q;
	cin >> n >> m >> q;
	dsu.resize(n);
	sz.resize(n, 1);
	for (int i = 0; i < n; ++i)
		dsu[i] = i;
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		u--, v--;
	}
	vector <pair <string, pair <int, int> > > qq(q);
	for (int i = 0; i < q; ++i)
		cin >> qq[i].first >> qq[i].second.first >> qq[i].second.second;
	for (int i = q - 1; i >= 0; --i) {
		if (qq[i].first[0] == 'a') {
			get(qq[i].second.first - 1, qq[i].second.second - 1);
		} else {
			makeUnion(qq[i].second.first - 1, qq[i].second.second - 1);
		}
	}
	for (int i = ans.size() - 1; i >= 0; --i)
		cout << ans[i] << endl;
	return 0;
}
