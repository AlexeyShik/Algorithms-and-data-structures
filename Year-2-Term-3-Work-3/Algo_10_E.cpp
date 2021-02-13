#include <iostream>
#include <vector>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fileio freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9;
const ll inf = 1e17;
vector<vector<int>> g, gr;
vector<string> desk;
vector<vector<pii>> cell;
vector<int> mt, rmt, used;
int n, m, d;

struct answer {
    int type;
    int r;
    int c;
    char col;
};

inline bool dfs(int u, int p = -1) {
    used[u] = (p == -1 ? u : used[p]);
    for (int v : gr[u]) {
        if (mt[v] == -1 || (used[mt[v]] != used[u] && dfs(mt[v], u))) {
            mt[v] = u;
            return true;
        }
    }
    return false;
}

inline void dfs_cover(int u) {
    used[u] = 1;
    for (int v : g[u]) {
        if (!used[v]) {
            used[v] = 1;
            dfs_cover(rmt[v]);
        }
    }
}

inline char neg(char c) {
    return c == 'W' ? 'B' : 'W';
}

inline int diag1(int i, int j) {
    return n - i + j - 1;
}

inline int diag2(int i, int j) {
    return diag1(i, m - j - 1);
}

vector<answer> solve(char col) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int d1 = diag1(i, j);
            int d2 = diag2(i, j);
            if ((desk[i][j] == col) ^ ((i + j) % 2 == 0)) {
                gr[d1].push_back(d2 + d);
                gr[d2 + d].push_back(d1);
                if (cell[d1].empty()) {
                    cell[d1].push_back({i, j});
                }
                if (cell[d2 + d].empty()) {
                    cell[d2 + d].push_back({i, j});
                }
            }
        }
    }
    for (int i = 0; i < d; ++i) {
        dfs(i);
    }
    for (int i = d; i < 2 * d; ++i) {
        if (mt[i] != -1) {
            rmt[mt[i]] = i;
        }
    }
    for (int u = 0; u < 2 * d; ++u) {
        for (int v : gr[u]) {
            if (mt[v] == u) {
                g[u].push_back(v);
            } else {
                g[v].push_back(u);
            }
        }
    }
    used.assign(2 * d, 0);
    for (int i = d; i < 2 * d; ++i) {
        if (mt[i] == -1) {
            dfs_cover(i);
        }
    }
    vector<answer> ans;
    for (int i = 0; i < d; ++i) {
        if (used[i]) {
            ans.push_back({2, cell[i][0].first, cell[i][0].second,
                           neg(desk[cell[i][0].first][cell[i][0].second])});
        }
    }
    for (int i = d; i < 2 * d; ++i) {
        if (!used[i]) {
            ans.push_back({1, cell[i][0].first, cell[i][0].second,
                           neg(desk[cell[i][0].first][cell[i][0].second])});
        }
    }
    return ans;
}

int main() {
    fastio;
    cin >> n >> m;
    d = n + m - 1;
    desk.resize(n);
    getline(cin, desk[0]);
    for (int i = 0; i < n; ++i) {
        getline(cin, desk[i]);
    }
    vector<answer> best(2 * d);
    for (char q : {'W', 'B'}) {
        g.clear();
        gr.clear();
        mt.clear();
        used.clear();
        rmt.clear();
        cell.clear();
        gr.resize(2 * d);
        mt.resize(2 * d, -1);
        used.resize(2 * d, -1);
        rmt.resize(2 * d, -1);
        cell.resize(2 * d);
        g.resize(2 * d);
        auto r = solve(q);
        if (r.size() < best.size()) {
            best = r;
        }
    }
    cout << best.size() << endl;
    for (answer &a : best) {
        cout << a.type << ' ' << a.r + 1 << ' ' << a.c + 1 << ' ' << a.col << endl;
    }
    return 0;
}
