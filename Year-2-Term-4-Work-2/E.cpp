//
// Created by Alexey Shik on 19.04.2021.
//

#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long ll;

constexpr char lowest = 'a' - 1;
constexpr int alphabet_size = 'z' - 'a' + 2;

vector<int> build_suff_arr(string s) {
    s = s + lowest;
    int n = (int) s.size();
    vector<int> arr(s.size()), clazz(s.size()), cnt(max(alphabet_size, n)),
            h(max(alphabet_size, n));
    int classes = 0;
    for (char c : s) {
        ++cnt[c - lowest];
    }
    for (int i = 1; i < alphabet_size; ++i) {
        h[i] = h[i - 1] + cnt[i - 1];
    }
    for (int i = 0; i < n; ++i) {
        arr[h[s[i] - lowest]++] = i;
    }
    for (int i = 1; i < n; ++i) {
        clazz[arr[i]] = clazz[arr[i - 1]];
        if (s[arr[i]] != s[arr[i - 1]]) {
            ++clazz[arr[i]];
            ++classes;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; ++i) {
            arr[i] = (arr[i] - k + n) % s.size();
        }
        cnt.assign(cnt.size(), 0);
        h.assign(cnt.size(), 0);
        for (int i = 0; i < n; ++i) {
            ++cnt[clazz[arr[i]]];
        }
        for (int i = 1; i <= classes; ++i) {
            h[i] = h[i - 1] + cnt[i - 1];
        }
        vector<int> narr(arr.size());
        for (int i = 0; i < n; ++i) {
            narr[h[clazz[arr[i]]]] = arr[i];
            h[clazz[arr[i]]]++;
        }
        arr = narr;
        vector<int> nclazz(clazz.size());
        classes = 0;
        for (int i = 1; i < n; ++i) {
            nclazz[arr[i]] = nclazz[arr[i - 1]];
            if (clazz[arr[i]] != clazz[arr[i - 1]]
                || clazz[(arr[i] + k) % s.size()] != clazz[(arr[i - 1] + k) % s.size()]) {
                ++nclazz[arr[i]];
                ++classes;
            }
        }
        clazz = nclazz;
        if (classes == n) {
            break;
        }
    }
    return arr;
}

pair<vector<int>, vector<int>> arr_and_lcp(string s) {
    vector<int> arr = build_suff_arr(s);
    s = s + lowest;
    int n = (int) s.size();
    vector<int> len_to_arr(arr.size());
    for (int i = 0; i < n; ++i) {
        len_to_arr[arr[i]] = i;
    }
    vector<int> lcp(n);
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int pos = len_to_arr[i];
        if (pos != 0) {
            while (s[(arr[pos] + k) % n] == s[(arr[pos - 1] + k) % n]) {
                ++k;
            }
        }
        lcp[pos] = k;
        if (k > 0) {
            --k;
        }
    }
    for (int i = 1; i < n; ++i) {
        arr[i - 1] = arr[i];
        lcp[i - 1] = lcp[i];
    }
    arr.pop_back();
    lcp.pop_back();
    return {arr, lcp};
}

int main() {
    int n, zz;
    cin >> n >> zz;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    string s;
    s.resize(n);
    for (int i = 0; i < n; ++i) {
        s[i] = (char) ('a' + v[i]);
    }
    auto pp = arr_and_lcp(s);
    vector<int> arr = pp.first;
    vector<int> lcp = pp.second;
    const int MAX_LOG = 20;
    vector<vector<int>> sparse(n, vector<int> (MAX_LOG));
    for (int i = 0; i < n; ++i) {
        sparse[i][0] = lcp[i];
    }
    for (int k = 1; k < MAX_LOG; ++k) {
        for (int i = n - 1; i - (1 << k) + 1 >= 0; --i) {
            sparse[i][k] = min(sparse[i][k - 1], sparse[i - (1 << (k - 1))][k - 1]);
        }
    }
    ll mx = n;
    int mx_beg = 0;
    int mx_len = n;
    vector<pair<int, int>> bounds(n, {-1, -1});
    bounds[0].first = 0;
    bounds[n - 1].second = n - 1;
    for (int i = 0; i < n; ++i) {
        if (i != 0) {
            int l = -1;
            int r = i;
            while (r - l > 1) {
                int m = (l + r) / 2;
                int k = (int) log2(i - m);
                if (min(sparse[i][k], sparse[m + (1 << k)][k]) != lcp[i]) {
                    l = m;
                } else {
                    r = m;
                }
            }
            bounds[i].first = r;
        }
        if (i != n - 1) {
            int l = i + 1;
            int r = n;
            while (r - l > 1) {
                int m = (l + r) / 2;
                int k = (int) log2(m - i);
                if (min(sparse[m][k], sparse[i + (1 << k)][k]) != lcp[i + 1]) {
                    r = m;
                } else {
                    l = m;
                }
            }
            bounds[i + 1].second = l;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (1ll * (bounds[i].second - bounds[i].first + 1) * lcp[i] > mx) {
            mx = 1ll * (bounds[i].second - bounds[i].first + 1) * lcp[i];
            mx_beg = arr[i];
            mx_len = lcp[i];
        }
    }
    cout << mx << endl << mx_len << endl;
    string t = s.substr(mx_beg, mx_len);
    for (int i = 0; i < mx_len; ++i) {
        cout << t[i] - 'a' << ' ';
    }
    return 0;
}