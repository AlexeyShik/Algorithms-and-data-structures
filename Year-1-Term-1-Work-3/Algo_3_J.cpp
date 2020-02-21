#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int p = 1000003;
ll zerg = 0;
int n, m;
vector <int> dsu;
vector <ll> add, cnt, sz;

inline int leader(int u) {
	return (dsu[u] == u ? u : leader(dsu[u]));
}

inline int siftToLeader(int u) {
	if (dsu[u] == u) {
		add[u]++;
		return u;
	}
	return siftToLeader(dsu[u]);
}

void join(int u, int v) {
	u = leader(u);
	v = leader(v);
	if (u == v)
		return;
	zerg = (13 * zerg + 11) % p;
	if (sz[u] > sz[v])
		swap(u, v);
	dsu[u] = v;
	sz[v] += sz[u];
	add[u] -= add[v];
}

inline void up(int u, ll &increase) {
	increase += add[u];
	if (dsu[u] == u)
		return;
	up(dsu[u], increase);
}

ll calc(int u) {
	ll increase = 0;
	up(u, increase);
	ll ans = increase - cnt[u];
	cnt[u] = increase;
	return ans;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	dsu.resize(n);
	add.resize(n, 0);
	cnt.resize(n, 0);
	sz.resize(n, 1);
	for (int i = 0; i < n; ++i)
		dsu[i] = i;
	for (int i = 0; i < m; ++i) {
		int type;
		cin >> type;
		if (type == 1) {
			int x;
			cin >> x;
			x = (x + (int)zerg) % n;
			zerg = (30 * zerg + 239) % p;
			siftToLeader(x);
		} else if (type == 2) {
			int x, y;
			cin >> x >> y;
			x = (x + (int)zerg) % n;
			y = (y + (int)zerg) % n;
			join(x, y);
		} else if (type == 3) {
			int x;
			cin >> x;
			x = (x + (int)zerg) % n;
			ll q = calc(x);
			zerg = (1ll * 100500 * zerg + q) % p;
			cout << q << endl;
		}
	}
	return 0;
}
