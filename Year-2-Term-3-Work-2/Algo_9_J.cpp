#include <iostream>
#include <vector>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
typedef long double ld;

const ll inf = 1e12 + 7;



struct edge {
    int from;
    int to;
    ll w;
};

enum color {
    WHITE, BLACK
};

inline void dfs(int u, vector<color> &used, vector<vector<edge> > &g) {
    used[u] = BLACK;
    for (edge v : g[u]) {
        if (used[v.to] == WHITE) {
            dfs(v.to, used, g);
        }
    }
}

ll solve(int n, vector<edge> &edges) {
    vector<ll> min_edge(n, inf);
    vector<int> min_id(n, -1);
    for (int i = 0; i < (int)edges.size(); ++i) {
        edge e = edges[i];
        if (min_edge[e.to] > e.w) {
            min_edge[e.to] = e.w;
            min_id[e.to] = i;
        }
    }
    ll ans = 0;
    for (int i = 1; i < n; ++i) {
        ans += min_edge[i];
    }
    for (edge &e : edges) {
        e.w -= min_edge[e.to];
    }
    vector<int> used(n, 0);
    vector<bool> on_cycle(n, false);
    bool was_cycle = false;
    for (int i = 1; i < n; ++i) {
        int j = i;
        while (j != 0 && used[j] == 0) {
            used[j] = i;
            j = edges[min_id[j]].from;
        }
        if (j != 0 && used[j] == i) {
            was_cycle = true;
            int begin = j;
            j = edges[min_id[j]].from;
            on_cycle[begin] = true;
            while (j != begin) {
                on_cycle[j] = true;
                j = edges[min_id[j]].from;
            }
            break;
        }
    }
    if (was_cycle) {
        vector<int> id(n);
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (!on_cycle[i]) {
                id[i] = cnt++;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (on_cycle[i]) {
                id[i] = cnt;
            }
        }
        vector<edge> new_edges;
        for (edge e : edges) {
            int u = id[e.from];
            int v = id[e.to];
            if (u == v) {
                continue;
            }
            new_edges.push_back({u, v, e.w});
        }
        ans += solve(cnt + 1, new_edges);
    }
    return ans;
}

int main() {
    fastio;
    int n, m;
    cin >> n >> m;
    vector<edge> edges;
    vector<vector<edge>> dg(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        if (u == v || v == 1) {
            continue;
        }
        --u, --v;
        edges.push_back({u, v, w});
        dg[u].push_back({u, v, w});
    }
    vector<color> used(n, WHITE);
    dfs(0, used, dg);
    for (bool b : used) {
        if (!b) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES\n" << solve(n, edges);
    return 0;
}
