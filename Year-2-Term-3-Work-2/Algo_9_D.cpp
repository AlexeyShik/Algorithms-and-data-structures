#include <iostream>
#include <vector>
#include <set>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;

const ll inf = 1e12;

int main() {
    fastio;
    int n, m;
    cin >> n >> m;
    vector<vector<pll>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    vector<bool> used(n, false);
    vector<ll> dist(n, inf);
    set<pll> q;
    q.insert({0, 0});
    dist[0] = 0;
    while (!q.empty()) {
        int u = (int) q.begin()->second;
        q.erase(q.begin());
        used[u] = true;
        for (pll edge : g[u]) {
            int v = (int) edge.first;
            ll w = edge.second;
            if (!used[v] && dist[v] > dist[u] + w) {
                auto it = q.find({dist[v], v});
                if (it != q.end()) {
                    q.erase(it);
                }
                dist[v] = dist[u] + w;
                q.insert({dist[v], v});
            }
        }
    }
    for (ll x : dist) {
        cout << (x == inf ? -1 : x) << ' ';
    }
    return 0;
}
