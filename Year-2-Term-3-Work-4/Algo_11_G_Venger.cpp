#include <iostream>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <cassert>

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

void hungarian(vector<vector<ll>> &cost) {
    int n = cost.size();
    vector<ll> phi_r(n + 1), phi_c(n + 1);
    vector<int> prev(n + 1), mt(n + 1);
    for (int i = 1; i <= n; ++i) {
        mt[0] = i;
        int curr = 0;
        vector<ll> min_dist(n + 1, inf);
        vector<bool> used(n + 1, false);
        do {
            used[curr] = true;
            ll d = inf;
            int next = -1;
            for (int j = 1; j <= n; ++j) {
                if (!used[j]) {
                    ll c = cost[mt[curr] - 1][j - 1] - phi_r[mt[curr]] - phi_c[j];
                    if (min_dist[j] > c) {
                        min_dist[j] = c;
                        prev[j] = curr;
                    }
                    if (d > min_dist[j]) {
                        next = j;
                        d = min_dist[j];
                    }
                }
            }
            for (int j = 0; j <= n; ++j) {
                if (used[j]) {
                    phi_r[mt[j]] += d;
                    phi_c[j] -= d;
                } else {
                    min_dist[j] -= d;
                }
            }
            curr = next;
        } while (mt[curr] != 0);
        do {
            int tmp = prev[curr];
            mt[curr] = mt[tmp];
            curr = tmp;
        } while (curr != 0);
    }
    cout << -phi_c[0] << endl;
    for (int i = 1; i <= n; ++i) {
        cout << mt[i] << ' ' << i << endl;
    }
}

int main() {
    fastio;
    int n;
    cin >> n;
    vector<vector<ll>> cost(n, vector<ll> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cost[i][j];
        }
    }
    hungarian(cost);
    return 0;
}