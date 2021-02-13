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
            g[u].push_back({u, v, c, (int) g[u].size(), back_u});
            g[v].push_back({v, u, 0, (int) g[v].size(), back_v});
        }
    }

    vector<edge> bfs() {
        queue<int> q;
        q.push(0);
        vector<bool> used(n, false);
        vector<edge> p(n, {-1, -1, -1, -1, -1});
        used[0] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (edge e : g[u]) {
                if (e.c > 0 && !used[e.to]) {
                    used[e.to] = true;
                    p[e.to] = e;
                    q.push(e.to);
                }
            }
        }
        vector<edge> path;
        int curr = n - 1;
        while (p[curr].c != -1) {
            path.push_back(p[curr]);
            curr = p[curr].from;
        }
        reverse(path.begin(), path.end());
        return path;
    }

    ll edmonds_karp() {
        vector<vector<ll>> f(n);
        for (int i = 0; i < n; ++i) {
            f[i].resize(g[i].size());
        }
        while (true) {
            vector<edge> path = bfs();
            if (path.empty()) {
                break;
            }
            ll c_min = 1e9;
            for (edge &e : path) {
                c_min = min(c_min, e.c);
            }
            for (edge &e : path) {
                f[e.from][e.id] += c_min;
                g[e.from][e.id].c -= c_min;
                f[e.to][e.back_id] = -f[e.from][e.id];
                g[e.to][e.back_id].c += c_min;
            }
        }
        ll ans = 0;
        for (ll w : f[0]) {
            ans += w;
        }
        return ans;
    }
};

int main() {
    fastio;
    int n;
    cin >> n;
    graph g(n);
    g.read();
    cout << g.edmonds_karp();
    return 0;
}
