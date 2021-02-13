#include <iostream>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <cassert>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fileio freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9;
const ll inf = 1e17;

struct edge {
    int from;
    int to;
    ll c;
    ll flow;
    int id;
    int back_id;
};

struct graph {
    int n;
    int s;
    int t;
    int len;
    vector<vector<edge>> g;

    explicit graph(int n) {
        this->n = n;
        len = 2 * n + 2;
        s = 2 * n;
        t = 2 * n + 1;
        g.resize(len);
    }

    void build(vector<pair<ll, pair<int, int>>> &edges, ll bound) {
        for (auto pp : edges) {
            if (pp.first < bound) {
                continue;
            }
            int u = pp.second.first;
            int v = pp.second.second;
            int back_u = g[v].size();
            int back_v = g[u].size();
            g[u].push_back({u, v, 1, 0, (int) g[u].size(), back_u});
            g[v].push_back({v, u, 0, 0, (int) g[v].size(), back_v});
        }
        for (int v = 0; v < n; ++v) {
            int back_u = g[v].size();
            int back_v = g[s].size();
            g[s].push_back({s, v, 1, 0, (int) g[s].size(), back_u});
            g[v].push_back({v, s, 0, 0, (int) g[v].size(), back_v});
        }
        for (int u = n; u < 2 * n; ++u) {
            int back_u = g[t].size();
            int back_v = g[u].size();
            g[u].push_back({u, t, 1, 0, (int) g[u].size(), back_u});
            g[t].push_back({t, u, 0, 0, (int) g[t].size(), back_v});
        }
    }

    vector<ll> bfs_dinica(ll bound) {
        queue<int> q;
        q.push(s);
        vector<ll> dist(len, inf);
        dist[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (edge e : g[u]) {
                if (e.c - e.flow >= bound && dist[e.to] == inf) {
                    dist[e.to] = dist[e.from] + 1;
                    q.push(e.to);
                }
            }
        }
        return dist;
    }

    inline ll dfs_bloc(int u, ll c_min, vector<int> &ptr, vector<ll> &dist,
                       ll bound, vector<bool> &used) {
        if (u == t) {
            return c_min;
        }
        if (c_min < bound) {
            return 0;
        }
        used[u] = true;
        for (; ptr[u] < (int) g[u].size(); ++ptr[u]) {
            edge &e = g[u][ptr[u]];
            if (e.c - e.flow >= bound && dist[e.to] == dist[e.from] + 1 && !used[e.to]) {
                ll flow = dfs_bloc(e.to, min(c_min, e.c - e.flow), ptr, dist, bound, used);
                e.flow += flow;
                g[e.to][e.back_id].flow -= flow;
                if (flow > 0) {
                    return flow;
                }
            }
        }
        return 0;
    }

    ll dinica(ll bound) {
        while (true) {
            vector<ll> dist = bfs_dinica(bound);
            if (dist[t] == inf) {
                break;
            }
            vector<int> ptr(len, 0);
            vector<bool> used(len, false);
            while (dfs_bloc(s, inf, ptr, dist, bound, used) != 0) {
                used.assign(len, false);
            }
        }
        ll ans = 0;
        for (edge e : g[s]) {
            ans += e.flow;
        }
        return ans;
    }

    ll dinica() {
        ll bound = 1e9;
        ll ans = 0;
        while (bound > 0) {
            ans = max(ans, dinica(bound));
            bound /= 2;
        }
        return ans;
    }
};

int main() {
    fastio;
    int n;
    cin >> n;
    vector<pair<ll, pair<int, int>>> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ll x;
            cin >> x;
            edges.push_back({x, {i, j + n}});
        }
    }
    sort(edges.begin(), edges.end());
    int l = 0, r = edges.size();
    while (r - l > 1) {
        int m = (l + r) / 2;
        graph g(n);
        g.build(edges, edges[m].first);
        if (g.dinica() == n) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << edges[l].first;
    return 0;
}
