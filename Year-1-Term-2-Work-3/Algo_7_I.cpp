#include <iostream>
#include <vector>
#include <algorithm>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
int const sz = 450;

struct event {
    int l, r, id;
    event() = default;
    event(int l, int r, int id) : l(l), r(r), id(id) {}
};

bool cmp(event const& a, event const &b) {
    if (a.l / sz < b.l / sz) {
        return true;
    } else if (a.l / sz > b.l / sz) {
       return false;
    } else {
       return a.r < b.r;
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector <int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    vector <event> query;
    vector <ll> ans(q, 0);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        query.push_back(event(l, r, i));
    }
    int l = 0, r = 0;
    ll cur = v[0];
    vector <int> cnt(1e6 + 1, 0);
    cnt[v[0]]++;
    sort(query.begin(), query.end(), cmp);
    for (event const& e : query) {
        while (r < e.r) {
            ++r;
            int x = v[r];
            cur -= 1ll * cnt[x] * cnt[x] * x;
            cnt[x]++;
            cur += 1ll * cnt[x] * cnt[x] * x;
        }
        while (r > e.r) {
            int x = v[r];
            cur -= 1ll * cnt[x] * cnt[x] * x;
            cnt[x]--;
            cur += 1ll * cnt[x] * cnt[x] * x;
            --r;
        }
        while (l > e.l) {
            --l;
            int x = v[l];
            cur -= 1ll * cnt[x] * cnt[x] * x;
            cnt[x]++;
            cur += 1ll * cnt[x] * cnt[x] * x;
        }
        while (l < e.l) {
            int x = v[l];
            cur -= 1ll * cnt[x] * cnt[x] * x;
            cnt[x]--;
            cur += 1ll * cnt[x] * cnt[x] * x;
            ++l;
        }
        ans[e.id] = cur;
    }
    for (ll x : ans) {
        cout << x << endl;
    }
    return 0;
}
