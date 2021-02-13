#include <iostream>
#include <vector>
#include <algorithm>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;

const ll inf = 1e12;

int main() {
    fastio;
    int n, s, f;
    cin >> n >> s >> f;
    --s, --f;
    vector<vector<pll>> g(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ll x;
            cin >> x;
            if (x != -1 && i != j) {
                g[i].push_back({j, x});
            }
        }
    }
    vector<bool> used(n, false);
    vector<ll> dist(n, inf);
    dist[s] = 0;
    for (int i = 0; i < n; ++i) {
        ll min_dist = inf;
        int arg_min = -1;
        for (int j = 0; j < n; ++j) {
            if (dist[j] < min_dist && !used[j]) {
                min_dist = dist[j];
                arg_min = j;
            }
        }
        if (arg_min == -1) {
            break;
        }
        used[arg_min] = true;
        for (pll edge : g[arg_min]) {
            dist[(int) edge.first] = min(dist[(int) edge.first], dist[arg_min] + edge.second);
        }
    }
    cout << (dist[f] == inf ? -1 : dist[f]);
    return 0;
}
