#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

enum Color {
    WHITE, BLACK
};

int curr_component = 0;

inline void dfs(int u, vector<Color> &used, vector<int> &order, vector<vector<int> > &g) {
    used[u] = BLACK;
    for (int v : g[u]) {
        if (used[v] == WHITE) {
            dfs(v, used, order, g);
        }
    }
    order.push_back(u);
}

inline void scc(int u, vector<Color> &used, vector<int> &comp, vector<vector<int>> &rg) {
    used[u] = BLACK;
    comp[u] = curr_component;
    for (int v : rg[u]) {
        if (used[v] == WHITE) {
            scc(v, used, comp, rg);
        }
    }
}

int green(int x) {
    return 3 * x;
}

int red(int x) {
    return 3 * x + 1;
}

int blue(int x) {
    return 3 * x + 2;
}

int normal(int x) {
    return 2 * x;
}

int revert(int x) {
    return 2 * x + 1;
}

bool is_revert(int x) {
    return x % 2;
}

int unbox(int x) {
    return x / 2;
}

int get_color(int x) {
    return unbox(x) % 3;
}

int get_i(int x) {
    return unbox(x) / 3;
}

string solve(int n, vector<vector<int>> &gg, string &color) {
    curr_component = 0;
    int sz = 6 * n;
    vector<vector<int>> g(sz);
    for (int i = 0; i < n; ++i) {
        if (color[i] == 'R') {
            g[revert(green(i))].push_back(normal(blue(i)));
            g[revert(blue(i))].push_back(normal(green(i)));
            g[normal(green(i))].push_back(revert(blue(i)));
            g[normal(blue(i))].push_back(revert(green(i)));
            g[normal(red(i))].push_back(revert(red(i)));
        }
        if (color[i] == 'G') {
            g[revert(red(i))].push_back(normal(blue(i)));
            g[revert(blue(i))].push_back(normal(red(i)));
            g[normal(red(i))].push_back(revert(blue(i)));
            g[normal(blue(i))].push_back(revert(red(i)));
            g[normal(green(i))].push_back(revert(green(i)));
        }
        if (color[i] == 'B') {
            g[revert(green(i))].push_back(normal(red(i)));
            g[revert(red(i))].push_back(normal(green(i)));
            g[normal(green(i))].push_back(revert(red(i)));
            g[normal(red(i))].push_back(revert(green(i)));
            g[normal(blue(i))].push_back(revert(blue(i)));
        }
    }
    for (int u = 0; u < n; ++u) {
        for (int v : gg[u]) {
            g[normal(green(u))].push_back(revert(green(v)));
            g[normal(green(v))].push_back(revert(green(u)));
            g[normal(red(u))].push_back(revert(red(v)));
            g[normal(red(v))].push_back(revert(red(u)));
            g[normal(blue(u))].push_back(revert(blue(v)));
            g[normal(blue(v))].push_back(revert(blue(u)));
        }
    }
    vector<vector<int>> rg(sz);
    for (int i = 0; i < sz; ++i) {
        for (int j : g[i]) {
            rg[j].push_back(i);
        }
    }
    vector<Color> used(sz, WHITE);
    vector<int> order;
    for (int i = 0; i < sz; ++i) {
        if (used[i] == WHITE) {
            dfs(i, used, order, g);
        }
    }
    reverse(order.begin(), order.end());
    used.assign(sz, WHITE);
    vector<int> comp(sz);
    for (int elem : order) {
        if (used[elem] == WHITE) {
            ++curr_component;
            scc(elem, used, comp, rg);
        }
    }
    string result;
    result.resize(n);
    for (int i = 0; i < sz; ++i) {
        if (!is_revert(i)) {
            if (comp[i] > comp[i + 1]) {
                result[get_i(i)] = get_color(i) == 0 ? 'G' : get_color(i) == 1 ? 'R' : 'B';
            } else if (comp[i] == comp[i + 1]) {
                return "Impossible";
            }
        }
    }
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    string color;
    cin >> color;
    vector<vector<int>> gg(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        gg[u].push_back(v);
        gg[v].push_back(u);
    }
    string result = solve(n, gg, color);
    cout << result;
    return 0;
}