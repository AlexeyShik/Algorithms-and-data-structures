#include <iostream>
#include <vector>
#include <algorithm>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
typedef long double ld;

const ll inf = 1e12 + 7;

int main() {
    fastio;
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> dist(n, vector<ll>(n, inf));
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        dist[u][v] = min(dist[u][v], (ll) w);
    }
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            if (i != k) {
                for (int j = 0; j < n; ++j) {
                    if (j != k && i != j) {
                        if (dist[i][k] != inf && dist[k][j] != inf) {
                            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << dist[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}
