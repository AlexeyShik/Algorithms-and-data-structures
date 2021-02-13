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
    vector<vector<int> > g(2 * n), rg(2 * n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        bool negu = u < 0;
        bool negv = v < 0;
        bool negw = w < 0;
        int gu = 2 * (abs(u) - 1) + negu;
        int gv = 2 * (abs(v) - 1) + negv;
        int gw = 2 * (abs(w) - 1) + negw;
        int nu = gu ^1;
        int nv = gv ^1;
        int nw = gw ^1;
        g[nu].push_back(gv);
        g[nv].push_back(gu);
        rg[gv].push_back(nu);
        rg[gu].push_back(nv);
        g[nu].push_back(gw);
        g[nw].push_back(gu);
        rg[gw].push_back(nu);
        rg[gu].push_back(nw);
        g[nv].push_back(gw);
        g[nw].push_back(gv);
        rg[gw].push_back(nv);
        rg[gv].push_back(nw);
    }
    vector<color> used(2 * n, WHITE);
    vector<int> order;
    for (int i = 0; i < 2 * n; ++i) {
        if (used[i] == WHITE) {
            dfs(i, used, order, g);
        }
    }
    reverse(order.begin(), order.end());
    used.assign(2 * n, WHITE);
    vector<int> comp(2 * n);
    for (int elem : order) {
        if (used[elem] == WHITE) {
            ++curr_component;
            scc(elem, used, comp, rg);
        }
    }
    for (int i = 0; i < 2 * n; i += 2) {
        if (comp[i] == comp[i + 1]) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES" << endl;
    for (int i = 0; i < 2 * n; i += 2) {
        cout << (comp[i] < comp[i + 1] ? -(i / 2) - 1 : (i / 2) + 1) << ' ';
    }
    return 0;
}
