#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum color {
    WHITE, GRAY, BLACK
};

inline bool dfs(int u, vector<color> &used, vector<int> &order, vector<vector<int> > &g) {
    used[u] = GRAY;
    for (int v : g[u]) {
        if (used[v] == GRAY || (used[v] == WHITE && !dfs(v, used, order, g))) {
            return false;
        }
    }
    used[u] = BLACK;
    order.push_back(u);
    return true;
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
        if (used[i] == WHITE && !dfs(i, used, order, g)) {
            cout << -1;
            return 0;
        }
    }
    reverse(order.begin(), order.end());
    for (int elem : order) {
        cout << elem + 1 << ' ';
    }
    return 0;
}
