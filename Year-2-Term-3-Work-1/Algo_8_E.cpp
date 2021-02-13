#include <iostream>
#include <vector>

using namespace std;

enum color {
    WHITE, GRAY, BLACK
};

inline int dfs(int u, vector<color> &used, vector<vector<int> > &g) {
    used[u] = GRAY;
    for (int v : g[u]) {
        if (used[v] == GRAY) {
            return v;
        } else if (used[v] == WHITE) {
            int result = dfs(v, used, g);
            if (result != -1) {
                return result;
            }
        }
    }
    used[u] = BLACK;
    return -1;
}

inline void print_cycle(int u, vector<color> &used, vector<vector<int>> &g) {
    cout << u + 1 << ' ';
    used[u] = BLACK;
    for (int v : g[u]) {
        if (used[v] == GRAY) {
            print_cycle(v, used, g);
        }
    }
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
    }
    vector<color> used(n, WHITE);
    for (int i = 0; i < n; ++i) {
        if (used[i] == WHITE) {
            int result = dfs(i, used, g);
            if (result != -1) {
                cout << "YES" << endl;
                print_cycle(result, used, g);
                return 0;
            }
        }
    }
    cout << "NO";
    return 0;
}
