#include <iostream>
#include <vector>
#include <cmath>

#pragma GCC optimize("O3")

using namespace std;

const int maxlog = 22;
const int inf = 1e9+7;

vector <vector <int> > g;
vector <int> tin, tout, d;
int timer = 0;
vector <int> cost;
vector <vector <int> > lca, mini;

inline void dfs(int u, int p) {
    tin[u] = timer++;
    d[u] = (p == -1 ? 0 : d[p] + 1);
    for (auto v : g[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    tout[u] = timer++;
}

inline void count(int u, int p) {
    lca[u][0] = p;
    mini[u][0] = cost[u];
    for (int i = 1; i < maxlog && lca[u][i - 1] != -1; ++i) {
        lca[u][i] = lca[lca[u][i - 1]][i - 1];
        mini[u][i] = min(mini[u][i - 1], mini[lca[u][i - 1]][i - 1]);
    }
    for (auto v : g[u]) {
        if (v != u) {
            count(v, u);
        }
    }
}

inline int query(int u, int v) {
    int root = -1;
    int ans = inf;
    if (tin[u] <= tin[v] && tout[v] <= tout[u]) {
        root = u;
        int delta = d[v] - d[root];
        for (int i = maxlog - 1; i >= 0; --i) {
            if (delta & (1 << i)) {
                ans = min(ans, mini[v][i]);
                v = lca[v][i];
            }
        }
        return ans;
    }
    if (tin[v] <= tin[u] && tout[u] <= tout[v]) {
        root = v;
        int delta = d[u] - d[root];
        for (int i = maxlog - 1; i >= 0; --i) {
            if (delta & (1 << i)) {
                ans = min(ans, mini[u][i]);
                u = lca[u][i];
            }
        }
        return ans;
    }
    if (d[u] - d[v] > 0) {
        int delta = d[u] - d[v];
        for (int i = maxlog - 1; i >= 0; --i) {
            if (delta & (1 << i)) {
                ans = min(ans, mini[u][i]);
                u = lca[u][i];
            }
        }
    }
    if (d[v] - d[u] > 0) {
        int delta = d[v] - d[u];
        for (int i = maxlog - 1; i >= 0; --i) {
            if (delta & (1 << i)) {
                ans = min(ans, mini[v][i]);
                v = lca[v][i];
            }
        }
    }
    for (int i = maxlog - 1; i >= 0; --i) {
        if (lca[u][i] != lca[v][i]) {
            ans = min(ans, mini[u][i]);
            u = lca[u][i];
            ans = min(ans, mini[v][i]);
            v = lca[v][i];
        }
    }
    if (u != v) {
        ans = min(ans, mini[u][0]);
        ans = min(ans, mini[v][0]);
    }
    return ans;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    g.resize(n);
    tin.resize(n, 0);
    tout.resize(n, 0);
    cost.resize(n, inf);
    d.resize(n, 0);
    for (int i = 1; i < n; ++i) {
        int p, y;
        cin >> p >> y;
        p--;
        g[p].push_back(i);
        cost[i] = y;
    }
    dfs(0, -1);
    lca.resize(n, vector <int> (maxlog, -1));
    mini.resize(n, vector <int> (maxlog, inf));
    count(0, -1);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        cout << query(u, v) << endl;
    }
    return 0;
}
