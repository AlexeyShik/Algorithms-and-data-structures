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

vector <int> calc_bound(vector<int> &arr) {
    vector<int> ans(arr.size());
    stack<int> st;
    for (int i = 0; i < (int) arr.size(); ++i) {
        while (!st.empty() && st.top() > arr[i]) {
            st.pop();
        }
        ans[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return ans;
}

vector<pair<int, int>> get_bounds(vector<int> arr) {
    vector<int> left = calc_bound(arr);
    reverse(arr.begin(), arr.end());
    vector<int> right = calc_bound(arr);
    vector<pair<int, int>> result(arr.size());
    for (int i = 0; i < (int) arr.size(); ++i) {
        result[i] = {left[i], right[(int) arr.size() - i - 1]};
    }
    return result;
}

int main() {
    string s;
    /*s = "a";
    string t = "b";
    for (int i = 0; i < 4; ++i) {
        string g = t;
        t = s;
        s += g;
    }
    cout << s << endl;*/
    cin >> s;
    int n = (int) s.size();
    auto pp = arr_and_lcp(s);
    vector<int> arr = pp.first;
    vector<int> id(n);
    for (int i = 0; i < n; ++i) {
        id[arr[i]] = i;
    }
    vector<int> lcp = pp.second;
    vector<pair<int, int>> bounds = get_bounds(arr);
    for (int i = 0; i < n; ++i) {
        if (bounds[i].first != -1) {
            bounds[i].first = id[bounds[i].first];
        }
        if (bounds[i].second != -1) {
            bounds[i].second = id[bounds[i].second];
        }
    }
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
    for (int i = 0; i < n; ++i) {
        if (bounds[i].first != -1) {
            int l = bounds[i].first;
            int r = i;
            int d = (r - l);
            int k = (int) log2(d);
            bounds[i].first = min(sparse[r][k], sparse[l + (1 << k)][k]);
        } else {
            bounds[i].first = 0;
        }
        if (bounds[i].second != -1) {
            int l = i;
            int r = bounds[i].second;
            int d = (r - l);
            int k = (int) log2(d);
            bounds[i].second = min(sparse[r][k], sparse[l + (1 << k)][k]);
        } else {
            bounds[i].second = 0;
        }
    }
    vector<ll> ans(n);
    ans[0] = 1;
    for (int i = 1; i < n; ++i) {
        int l = 0;
        int r = i + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (m + max(bounds[id[m]].first, bounds[id[m]].second) - 1 >= i) {
                r = m;
            } else {
                l = m;
            }
        }
        ans[i] = ans[i - 1] + l + 1;
    }
    for (ll x : ans) {
        cout << x << endl;
    }
    return 0;
}