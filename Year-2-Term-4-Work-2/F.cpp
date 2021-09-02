//
// Created by Alexey Shik on 19.04.2021.
//

#include <iostream>
#include <vector>

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

pair<vector<int>, vector<int>> arr_and_lcp(string &s) {
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
    string s;
    cin >> s;
    int n = (int) s.size();
    auto pp = arr_and_lcp(s);
    vector<int> arr = pp.first;
    vector<int> lcp = pp.second;
    ll ans = n - arr[0];
    for (int i = 1; i < n; ++i) {
        ans += n - arr[i] - lcp[i];
    }
    cout << ans;
    cout << lowest;
    return 0;
}