#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
const ll inf = 1e17;

int t;
vector<vector<pair<pair<int, int>, pair<ll, ll>>>> g;
vector<int> dist;
vector<int> ptr;

void dfs_topsort(int u, vector<int> &order, vector<bool> &used) {
    used[u] = true;
    for (auto pp : g[u]) {
        if (!used[pp.first.second]) {
            dfs_topsort(pp.first.second, order, used);
        }
    }
    order.push_back(u);
}

int main() {
    int n, m, l, s = 0;
    fastio;
    cin >> n >> m >> l;
    map<pair<int, int>, int> edge_to_id;
    g.resize(n);
    ptr.resize(n);
    dist.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> dist[i];
        if (dist[i] == 1) {
            s = i;
        }
        if (dist[i] == l) {
            t = i;
        }
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        --u, --v;
        edge_to_id[{u, g[u].size()}] = i;
        g[u].push_back({{u, v}, {c, 0L}});
    }
    vector<int> order;
    vector<bool> used(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs_topsort(i, order, used);
        }
    }
    reverse(order.begin(), order.end());
    vector<ll> ans(m);
    vector<bool> block(n, false);
    ll flow = -1;
    while (flow != 0) {
        vector<ll> p(n, 0);
        p[s] = inf;
        vector<vector<pair<pair<pair<int, int>, pair<ll, ll>>, pair<ll, int>>>> fin(n);
        for (int u : order) {
            if (block[u]) {
                continue;
            }
            for (int i = 0; i < (int) g[u].size(); ++i) {
                auto &e = g[u][i];
                if (e.second.first - e.second.second > 0 && !block[e.first.second]) {
                    ll curr = min(p[u], e.second.first - e.second.second);
                    p[e.first.second] += curr;
                    p[u] -= curr;
                    e.second.second += curr;
                    fin[e.first.second].push_back({e, {curr, i}});
                }
            }
        }
        flow = p[t];
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            if (u == t || u == s || block[u]) {
                continue;
            }
            if (p[u] > 0) {
                block[u] = true;
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            if (u == t || u == s) {
                continue;
            }
            while (p[u] > 0) {
                auto &fb = fin[u].back();
                int from = fb.first.first.first;
                ll curr = min(fb.second.first, p[u]);
                g[fb.first.first.first][fb.second.second].second.second -= curr;
                p[u] -= curr;
                p[from] += curr;
                fin[u].pop_back();
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int) g[i].size(); ++j) {
            ans[edge_to_id[{g[i][j].first.first, j}]] = g[i][j].second.second;
        }
    }
    for (ll x : ans) {
        cout << x << endl;
    }
    return 0;
}
