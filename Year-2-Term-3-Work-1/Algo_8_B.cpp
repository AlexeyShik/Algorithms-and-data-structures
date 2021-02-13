#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum color {
    WHITE, BLACK
};

int curr_component = 0;

inline void dfs(int u, vector<color> &used, vector<int> &order, vector<vector<int> > &g) {
    used[u] = BLACK;
    for (int v : g[u]) {
        if (used[v] == WHITE) {
            dfs(v, used, order, g);
        }
    }
    order.push_back(u);
}

inline void scc(int u, vector<color> &used, vector<int> &comp, vector<vector<int>> &rg) {
    used[u] = BLACK;
    comp[u] = curr_component;
    for (int v : rg[u]) {
        if (used[v] == WHITE) {
            scc(v, used, comp, rg);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > g(n), rg(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    vector<color> used(n, WHITE);
    vector<int> order;
    for (int i = 0; i < n; ++i) {
        if (used[i] == WHITE) {
            dfs(i, used, order, g);
        }
    }
    reverse(order.begin(), order.end());
    used.assign(n, WHITE);
    vector<int> comp(n);
    for (int elem : order) {
        if (used[elem] == WHITE) {
            ++curr_component;
            scc(elem, used, comp, rg);
        }
    }
    cout << curr_component << endl;
    for (int elem : comp) {
        cout << elem << ' ';
    }
    return 0;
}
