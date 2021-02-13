#include <iostream>
#include <vector>
#include <unordered_map>

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
vector<vector<int>> g;
vector<int> mtl, mtr, used;
vector<vector<bool>> reach, edge;

inline void dfs(int u, int p = -1) {
    if (p == -1) {
        p = u;
        used[u] = u;
    } else {
        used[u] = used[p];
    }
    for (int r : g[u]) {
        reach[p][r] = true;
        int l = mtr[r];
        if (used[l] != used[u]) {
            dfs(l, p);
        }
    }
}

int main() {
    int n;
    cin >> n;
    g.resize(2 * n);
    edge.resize(n, vector<bool>(2 * n));
    for (int u = 0; u < n; ++u) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v;
            --v;
            v += n;
            g[u].push_back(v);
            g[v].push_back(u);
            edge[u][v] = true;
        }
    }
    mtl.resize(n);
    mtr.resize(2 * n);
    for (int i = 0; i < n; ++i) {
        cin >> mtl[i];
        --mtl[i];
        mtl[i] += n;
        mtr[mtl[i]] = i;
    }
    reach.resize(n, vector<bool>(2 * n));
    used.resize(n, -1);
    for (int i = 0; i < n; ++i) {
        dfs(i);
    }
    for (int i = 0; i < n; ++i) {
        vector<int> ans;
        for (int j = n; j < 2 * n; ++j) {
            if (j == mtl[i] || (edge[i][j] && reach[mtr[j]][mtl[i]])) {
                ans.push_back(j);
            }
        }
        cout << ans.size() << ' ';
        for (int x : ans) {
            cout << x - n + 1 << ' ';
        }
        cout << endl;
    }
    return 0;
}
