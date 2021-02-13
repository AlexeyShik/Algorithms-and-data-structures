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
    ll w;
    int id;
    int back_id;
};

struct graph {
    int n;
    int s;
    int t;
    int len;
    vector<vector<edge>> g;
    constexpr static edge Null = {-1, -1, -1, -1, -1, -1, -1};

    explicit graph(int n) {
        this->n = n;
        s = 2 * n;
        t = 2 * n + 1;
        len = 2 * n + 2;
        g.resize(len);
    }

    void build(vector<vector<ll>> &cost) {
        for (int v = 0; v < n; ++v) {
            int back_u = g[v].size();
            int back_v = g[s].size();
            g[s].push_back({s, v, 1, 0, 0, (int) g[s].size(), back_u});
            g[v].push_back({v, s, 0, 0, 0, (int) g[v].size(), back_v});
        }
        for (int u = n; u < 2 * n; ++u) {
            int back_u = g[t].size();
            int back_v = g[u].size();
            g[u].push_back({u, t, 1, 0, 0, (int) g[u].size(), back_u});
            g[t].push_back({t, u, 0, 0, 0, (int) g[t].size(), back_v});
        }
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                int back_u = g[v + n].size();
                int back_v = g[u].size();
                g[u].push_back({u, v + n, 1, 0, cost[u][v], (int) g[u].size(), back_u});
                g[v + n].push_back({v + n, u, 0, 0, -cost[u][v], (int) g[v + n].size(), back_v});
            }
        }
    }

    pair<vector<ll>, vector<edge>> dijkstra(vector<ll> &phi) {
        vector<ll> dist(len, inf);
        vector<bool> used(len, false);
        vector<edge> prev(len, Null);
        dist[s] = 0;
        int u = s;
        while (u != -1 && dist[u] != inf) {
            used[u] = true;
            for (edge &e : g[u]) {
                if (e.c > e.flow && dist[e.from] + (e.w + phi[e.from] - phi[e.to]) < dist[e.to]) {
                    dist[e.to] = dist[e.from] + (e.w + phi[e.from] - phi[e.to]);
                    prev[e.to] = e;
                }
            }
            u = -1;
            for (int v = 0; v < len; ++v) {
                if ((u == -1 || dist[u] > dist[v]) && !used[v]) {
                    u = v;
                }
            }
        }
        return {dist, prev};
    }


    vector<ll> ford_bellman() {
        vector<ll> dist(len, inf);
        dist[s] = 0;
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                for (edge &e : g[j]) {
                    if (e.c > e.flow && dist[e.from] + e.w < dist[e.to] && dist[e.from] != inf) {
                        dist[e.to] = dist[e.from] + e.w;
                    }
                }
            }
        }
        return dist;
    }

    void min_cost_flow() {
        ll cost = 0;
        vector<ll> phi = ford_bellman();
        while (true) {
            auto tmp = dijkstra(phi);
            vector<ll> dist = tmp.first;
            vector<edge> prev = tmp.second;
            vector<edge> path;
            int v = t;
            while (prev[v].c != -1) {
                path.push_back(prev[v]);
                v = prev[v].from;
            }
            reverse(path.begin(), path.end());
            if (path.empty()) {
                break;
            }
            ll flow = inf;
            for (edge &e : path) {
                flow = min(flow, e.c - e.flow);
            }
            for (edge &e : path) {
                cost += flow * e.w;
                g[e.from][e.id].flow += flow;
                g[e.to][e.back_id].flow -= flow;
            }
            for (int i = 0; i < len; ++i) {
                phi[i] += dist[i];
            }
        }
        cout << cost << endl;
        for (int i = 0; i < n; ++i) {
            for (edge &e : g[i]) {
                if (e.c == e.flow) {
                    cout << e.from + 1 << ' ' << e.to + 1 - n << endl;
                }
            }
        }
    }
};

int main() {
    fastio;
    int n;
    cin >> n;
    graph g(n);
    vector<vector<ll>> cost(n, vector<ll> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cost[i][j];
        }
    }
    g.build(cost);
    g.min_cost_flow();
    return 0;
}
