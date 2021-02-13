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
    int n;
    cin >> n;
    vector<int> col(n);
    for (int i = 0; i < n; ++i) {
        cin >> col[i];
    }
    vector<bool> was_wire(n, false);
    vector<pair<int, bool>> socket;
    vector<vector<int>> connect_to(n, vector<int> (2));
    for (int i = 0; i < 2 * n; ++i) {
        int wire;
        cin >> wire;
        --wire;
        socket.emplace_back(wire, was_wire[wire]);
        connect_to[wire][was_wire[wire]] = i;
        was_wire[wire] = true;
    }
    vector<vector<int> > g(2 * n), rg(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        auto su = socket[i];
        auto sv = socket[(i + 1) % (2 * n)];
        if (col[su.first] == col[sv.first]) {
            int u = su.first * 2 + !su.second, v = sv.first * 2 + sv.second;
            int nu = u ^1;
            int nv = v ^1;
            g[u].push_back(v);
            g[nv].push_back(nu);
            rg[v].push_back(u);
            rg[nu].push_back(nv);
        }
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
    vector<int> in_ans(n);
    for (int i = 0; i < 2 * n; i += 2) {
        int wire = i / 2;
        in_ans[wire] = connect_to[wire][comp[i] > comp[i + 1]];
    }
    for (int i = 0; i < n; ++i) {
        cout << in_ans[i] + 1 << ' ';
    }
    return 0;
}
