#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

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

vector<pair<int, int>> path;
vector<vector<pair<int, int>>> g;
vector<int> first;
vector<bool> used;

void euler(int u) {
    while (first[u] != (int) g[u].size()) {
        if (used[g[u][first[u]].first]) {
            ++first[u];
            continue;
        }
        auto e = g[u][first[u]++];
        used[e.first] = true;
        euler(e.second);
        path.emplace_back(e.first, e.second);
    }
}

int main() {
    fastio;
    int n, m = 0, k;
    cin >> n >> k;
    g.resize(n);
    set<pair<int, int>> additional;
    vector<pair<int, int>> edges;
    vector<int> pw(n, 0);
    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        edges.emplace_back(u, v);
        g[u].push_back({m, v});
        g[v].push_back({m, u});
        ++m;
        ++pw[u];
        ++pw[v];
    }
    int s = -1;
    for (int u = 0; u < n; ++u) {
        if (pw[u] % 2 == 1 && s == -1) {
            s = u;
        } else if (pw[u] % 2 == 1) {
            additional.insert({m, u});
            additional.insert({m, s});
            g[s].push_back({m, u});
            g[u].push_back({m, s});
            edges.emplace_back(u, s);
            ++pw[u];
            ++pw[s];
            ++m;
            s = -1;
        }
    }
    used.resize(m, false);
    first.resize(n);
    euler(0);
    reverse(path.begin(), path.end());
    cout << max(1, (int) additional.size() / 2) << endl;
    vector<vector<int>> paths;
    int prev = 0;
    for (int i = 0; i < (int) path.size(); ++i) {
        if (additional.find(path[i]) != additional.end()) {
            paths.emplace_back();
            for (int j = prev; j < i; ++j) {
                paths[paths.size() - 1].push_back(path[j].second);
            }
            prev = i;
        }
    }
    vector<int> fi;
    if (additional.empty()) {
        int id = path[prev].first;
        auto e = edges[id];
        int v = (e.second == path[prev].second ? e.first : e.second);
        fi.push_back(v);
    }
    for (int i = prev; i < (int) path.size(); ++i) {
        fi.push_back(path[i].second);
    }
    if (!paths.empty()) {
        for (auto &p : paths[0]) {
            fi.push_back(p);
        }
    } else {
        paths.resize(1);
    }
    paths[0] = fi;
    for (auto &p : paths) {
        if (p.size() == 1) {
            cout << p[0] + 1 << ' ' << p[0] + 1 << ' ';
        } else {
            for (int x : p) {
                cout << x + 1 << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}
