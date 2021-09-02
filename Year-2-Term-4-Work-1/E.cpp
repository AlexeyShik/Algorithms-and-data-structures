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

vector<ll> calc_hash(string &s) {
    vector<ll> hash(s.size() + 1, 0);
    for (int i = 0; i < (int) s.size(); ++i) {
        hash[i + 1] = add(mul(base, hash[i]), s[i]);
    }
    return hash;
}

vector<int> z_func(string &s) {
    vector<int> z(s.size(), 0);
    int l = 0, r = 0;
    for (int i = 1; i < (int) s.size(); ++i) {
        z[i] = 0;
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < (int) s.size() && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

ll get_hash(vector<ll> &hash, vector<ll> &pw, int l, int r) {
    return sub(hash[r], mul(hash[l - 1], pw[r - l + 1]));
}

int main() {
    string t, p;
    cin >> p >> t;
    string s = p + "$" + t;
    vector<int> z = z_func(s);
    vector<ll> hash_p = calc_hash(p);
    vector<ll> hash_s = calc_hash(s);
    vector<ll> pw(s.size() + 1, 1);
    for (int i = 0; i < (int) s.size(); ++i) {
        pw[i + 1] = mul(pw[i], base);
    }
    vector<int> ans;
    for (int i = (int) p.size() + 1; i + (int) p.size() <= (int) s.size(); ++i) {
        if (z[i] >= (int) p.size() - 1) {
            ans.push_back(i - p.size());
            continue;
        }
        int l = i + z[i] + 1;
        int r = i + p.size() - 1;
        ll ht = get_hash(hash_s, pw, l + 1, r + 1);
        l = z[i] + 1;
        r = p.size() - 1;
        ll hp = get_hash(hash_p, pw, l + 1, r + 1);
        if (hp == ht) {
            ans.push_back(i - p.size());
        }
    }
    cout << ans.size() << endl;
    for (int x : ans) {
        cout << x << ' ';
    }
    return 0;
}
