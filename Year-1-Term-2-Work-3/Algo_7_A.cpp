#include <iostream>
#include <vector>
#pragma GCC optimize("O3")

using namespace std;

const int n = (1 << 24);
unsigned int a, b;
unsigned int cur = 0;

inline unsigned int nextRand() {
    cur = cur * a + b;
    return cur >> 8;
}

int main() {
    int m, q;
    cin >> m >> q >> a >> b;
    vector <unsigned int> v(n, 0);
    for (int i = 0; i < m; ++i) {
        unsigned int d = nextRand();
        unsigned int l = nextRand();
        unsigned int r = nextRand();
        if (l > r) {
            swap(l, r);
        }
        if (r + 1 < n) {
            v[r + 1] -= d;
        }
        v[l] += d;
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 1; j < n; ++j) {
            v[j] += v[j - 1];
        }
    }
    unsigned int ans = 0;
    for (int i = 0; i < m; ++i) {
        unsigned int l = nextRand();
        unsigned int r = nextRand();
        if (l > r) {
            swap(l, r);
        }
        ans += v[r] - (l > 0 ? v[l - 1] : 0);
    }
    cout << ans;
    return 0;
}
