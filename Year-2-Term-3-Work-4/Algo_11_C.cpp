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
    vector<vector<edge>> g;

    explicit graph(int n) {
        this->n = n;
        g.resize(n);
    }

    void read() {
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int u, v;
            ll c;
            cin >> u >> v >> c;
            --u, --v;
            int back_u = g[v].size();
            int back_v = g[u].size();
            g[u].push_back({u, v, c, 0, (int) g[u].size(), back_u});
            g[v].push_back({v, u, c, 0, (int) g[v].size(), back_v});
        }
    }

    vector<ll> bfs_dinica(ll bound) {
        queue<int> q;
        q.push(0);
        vector<ll> dist(n, inf);
        dist[0] = 0;
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
        if (u == n - 1) {
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
            if (dist[n - 1] == inf) {
                break;
            }
            vector<int> ptr(n, 0);
            vector<bool> used(n, false);
            while (dfs_bloc(0, inf, ptr, dist, bound, used) != 0) {
                used.assign(n, false);
            }
        }
        ll ans = 0;
        for (edge e : g[0]) {
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

    inline void dfs_cut(int u, vector<bool> &used) {
        used[u] = true;
        for (edge e : g[u]) {
            if (e.c - e.flow > 0 && !used[e.to]) {
                dfs_cut(e.to, used);
            }
        }
    }

    void print_cut() {
        vector<bool> used(n, false);
        dfs_cut(0, used);
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (used[i]) {
                ans.push_back(i);
            }
        }
        cout << ans.size() << endl;
        for (int x : ans) {
            cout << x + 1 << ' ';
        }
    }
};

int main() {
    fastio;
    int n;
    cin >> n;
    graph g(n);
    g.read();
    g.dinica();
    g.print_cut();
    return 0;
}
