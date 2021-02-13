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
    int len;
    int k;
    int s;
    int t;
    vector<vector<edge>> g;
    constexpr static edge Null = {-1, -1, -1, -1, -1, -1, -1};
    vector<vector<ll>> cost;

    explicit graph(int n, int k) {
        this->n = n;
        this->k = k;
        len = 2 * n + 2;
        s = 2 * n;
        t = 2 * n + 1;
        g.resize(len);
        cost.resize(n,  vector<ll> (n));
    }

    void read() {
        for (int u = 0; u < n; ++u) {
            for (int v = n; v < 2 * n; ++v) {
                int back_u = g[v].size();
                int back_v = g[u].size();
                cin >> cost[u][v - n];
                g[u].push_back({u, v, 1, 0, cost[u][v - n], (int) g[u].size(), back_u});
                g[v].push_back({v, u, 0, 0, -cost[u][v - n], (int) g[v].size(), back_v});
            }
        }
        for (int v = 0; v < n; ++v) {
            int back_u = g[v].size();
            int back_v = g[s].size();
            g[s].push_back({s, v, k, 0, 0, (int) g[s].size(), back_u});
            g[v].push_back({v, s, 0, 0, 0, (int) g[v].size(), back_v});
        }
        for (int u = n; u < 2 * n; ++u) {
            int back_u = g[t].size();
            int back_v = g[u].size();
            g[u].push_back({u, t, k, 0, 0, (int) g[u].size(), back_u});
            g[t].push_back({t, u, 0, 0, 0, (int) g[t].size(), back_v});
        }
    }

    pair<vector<ll>, vector<edge>> dijkstra(vector<ll> &phi) {
        vector<ll> dist(len, inf);
        vector<edge> prev(len, Null);
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

    ll min_cost_flow() {
        ll ans = 0;
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
                ans += flow * e.w;
                g[e.from][e.id].flow += flow;
                g[e.to][e.back_id].flow -= flow;
            }
            for (int i = 0; i < n; ++i) {
                phi[i] += dist[i];
            }
        }
        return ans;
    }

    void find_k_match() {
        for (int i = 0; i < len; ++i) {
            for (edge &e : g[i]) {
                if (e.from < n && e.to >= n && e.to < 2 * n) {
                    if (e.flow != e.c) {
                        cost[e.from][e.to - n] = inf;
                    } else {
                        cost[e.from][e.to - n] = e.w;
                    }
                }
            }
        }
        for (int it = 0; it < k; ++it) {
            vector<int> mt = hungarian(cost);
            vector<int> ans(n + 1);
            for (int i = 1; i <= n; ++i) {
                cost[mt[i] - 1][i - 1] = inf;
                ans[mt[i]] = i;
            }
            for (int i = 1; i <= n; ++i) {
                cout << ans[i] << ' ';
            }
            cout << endl;
        }
    }

    static vector<int> hungarian(vector<vector<ll>> cost) {
        int n = cost.size();
        vector<ll> phi_r(n + 1), phi_c(n + 1);
        vector<int> prev(n + 1), mt(n + 1);
        for (int i = 1; i <= n; ++i) {
            mt[0] = i;
            int curr = 0;
            vector<ll> min_dist(n + 1, inf);
            vector<bool> used(n + 1, false);
            do {
                used[curr] = true;
                ll d = inf;
                int next = -1;
                for (int j = 1; j <= n; ++j) {
                    if (!used[j]) {
                        ll c = cost[mt[curr] - 1][j - 1] - phi_r[mt[curr]] - phi_c[j];
                        if (min_dist[j] > c) {
                            min_dist[j] = c;
                            prev[j] = curr;
                        }
                        if (d > min_dist[j]) {
                            next = j;
                            d = min_dist[j];
                        }
                    }
                }
                for (int j = 0; j <= n; ++j) {
                    if (used[j]) {
                        phi_r[mt[j]] += d;
                        phi_c[j] -= d;
                    } else {
                        min_dist[j] -= d;
                    }
                }
                curr = next;
            } while (mt[curr] != 0);
            do {
                int tmp = prev[curr];
                mt[curr] = mt[tmp];
                curr = tmp;
            } while (curr != 0);
        }
        return mt;
    }
};



int main() {
    fastio;
    int n, k;
    cin >> n >> k;
    graph g(n, k);
    g.read();
    cout << g.min_cost_flow() << endl;
    g.find_k_match();
    return 0;
}
