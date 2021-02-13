#include <iostream>
#include <vector>

using namespace std;

inline bool dfs(int u, vector<int> &used, vector<vector<int> > &g, int color) {
    used[u] = color;
    for (int v : g[u]) {
        if (used[v] == color || (used[v] == -1 && !dfs(v, used, g, 1 - color))) {
            return false;
        }
    }
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
        g[v].push_back(u);
    }
    vector<int> used(n, -1);
    for (int i = 0; i < n; ++i) {
        if (used[i] == -1 && !dfs(i, used, g, 0)) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
    return 0;
}
