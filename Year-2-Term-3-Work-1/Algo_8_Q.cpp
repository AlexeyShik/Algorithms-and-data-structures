#include <iostream>
#include <vector>

using namespace std;

enum color {
    WHITE, GRAY, BLACK
};

struct edge {
    int to;
    int index;
    bool truly;

    edge(int to, int index, bool truly) : to(to), index(index), truly(truly) {}
};

inline bool dfs(int u, int w, vector<color> &used, vector<int> &truth, vector<vector<edge> > &g) {
    used[u] = GRAY;
    for (edge v : g[u]) {
        if (v.index <= w) {
            if (used[v.to] == WHITE) {
                truth[v.to] = (truth[u] == v.truly);
                if (!dfs(v.to, w, used, truth, g)) {
                    return false;
                }
            } else if (used[v.to] == GRAY && (v.truly == truth[u]) != truth[v.to]) {
                return false;
            }
        }
    }
    used[u] = BLACK;
    return true;
}

bool check(int n, int index, vector<vector<edge>> &g) {
    vector<color> used(n, WHITE);
    vector<int> truth(n, -1);
    bool ok = true;
    for (int i = 0; i < n; ++i) {
        if (used[i] == WHITE) {
            truth[i] = 1;
            vector<color> preused = used;
            vector<int> pretruth = truth;
            ok &= dfs(i, index, used, truth, g);
            truth[i] = 0;
            used = preused;
            truth = pretruth;
            ok &= dfs(i, index, used, truth, g);
        }
    }
    return ok;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<edge> > g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        --u, --v;
        g[u].push_back(edge(v, i, c == 'T'));
        g[v].push_back(edge(u, i, c == 'T'));
    }
    int l = -1, r = m;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (check(n, mid, g)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l + 1;
    return 0;
}
