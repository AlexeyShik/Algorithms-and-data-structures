#include <iostream>
#include <vector>

#pragma GCC optimize("O3", "unroll-loops", "fast-math")
#define fastio ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;

typedef long long ll;
const int MAXN = 1e6 + 1;

pair<vector<int>, vector<int>> prime_factor() {
    vector<int> factor(MAXN);
    vector<int> remain(MAXN);
    vector<int> primes;
    for (int i = 2; i <= MAXN; ++i) {
        if (factor[i] == 0) {
            primes.push_back(i);
            factor[i] = i;
            remain[i] = 1;
        }
        for (int d : primes) {
            if (d > factor[i] || 1ll * i * d > MAXN) {
                break;
            }
            factor[i * d] = d;
            remain[i * d] = i;
        }
    }
    return {factor, remain};
}

int main() {
    fastio;
    int n;
    cin >> n;
    auto pp = prime_factor();
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        while (x > 1) {
            cout << pp.first[x] << ' ';
            x = pp.second[x];
        }
        cout << '\n';
    }
    return 0;
}
