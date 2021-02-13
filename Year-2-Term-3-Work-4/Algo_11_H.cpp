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
    vector<vector<edge>> g;
    constexpr static edge Null = {-1, -1, -1, -1, -1, -1, -1};

    explicit graph(int n) {
        this->n = n;
        s = 0;
        t = n - 1;
        g.resize(n);
    }

    void read() {
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int u, v;
            ll c, w;
            cin >> u >> v >> c >> w;
            --u, --v;
            int back_u = g[v].size();
            int back_v = g[u].size();
            g[u].push_back({u, v, c, 0, w, (int) g[u].size(), back_u});
            g[v].push_back({v, u, 0, 0, -w, (int) g[v].size(), back_v});
        }
    }

    pair<vector<ll>, vector<edge>> dijkstra(vector<ll> &phi) {
        vector<ll> dist(n, inf);
        vector<bool> used(n, false);
        vector<edge> prev(n, Null);
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
            for (int v = 0; v < n; ++v) {
                if ((u == -1 || dist[u] > dist[v]) && !used[v]) {
                    u = v;
                }
            }
        }
        return {dist, prev};
    }


    vector<ll> ford_bellman() {
        vector<ll> dist(n, inf);
        dist[s] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (edge &e : g[j]) {
                    if (e.c > e.flow && dist[e.from] + e.w < dist[e.to] && dist[e.from] != inf) {
                        dist[e.to] = dist[e.from] + e.w;
                    }
                }
            }
        }
        return dist;
    }

    ll min_cost_flow() {
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
            for (int i = 0; i < n; ++i) {
                phi[i] += dist[i];
            }
        }
        return cost;
    }
};

int main() {
    fastio;
    int n;
    cin >> n;
    graph g(n);
    g.read();
    cout << g.min_cost_flow();
    return 0;
}
