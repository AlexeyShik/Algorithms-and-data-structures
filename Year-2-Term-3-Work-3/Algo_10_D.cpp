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
vector<int> mt, rmt, used;

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

int main() {
    fastio;
    int k;
    cin >> k;
    for (int q = 0; q < k; ++q) {
        g.clear();
        gr.clear();
        mt.clear();
        used.clear();
        rmt.clear();
        int a, b;
        cin >> a >> b;
        int n = a + b;
        gr.resize(n);
        vector<vector<bool>> connected(n, vector<bool> (n, false));
        for (int u = 0; u < a; ++u) {
            int v;
            cin >> v;
            while (v != 0) {
                --v;
                v += a;
                connected[u][v] = true;
                cin >> v;
            }
        }
        for (int u = 0; u < a; ++u) {
            for (int v = a; v < n; ++v) {
                if (!connected[u][v]) {
                    gr[u].push_back(v);
                }
            }
        }
        mt.resize(n, -1);
        used.resize(n, -1);
        for (int i = 0; i < n; ++i) {
            dfs(i);
        }
        rmt.resize(n, -1);
        for (int i = a; i < n; ++i) {
            if (mt[i] != -1) {
                rmt[mt[i]] = i;
            }
        }
        g.resize(n);
        for (int u = 0; u < n; ++u) {
            for (int v : gr[u]) {
                if (mt[v] == u) {
                    g[u].push_back(v);
                } else {
                    g[v].push_back(u);
                }
            }
        }
        used.assign(n, 0);
        for (int i = a; i < n; ++i) {
            if (mt[i] == -1) {
                dfs_cover(i);
            }
        }
        int cnt_l = 0, cnt_r = 0;
        for (int i = 0; i < n; ++i) {
            if (i < a && used[i]) {
                ++cnt_l;
            }
            if (i >= a && !used[i]) {
                ++cnt_r;
            }
        }
        cout << n - (cnt_l + cnt_r) << endl;
        cout << a - cnt_l << ' ' << b - cnt_r << endl;
        for (int i = 0; i < a; ++i) {
            if (!used[i]) {
                cout << i + 1 << ' ';
            }
        }
        cout << endl;
        for (int i = a; i < n; ++i) {
            if (used[i]) {
                cout << i + 1 - a << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}
