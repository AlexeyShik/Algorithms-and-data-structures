#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <set>
#include <queue>
#include <cmath>

#pragma GCC optimize("O3", "unroll-loops", "fast-math")

using namespace std;

typedef long long ll;

vector<unordered_map<int, ll>> precalc;
vector<vector<int>> perms1, perms2;
vector<ll> pcnts1, pcnts2;

ll ans = 0;
int n;
ll m;

void merge_sort(vector<int> &v, ll &cnt) {
    if (v.size() <= 1) {
        return;
    }
    vector<int> v1, v2;
    for (int i = 0; i < (int) v.size(); ++i) {
        if (2 * i < (int) v.size()) {
            v1.push_back(v[i]);
        } else {
            v2.push_back(v[i]);
        }
    }
    merge_sort(v1, cnt);
    merge_sort(v2, cnt);
    int l = 0, r = 0;
    while (l < (int) v1.size() && r < (int) v2.size()) {
        if (v1[l] < v2[r]) {
            v[l + r] = v1[l];
            ++l;
        } else {
            v[l + r] = v2[r];
            cnt += (int) (v1.size() - l);
            ++r;
        }
    }
    while (l < (int) v1.size()) {
        v[l + r] = v1[l];
        ++l;
    }
    while (r < (int) v2.size()) {
        v[l + r] = v2[r];
        ++r;
    }
}

void merge_sort(vector<int> &v, int beg, ll &cnt) {
    vector<int> tmp;
    for (int i = beg; i < (int) v.size(); ++i) {
        tmp.push_back(v[i]);
    }
    merge_sort(tmp, cnt);
    for (int i = beg; i < (int) v.size(); ++i) {
        v[i] = tmp[i - beg];
    }
}

bool next_permutation(vector<int> &v, ll &cnt) {
    int n = v.size();
    bool highest = true;
    for (int i = 1; i < n; ++i) {
        highest &= v[i] < v[i - 1];
    }
    if (highest) {
        return false;
    }
    int id;
    for (id = n - 2; id >= 0; --id) {
        if (v[id] < v[id + 1]) {
            break;
        }
    }
    int mid = -1;
    for (int i = id + 1; i < n; ++i)
        if (v[i] > v[id] && (mid == -1 || v[mid] > v[i]))
            mid = i;
    if (mid == -1)
        mid = id + 1;
    for (int i = id + 1; i <= mid; ++i) {
        cnt += v[i - 1] > v[i] ? 1 : -1;
        swap(v[i - 1], v[i]);
    }
    for (int i = mid - 1; i > id; --i) {
        cnt += v[i - 1] > v[i] ? 1 : -1;
        swap(v[i - 1], v[i]);
    }
    merge_sort(v, id + 1, cnt);
    return true;
}

void calc(ll cnt, vector<int> &v1, vector<int> &v2) {
    for (int x : v1) {
        for (int y : v2) {
            if (x < y) {
                ++cnt;
            }
        }
    }
    if (cnt > m) {
        return;
    }
    unordered_map<ll, ll> cnts;
    for (int i = 0; i < (int) perms1.size(); ++i) {
        ll add = pcnts1[i];
        for (int j = 0; j < (int) v1.size(); ++j) {
            add += precalc[j][v1[perms1[i][j]]];
        }
        cnts[add]++;
    }
    for (int i = 0; i < (int)  perms2.size(); ++i) {
        ll add = pcnts2[i];
        for (int j = 0; j < (int) v2.size(); ++j) {
            add += precalc[j + (int) v1.size()][v2[perms2[i][j]]];
        }
        ans += cnts[m - cnt - add];
    }
}

void gen(ll cnt, vector<int> &free, vector<int> &curr, int k, int l) {
    if ((int) free.size() - k < ((int) free.size() + 1) / 2 - l) {
        return;
    }
    if (2 * l >= (int) free.size()) {
        vector<int> other;
        auto tmp = curr;
        for (int &x : free) {
            if (!binary_search(curr.begin(), curr.end(), x)) {
                other.push_back(x);
            }
        }
        calc(cnt, tmp, other);
        return;
    }
    if (k >= (int) free.size()) {
        return;
    }
    for (int i = k; i < (int) free.size(); ++i) {
        curr[l] = free[i];
        gen(cnt, free, curr, i + 1, l + 1);
    }
}

int main() {
    cin >> n >> m;
    vector<int> v(n);
    vector<bool> has(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        has[v[i]] = true;
    }
    ll cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (v[i] != 0) {
            for (int j = 0; j < i; ++j) {
                if (v[j] != 0 && v[j] < v[i]) {
                    cnt++;
                }
            }
        }
    }
    if (cnt > m) {
        cout << 0;
        return 0;
    }
    vector<int> free;
    for (int i = 1; i <= n; ++i) {
        if (!has[i]) {
            free.push_back(i);
        }
    }
    vector<pair<vector<int>, vector<int>>> vecs;
    for (int i = 0; i < n; ++i) {
        if (v[i] == 0) {
            vector<int> l, r;
            for (int j = 0; j < i; ++j) {
                if (v[j] != 0) {
                    l.push_back(v[j]);
                }
            }
            for (int j = i + 1; j < n; ++j) {
                if (v[j] != 0) {
                    r.push_back(v[j]);
                }
            }
            sort(l.begin(), l.end());
            sort(r.begin(), r.end());
            vecs.emplace_back(l, r);
        }
    }
    vector<int> curr(((int) free.size() + 1) / 2);
    sort(free.begin(), free.end());
    precalc.resize(vecs.size());
    for (int i = 0; i < (int) vecs.size(); ++i) {
        for (int x : free) {
            auto vv = vecs[i].first;
            auto it = lower_bound(vv.begin(), vv.end(), x);
            precalc[i][x] += (it == vv.begin() ? 0 : it - vv.begin());
            vv = vecs[i].second;
            it = upper_bound(vv.begin(), vv.end(), x);
            precalc[i][x] += (it == vv.end() ? 0 : vv.end() - it);
        }
    }
    int k = (int) (free.size() + 1) / 2;
    vector<int> t(k);
    for (int i = 0; i < (int) t.size(); ++i) {
        t[i] = i;
    }
    ll c = k * (k - 1) / 2;
    do {
        pcnts1.push_back(c);
        perms1.push_back(t);
    } while (next_permutation(t, c));
    k = (int) free.size() / 2;
    t.clear();
    t.resize(k);
    for (int i = 0; i < (int) t.size(); ++i) {
        t[i] = i;
    }
    c = k * (k - 1) / 2;
    do {
        pcnts2.push_back(c);
        perms2.push_back(t);
    } while (next_permutation(t, c));
    gen(cnt, free, curr, 0, 0);
    cout << ans;
    return 0;
}

/*
 5 5
 4 0 0 2 0

 4 4
 0 0 0 0

 3 2
 1 3 2

 6 3
 0 0 2 0 0 0

 2 87
 2 0

 10 30
 0 6 3 0 0 2 10 0 0 0

 23 100
 0 13 0 0 12 0 0 0 2 0 0 10 5 0 0 0 0 0 0 7 15 16 20
 */