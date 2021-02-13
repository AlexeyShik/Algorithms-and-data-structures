#include <iostream>
#include <vector>
#include <map>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;

const ll inf = INT64_MAX / 2;

int main() {
    fastio;
    int n, m, s;
    cin >> n >> m >> s;
    --s;
    vector<pair<pii, ll>> g;
    map<pii, ll> mg;
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        --u, --v;
        if (mg.find({u, v}) == mg.end()) {
            mg[{u, v}] = w;
        } else {
            mg[{u, v}] = min(mg[{u, v}], (ll) w);
        }
    }
    g.reserve(mg.size());
    for (auto elem : mg) {
        g.emplace_back(elem.first, elem.second);
    }
    vector<ll> dist(n, inf);
    vector<int> prev(n, -1);
    dist[s] = 0;
    for (int i = 0; i < n; ++i) {
        for (auto edge : g) {
            int u = edge.first.first;
            int v = edge.first.second;
            ll w = edge.second;
            if (dist[u] != inf && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
            }
        }
    }
    vector<bool> on_cycle(n, false);
    for (auto edge : g) {
        int u = edge.first.first;
        int v = edge.first.second;
        ll w = edge.second;
        if (dist[u] != inf && dist[u] + w < dist[v]) {
            for (int i = 0; i < n; ++i) {
                v = prev[v];
            }
            int tmp = v;
            on_cycle[tmp] = true;
            while (prev[tmp] != v) {
                tmp = prev[tmp];
                on_cycle[tmp] = true;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (auto edge : g) {
            int u = edge.first.first;
            int v = edge.first.second;
            if (on_cycle[u]) {
                on_cycle[v] = true;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (dist[i] == inf) {
            cout << '*' << endl;
        } else if (on_cycle[i]) {
            cout << "-" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }
    return 0;
}
