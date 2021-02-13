#include <iostream>
#include <vector>
#include <set>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;
typedef long double ld;

const ll inf = 1e12 + 7;

struct edge {
    int from;
    int to;
    ll w;

    bool operator<(const edge &other) const {
        return w < other.w || (w == other.w && (to < other.to
                                                || (to == other.to && from < other.from)));
    }
};

inline int get(int u, vector<int> &dsu) {
    return dsu[u] = u == dsu[u] ? u : get(dsu[u], dsu);
}

void join(int u, int v, vector<int> &dsu, vector<ll> &add, vector<set<edge>> &rg) {
    u = get(u, dsu);
    v = get(v, dsu);
    if (u == v) {
        return;
    }
    if (rg[u].size() > rg[v].size()) {
        swap(u, v);
    }
    while (!rg[u].empty()) {
        const edge e = *rg[u].begin();
        if (e.to != v) {
            rg[v].insert({v, e.to, e.w + add[u] - add[v]});
        }
        rg[u].erase(rg[u].begin());
    }
    dsu[u] = v;
}

inline void dfs(int u, vector<int> &used, vector<set<edge>> &g) {
    used[u] = 1;
    for (const edge &v : g[u]) {
        if (used[v.to] == 0) {
            dfs(v.to, used, g);
        }
    }
}

int main() {
    fastio;
    int n, m;
    cin >> n >> m;
    vector<set<edge>> g(n), rg(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u, --v;
        g[u].insert({u, v, w});
        rg[v].insert({v, u, w});
    }
    vector<int> used(n, 0);
    dfs(0, used, g);
    for (bool b : used) {
        if (b == 0) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES\n";
    ll ans = 0;
    used.assign(n, 0);
    vector<int> dsu(n), prev(n, -1);
    vector<ll> add(n, 0);
    for (int i = 0; i < n; ++i) {
        dsu[i] = i;
    }
    for (int i = 0; i < n; ++i) {
        int u = get(i, dsu);
        while (u != get(0, dsu)) {
            used[u] = i;
            while (!rg[u].empty() && get(rg[u].begin()->to, dsu) == u) {
                rg[u].erase(rg[u].begin());
            }
            const edge e = *rg[u].begin();
            ll curr = e.w + add[u];
            add[u] -= curr;
            ans += curr;
            int to = get(e.to, dsu);
            if (to == get(0, dsu)) {
                int v = u;
                while (v != -1) {
                    join(v, 0, dsu, add, rg);
                    v = prev[v];
                }
                break;
            }
            if (used[to] == i) {
                vector<int> cycle;
                int v = u;
                int parent = prev[to];
                while (v != parent) {
                    cycle.push_back(v);
                    v = prev[v];
                }
                for (int t = 1; t < (int) cycle.size(); ++t) {
                    join(cycle[t - 1], cycle[t], dsu, add, rg);
                }
                prev[get(to, dsu)] = parent;
                u = get(u, dsu);
            } else {
                prev[to] = u;
                u = to;
            }
        }
    }
    cout << ans;
    return 0;
}
