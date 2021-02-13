#include <iostream>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <unordered_map>
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

struct task {
    ll l;
    ll r;
    ll w;
    int i;
};

struct edge {
    int from;
    int to;
    ll c;
    ll flow;
    ll w;
    int id;
    int back_id;
    int i;
};

struct graph {
    int n;
    int k;
    int s;
    int t;
    int t_size = 0;
    vector<vector<edge>> g;
    constexpr static edge Null = {-1, -1, -1, -1, -1, -1, -1, -1};

    explicit graph(int n, int k) {
        this->n = n + 2;
        this->k = k;
        s = n;
        t = n + 1;
        g.resize(n + 2);
    }

    void build(vector<task> &tasks, vector<ll> &times) {
        t_size = tasks.size();
        int u = s;
        int v = (int) times[0];
        int back_u = g[v].size();
        int back_v = g[u].size();
        g[u].push_back({u, v, k, 0, 0, (int) g[u].size(), back_u, -1});
        g[v].push_back({v, u, 0, 0, 0, (int) g[v].size(), back_v, -1});
        for (int i = 1; i < (int) times.size(); ++i) {
            u = (int) times[i - 1];
            v = (int) times[i];
            back_u = g[v].size();
            back_v = g[u].size();
            g[u].push_back({u, v, k, 0, 0, (int) g[u].size(), back_u, -1});
            g[v].push_back({v, u, 0, 0, 0, (int) g[v].size(), back_v, -1});
        }
        u = (int) times.back();
        v = t;
        back_u = g[v].size();
        back_v = g[u].size();
        g[u].push_back({u, v, k, 0, 0, (int) g[u].size(), back_u, -1});
        g[v].push_back({v, u, 0, 0, 0, (int) g[v].size(), back_v, -1});
        for (task &ts : tasks) {
            u = (int) ts.l;
            v = (int) ts.r;
            back_u = g[v].size();
            back_v = g[u].size();
            g[u].push_back({u, v, 1, 0, -ts.w, (int) g[u].size(), back_u, ts.i});
            g[v].push_back({v, u, 0, 0, ts.w, (int) g[v].size(), back_v, -1});
        }
    }

    pair<vector<ll>, vector<edge>> dijkstra(vector<ll> &phi) {
        vector<ll> dist(n, inf);
        vector<edge> prev(n, Null);
        dist[s] = 0;
        set<pair<ll, int>> q;
        q.insert({0, s});
        while (!q.empty()) {
            int u = q.begin()->second;
            q.erase(q.begin());
            for (edge &e : g[u]) {
                if (e.c > e.flow && dist[e.from] + (e.w + phi[e.from] - phi[e.to]) < dist[e.to]) {
                    q.erase({dist[e.to], e.to});
                    dist[e.to] = dist[e.from] + (e.w + phi[e.from] - phi[e.to]);
                    prev[e.to] = e;
                    q.insert({dist[e.to], e.to});
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

    void print_ans() {
        vector<int> ans(t_size);
        for (int i = 0; i < n; ++i) {
            for (edge &e : g[i]) {
                if (e.i != -1 && e.flow == e.c) {
                    ans[e.i] = 1;
                }
            }
        }
        for (int x : ans) {
            cout << x << ' ';
        }
    }
};

int main() {
    fastio;
    int n, k;
    cin >> n >> k;
    vector<task> tasks;
    set<ll> times;
    for (int i = 0; i < n; ++i) {
        ll s, t, c;
        cin >> s >> t >> c;
        times.insert(s);
        times.insert(s + t);
        tasks.push_back({s, s + t, c, i});
    }
    unordered_map<ll, int> compress;
    vector<ll> vtimes;
    int id = 0;
    for (ll x : times) {
        compress[x] = id++;
        vtimes.push_back(compress[x]);
    }
    for (task &t : tasks) {
        t.l = compress[t.l];
        t.r = compress[t.r];
    }
    graph g(times.size(), k);
    g.build(tasks, vtimes);
    g.min_cost_flow();
    g.print_ans();
    return 0;
}
