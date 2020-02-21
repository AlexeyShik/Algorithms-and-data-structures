#include <bits/stdc++.h>
#define fastio ios_base :: sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pii pair<int, int>

using namespace std;
typedef long long ll;
vector <int> sz;
vector <bool> part;
vector <int> dsu;
int n, m;

inline pii leader(int u) {
	bool xxor = 0;
	while (dsu[u] != u) {
		xxor ^= part[u];
		u = dsu[u];
	}
	return {u, xxor};
}

inline bool get(int u, int v) {
	return leader(u).second == leader(v).second;
}

inline void join(int u, int v) {
	pii pu = leader(u);
	pii pv = leader(v);
	u = pu.first;
	v = pv.first;
	if (sz[u] > sz[v]) {
		swap(pu, pv);
		swap(u, v);
	}
	dsu[u] = v;
	part[u] = pu.second ^ pv.second ^ 1;
	sz[v] += sz[u];
}

int main() {
	fastio;
	cin >> n >> m;
	dsu.resize(n);
	sz.resize(n, 1);
	part.resize(n, 0);
	for (int i = 0; i < n; ++i)
		dsu[i] = i;
	int shift = 0;
	for (int i = 0; i < m; ++i) {
		int id, u, v;
		cin >> id >> u >> v;
		u = (u + shift - 1) % n;
		v = (v + shift - 1) % n;
		if (id == 0) {
			join(u, v);
		} else {
			if (get(u, v)) {
				cout << "YES" << endl;
				shift = (shift + 1) % n;
			} else {
				cout << "NO" << endl;
			}
		}
	}
	return 0;
}
/*
3 5
0 1 2
0 2 3
1 1 2
1 1 3
1 1 3
*/
