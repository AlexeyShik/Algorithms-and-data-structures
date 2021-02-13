#include <iostream>
#include <vector>

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
    int n, m, s;
    cin >> n >> m >> s;
    --s;
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
    vector <bool> win(n);
    for (int u : order) {
        for (int v : g[u]) {
            if (!win[v]) {
                win[u] = true;
            }
        }
    }
    cout << (win[s] ? "First" : "Second") << " player wins";
    return 0;
}
