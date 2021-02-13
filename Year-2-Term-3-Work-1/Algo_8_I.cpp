#include <iostream>
#include <vector>

using namespace std;

struct edge {
    int from;
    int to;

    explicit edge(int from, int to) : from(from), to(to) {}
};

const int INF = 1e9+7;

enum color {
    WHITE, BLACK
};

int timer = 0, points = 0;

inline void dfs(int u, int p, vector<int> &tin, vector<int> &f,
                vector<color> &used, vector<bool> &point, vector<vector<edge> > &g) {
    used[u] = BLACK;
    tin[u] = f[u] = timer++;
    int count = 0;
    for (edge e : g[u]) {
        if (used[e.to] == WHITE) {
            dfs(e.to, u, tin, f, used, point, g);
            f[u] = min(f[u], f[e.to]);
            if (f[e.to] >= tin[u]) {
                ++count;
            }
        } else if (e.to != p)  {
            f[u] = min(f[u], tin[e.to]);
        }
    }
    if (count >= 2 || (p != -1 && count >= 1)) {
        ++points;
        point[u] = true;
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
        g[u].push_back(edge(u, v));
        g[v].push_back(edge(v, u));
    }
    vector<color> used(n, WHITE);
    vector<int> tin(n, INF), f(n, INF);
    vector<bool> point(n);
    for (int i = 0; i < n; ++i) {
        if (used[i] == WHITE) {
            dfs(i, -1, tin, f, used, point, g);
        }
    }
    cout << points << endl;
    for (int i = 0; i < n; ++i) {
        if (point[i]) {
            cout << i + 1 << ' ';
        }
    }
    return 0;
}
