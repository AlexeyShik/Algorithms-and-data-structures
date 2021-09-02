#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <ctime>
#include <set>
#include <queue>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

vector<pii> edges;
vector<int> deg;
vector<bool> in_cover;
vector<vector<int>> g;

void f(int i, int rem) {
    if (i == (int) edges.size()) {
        for (int j = 0; j < (int) g.size(); ++j) {
            if (!in_cover[j] && rem > 0) {
                in_cover[j] = true;
                rem--;
            }
        }
        cout << "Yes" << endl;
        for (int j = 0; j < (int) in_cover.size(); ++j) {
            if (in_cover[j]) {
                cout << j + 1 << ' ';
            }
        }
        exit(0);
    }
    int u = edges[i].first;
    int v = edges[i].second;
    if (in_cover[u] || in_cover[v]) {
        f(i + 1, rem);
    } else {
        if (rem == 0) {
            return;
        }
        if (deg[u] == 1) {
            in_cover[v] = true;
            f(i + 1, rem - 1);
            in_cover[v] = false;
        } else if (deg[v] == 1) {
            in_cover[u] = true;
            f(i + 1, rem - 1);
            in_cover[u] = false;
        } else {
            if (deg[u] < deg[v]) {
                swap(u, v);
            }
            in_cover[u] = true;
            f(i + 1, rem - 1);
            in_cover[u] = false;
            vector<int> covered;
            for (int t : g[u]) {
                if (!in_cover[t]) {
                    covered.push_back(t);
                    in_cover[t] = true;
                }
            }
            if (rem >= (int) covered.size()) {
                f(i + 1, rem - (int) covered.size());
            }
            for (int t : covered) {
                in_cover[t] = false;
            }
        }
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    edges.resize(m);
    in_cover.resize(n);
    deg.resize(n);
    g.resize(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        edges[i] = {u, v};
        deg[u]++;
        deg[v]++;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    f(0, k);
    cout << "No";
    return 0;
}