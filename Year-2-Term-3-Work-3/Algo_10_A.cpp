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
vector<vector<int>> g;
vector<int> mt;
vector<int> used;

inline bool dfs(int u, int p = -1) {
    used[u] = (p == -1 ? u : used[p]);
    for (int v : g[u]) {
        if (mt[v] == -1 || (used[mt[v]] != used[u] && dfs(mt[v], u))) {
            mt[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    fastio;
    int a, b, m;
    cin >> a >> b >> m;
    int n = a + b;
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        v += a;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    mt.resize(n, -1);
    used.resize(n, -1);
    int mx = 0;
    for (int i = 0; i < a; ++i) {
        if (dfs(i)) {
            ++mx;
        }
    }
    cout << mx;
    return 0;
}
