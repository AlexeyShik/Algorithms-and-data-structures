#include <iostream>
#include <vector>
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
    int n, s = -1, f = -1;
    cin >> n;
    int m = 0;
    g.resize(n);
    for (int u = 0; u < n; ++u) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v;
            --v;
            if (u < v) {
                g[u].push_back({m, v});
                g[v].push_back({m, u});
                ++m;
            }
        }
        if (k % 2 == 1 && s == -1) {
            s = u;
        } else if (k % 2 == 1 && f == -1) {
            f = u;
        }  else if (k % 2 == 1) {
            cout << -1;
            return 0;
        }
    }
    if (s == -1 && f != -1) {
        cout << -1;
        return 0;
    }
    used.resize(m, false);
    first.resize(n);
    euler(s == -1 ? 0 : s);
    cout << path.size() << endl;
    reverse(path.begin(), path.end());
    cout << path[0].first + 1 << ' ';
    for (auto pp : path) {
        cout << pp.second + 1 << ' ';
    }
    return 0;
}
