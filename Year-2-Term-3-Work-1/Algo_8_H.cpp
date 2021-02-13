#include <iostream>
#include <vector>

using namespace std;

struct edge {
    int from;
    int to;
    int id;

    explicit edge(int from, int to, int id) : from(from), to(to), id(id) {}
};

const int INF = 1e9+7;

enum color {
    WHITE, BLACK
};

int timer = 0, bridges = 0;

inline void dfs(int u, int p, vector<int> &tin, vector<int> &f,
                vector<color> &used, vector<bool> &bridge, vector<vector<edge> > &g) {
    used[u] = BLACK;
    tin[u] = f[u] = timer++;
    for (edge e : g[u]) {
        if (used[e.to] == WHITE) {
            dfs(e.to, u, tin, f, used, bridge, g);
        }
        if (e.to != p) {
            f[u] = min(f[u], f[e.to]);
        }
        if (tin[u] < f[e.to]) {
            bridge[e.id] = true;
            ++bridges;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<edge> > g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(edge(u, v, i));
        g[v].push_back(edge(v, u, i));
    }
    vector<color> used(n, WHITE);
    vector<int> tin(n, INF), f(n, INF);
    vector<bool> bridge(m);
    for (int i = 0; i < n; ++i) {
        if (used[i] == WHITE) {
            dfs(i, -1, tin, f, used, bridge, g);
        }
    }
    cout << bridges << endl;
    for (int i = 0; i < m; ++i) {
        if (bridge[i]) {
            cout << i + 1 << ' ';
        }
    }
    return 0;
}