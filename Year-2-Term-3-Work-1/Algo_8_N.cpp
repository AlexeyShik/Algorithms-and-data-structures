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

bool check(int x, int n, vector<vector<pair<int, int>>> &g0) {
    curr_component = 0;
    vector<vector<int> > g(n), rg(n);
    for (int u = 0; u < n; ++u) {
        for (auto e : g0[u]) {
            if (e.second <= x) {
                g[u].push_back(e.first);
                rg[e.first].push_back(u);
            }
        }
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
    return curr_component == 1;
}

int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>> > g(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int t;
            cin >> t;
            if (i != j) {
                g[i].push_back({j, t});
            }
        }
    }
    int l = -1, r = 1e9;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (check(mid, n, g)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r;
    return 0;
}
