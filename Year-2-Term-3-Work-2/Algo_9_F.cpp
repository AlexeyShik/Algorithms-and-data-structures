#include <iostream>
#include <vector>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
typedef long double ld;

const ll inf = 1e12 + 7;
const int undef = 1e9;

int main() {
    fastio;
    int n;
    cin >> n;
    vector<vector<ll>> dist(n, vector<ll>(n, inf));
    vector<vector<int>> next(n, vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        for (int j = 0; j < n; ++j) {
            int x;
            cin >> x;
            if (x != undef && dist[i][j] > x) {
                dist[i][j] = x;
                next[i][j] = j;
            }
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != inf && dist[k][j] != inf
                    && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
                if (dist[i][j] < -inf) {
                    dist[i][j] = -inf;
                }
            }
        }
    }
    vector<int> cycle;
    for (int i = 0; i < n; ++i) {
        if (dist[i][i] < 0) {
            cycle.push_back(i);
            int j = i;
            while (next[j][i] != i && (int) cycle.size() <= 3 * n) {
                j = next[j][i];
                cycle.push_back(j);
            }
            cycle.push_back(i);
            break;
        }
    }
    if (cycle.empty()) {
        cout << "NO";
        return 0;
    }
    for (int i = 0; i < (int)cycle.size(); ++i) {
        vector<int> used(n, -1);
        used[cycle[i]] = 0;
        bool found = false;
        for (int j = i + 1; j < (int) cycle.size(); ++j) {
            if (used[cycle[j]] != -1) {
                vector<int> tmp;
                for (int t = used[cycle[j]]; t <= j; ++t) {
                    tmp.push_back(cycle[t]);
                }
                cycle = tmp;
                found = true;
                break;
            } else {
                used[cycle[j]] = j;
            }
        }
        if (found) {
            break;
        }
    }
    cout << "YES" << endl;
    cout << cycle.size() << endl;
    for (int x : cycle) {
        cout << x + 1 << ' ';
    }
    return 0;
}
