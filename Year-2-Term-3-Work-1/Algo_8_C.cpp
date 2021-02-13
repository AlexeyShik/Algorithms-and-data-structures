#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum color {
    WHITE, GRAY, BLACK
};

const int INF = 1e9 + 7;

inline void dfs(int u, vector<color> &used, vector<int> &order,
        vector<vector<pair<int, int>> > &g) {
    used[u] = BLACK;
    for (auto e : g[u]) {
        if (used[e.first] == WHITE) {
            dfs(e.first, used, order, g);
        }
    }
    order.push_back(u);
}

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s, --t;
    vector<vector<pair<int, int>> > g(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        g[u].push_back({v, w});
    }
    vector<color> used(n, WHITE);
    vector<int> order;
    for (int i = 0; i < n; ++i) {
        if (used[i] == WHITE) {
            dfs(i, used, order, g);
        }
    }
    vector<int> dp(n, INF);
    dp[t] = 0;
    for (int u : order) {
        for (auto e : g[u]) {
            if (dp[e.first] != INF) {
                dp[u] = min(dp[u], e.second + dp[e.first]);
            }
        }
    }
    if (dp[s] == INF) {
        cout << "Unreachable";
    } else {
        cout << dp[s];
    }
    return 0;
}
