#include<bits/stdc++.h>
#define pll pair<ll, ll>

using namespace std;
typedef long long ll;

inline void dfs(int u, int p, vector <vector <pll> > &g, vector <vector <ll> > &cost) {
	for (auto v : g[u]) {
		int vv = (int)v.first;
		if (vv == p)
			continue;
		dfs(vv, u, g, cost);
		cost[u][0] += max(cost[vv][1], cost[vv][0]);
	}
	for (auto v : g[u]) {
		int vv = (int)v.first;
		if (vv == p)
			continue;
		cost[u][1] = max(cost[u][1], cost[u][0] - max(cost[vv][0], cost[vv][1]) + cost[vv][0] + v.second);
	}
}

int main() {
	freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
	int n;
	cin >> n;
	vector <vector <pll> > g(n);
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		g[u].push_back({v, w});
		g[v].push_back({u, w});
	}
	vector <vector <ll> > cost(n, vector <ll> (2, 0));
	dfs(0, -1, g, cost);
	cout << max(cost[0][0], cost[0][1]);
	return 0;
}
