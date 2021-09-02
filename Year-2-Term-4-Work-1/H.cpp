#include <iostream>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <cassert>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), \
cout.tie(0), cout.precision(20), cout.setf(ios::fixed)
#define fileio freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

typedef long long ll;
typedef long double ld;
const ll mod = 1e9+7;
const ll base = 41;
const ll inf = 1e17;

ll add(ll a, ll b) {
    return (a + b) % mod;
}

ll sub(ll a, ll b) {
    return (a + mod - b) % mod;
}

ll mul(ll a, ll b) {
    return (a * b) % mod;
}

int main() {
    string s;
    cin >> s;
    vector<ll> hash(s.size() + 1, 0);
    vector<ll> pw(s.size() + 1, 1);
    for (int i = 0; i < (int) s.size(); ++i) {
        hash[i + 1] = add(mul(base, hash[i]), s[i]);
        pw[i + 1] = mul(pw[i], base);
    }
    int q;
    cin >> q;
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if (r1 - l1 != r2 - l2) {
            cout << "No" << endl;
            continue;
        }
        if (l1 > l2) {
            swap(l1, l2);
            swap(r1, r2);
        }
        ll h1 = sub(hash[r1], mul(hash[l1 - 1], pw[r1 - l1 + 1]));
        ll h2 = sub(hash[r2], mul(hash[l2 - 1], pw[r2 - l2 + 1]));
        cout << (h1 == h2 ? "Yes" : "No") << endl;
    }
    return 0;
}
