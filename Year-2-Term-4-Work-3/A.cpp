#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
    ll n, c;
    cin >> n;
    vector<ll> v((int) n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    cin >> c;
    ll m = (n + 1) / 2;
    vector<ll> w;
    for (ll mask = 0; mask < (1 << m); ++mask) {
        ll weight = 0;
        for (int i = 0; i < m; ++i) {
            weight += ((mask & (1 << i)) != 0) * v[i];
        }
        w.push_back(weight);
    }
    sort(w.begin(), w.end());
    ll shift = m;
    m = n - m;
    ll ans = 0;
    for (ll mask = 0; mask < (1 << m); ++mask) {
        ll weight = 0;
        for (int i = (int) shift; i < n; ++i) {
            weight += ((mask & (1 << (i - shift))) != 0) * v[i];
        }
        if (w[0] + weight > c) {
            continue;
        }
        int l = 0, r = (int) w.size();
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (w[mid] + weight <= c) {
                l = mid;
            } else {
                r = mid;
            }
        }
        ans += l + 1;
    }
    cout << ans;
    return 0;
}