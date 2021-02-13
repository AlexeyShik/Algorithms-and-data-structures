#include <iostream>
#include <vector>

using namespace std;

enum color {
    WHITE, GRAY, BLACK
};

int curr_component = 0;

inline void dfs(int u, vector<color> &used, vector<int> &comp, vector<vector<int> > &g) {
    used[u] = GRAY;
    comp[u] = curr_component;
    for (int v : g[u]) {
        if (used[v] == WHITE) {
            dfs(v, used, comp, g);
        }
    }
    used[u] = BLACK;
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
    vector<color> used(n, WHITE);
    vector<int> comp(n);
    for (int i = 0; i < n; ++i) {
        if (used[i] == WHITE) {
            ++curr_component;
            dfs(i, used, comp, g);
        }
    }
    cout << curr_component << endl;
    for (int elem : comp) {
        cout << elem << ' ';
    }
    return 0;
}
