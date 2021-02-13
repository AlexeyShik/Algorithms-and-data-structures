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
vector<bool> used;

inline void dfs(int u) {
    used[u] = true;
    for (int v : g[u]) {
        if (!used[v]) {
            used[v] = true;
            dfs(mt[v]);
        }
    }
}

int main() {
    fastio;
    int a, b;
    cin >> a >> b;
    int n = a + b;
    vector<vector<int>> gr(n);
    g.resize(n);
    for (int i = 0; i < a; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int v;
            cin >> v;
            --v;
            v += a;
            gr[i].push_back(v);
        }
    }
    mt.resize(a);
    vector<bool> r_mt(n, false);
    for (int i = 0; i < a; ++i) {
        cin >> mt[i];
        --mt[i];
        mt[i] += a;
        if (mt[i] != -1) {
            r_mt[mt[i]] = true;
        }
    }
    for (int u = 0; u < n; ++u) {
        for (int v : gr[u]) {
            if (mt[u] == v) {
                g[u].push_back(v);
            } else {
                g[v].push_back(u);
            }
        }
    }
    used.resize(n, false);
    for (int i = a; i < n; ++i) {
        if (!r_mt[i]) {
            dfs(i);
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
    cout << cnt_l + cnt_r << endl;
    cout << cnt_l << ' ';
    for (int i = 0; i < a; ++i) {
        if (used[i]) {
            cout << i + 1 << ' ';
        }
    }
    cout << endl;
    cout << cnt_r << ' ';
    for (int i = a; i < n; ++i) {
        if (!used[i]) {
            cout << i + 1 - a << ' ';
        }
    }
    return 0;
}
