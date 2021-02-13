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
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9;
const ll inf = 1e17;

struct edge {
    int from;
    int to;
    ll l;
    ll c;
    ll flow;
    int id;
    int back_id;
};

struct graph {
    int n;
    int m;
    int s;
    int t;
    int len;
    vector<vector<edge>> g;
    vector<vector<edge>> decomp;
    vector<ll> flows;
    map<pair<int, int>, int> edge_to_id;

    explicit graph(int n) {
        this->n = n;
        len = 3 * n + 2;
        g.resize(len);
    }

    void read() {
        s = len - 2;
        t = len - 1;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int u, v;
            ll l, c;
            cin >> u >> v >> l >> c;
            --u, --v;
            int back_u = g[v].size();
            int back_v = g[u].size();
            edge_to_id[{u, g[u].size()}] = i;
            edge_to_id[{v, g[v].size()}] = -1;
            g[u].push_back({u, v, l, c - l, 0, (int) g[u].size(), back_u});
            g[v].push_back({v, u, 0, 0, 0, (int) g[v].size(), back_v});

            back_u = g[t].size();
            int back_t = g[u].size();
            edge_to_id[{u, g[u].size()}] = -1;
            edge_to_id[{t, g[t].size()}] = -1;
            g[u].push_back({u, t, 0, l, 0, (int) g[u].size(), back_u});
            g[t].push_back({t, u, 0, 0, 0, (int) g[t].size(), back_t});

            int back_s = g[v].size();
            back_v = g[s].size();
            edge_to_id[{s, g[s].size()}] = -1;
            edge_to_id[{v, g[v].size()}] = -1;
            g[s].push_back({s, v, 0, l, 0, (int) g[s].size(), back_s});
            g[v].push_back({v, s, 0, 0, 0, (int) g[v].size(), back_v});
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

    void print() {
        for (edge e : g[s]) {
            if (e.c != e.flow) {
                cout << "NO";
                return;
            }
        }
        cout << "YES" << endl;
        vector<ll> flow(m);
        for (int i = 0; i < n; ++i) {
            for (edge e : g[i]) {
                if (edge_to_id[{i, e.id}] != -1) {
                    flow[edge_to_id[{i, e.id}]] = e.flow + e.l;
                }
            }
        }
        for (ll x : flow) {
            cout << x << endl;
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
    g.print();
    return 0;
}
