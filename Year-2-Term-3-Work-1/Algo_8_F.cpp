#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum color {
    WHITE, BLACK
};

inline void dfs(int u, vector<color> &used, vector<int> &order, vector<vector<int> > &g) {
    used[u] = BLACK;
    for (int v : g[u]) {
        if (used[v] == WHITE) {
            dfs(v, used, order, g);
        }
    }
    order.push_back(u);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
    }
    vector<color> used(n, WHITE);
    vector<int> order;
    for (int i = 0; i < n; ++i) {
        if (used[i] == WHITE) {
            dfs(i, used, order, g);
        }
    }
    vector<int> dp(n, -1);
    reverse(order.begin(), order.end());
    dp[order[0]] = 1;
    for (int u : order) {
        for (int v : g[u]) {
            if (dp[u] != -1) {
                dp[v] = max(dp[v], dp[u] + 1);
            }
        }
    }
    cout << (dp[order[n - 1]] == n ? "YES" : "NO");
    return 0;
}
