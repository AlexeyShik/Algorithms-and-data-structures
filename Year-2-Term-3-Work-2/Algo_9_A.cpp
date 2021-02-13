#include <iostream>
#include <vector>
#include <queue>

#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> dist(n, 0);
    vector<bool> used(n, false);
    queue<pii > q;
    q.push({0, 0});
    while (!q.empty()) {
        int u = q.front().first;
        int d = q.front().second;
        q.pop();
        used[u] = true;
        for (int v : g[u]) {
            if (!used[v]) {
                dist[v] = dist[u] + 1;
                used[v] = true;
                q.push({v, d + 1});
            }
        }
    }
    for (int x : dist) {
        cout << x << ' ';
    }
    return 0;
}
