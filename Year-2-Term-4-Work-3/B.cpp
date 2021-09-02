#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

#pragma GCC optimize("O3", "unroll-loops", "fast-math")

using namespace std;

typedef long long ll;

ll ans = 0;
string s;

vector<int> zeros, ones;

void gen(int i, string &v1, string &v2, ll mul, int d1, int d0) {
    if (d1 > ones[i] || d0 > zeros[i]) {
        return;
    }
    if (i == (int) s.size() && d1 == 0 && d0 == 0) {
        ans += mul;
        return;
    }
    if (v1.size() == v2.size()) {
        if (i + 4 <= (int) s.size() && s[i] == s[i + 1] && s[i] == s[i + 2] && s[i] == s[i + 3]) {
            if (((int) v1.size() + 4) * 2 <= (int) s.size()) {
                for (int t = 0; t < 4; ++t) {
                    v1.push_back(s[i]);
                }
                gen(i + 4, v1, v2, 2 * mul, d1 + 4 * (s[i] == 'x'), d0 + 4 * (s[i] == 'o'));
                for (int t = 0; t < 4; ++t) {
                    v1.pop_back();
                }
            }

            if (((int) v1.size() + 3) * 2 <= (int) s.size()) {
                for (int t = 0; t < 3; ++t) {
                    v1.push_back(s[i]);
                }
                v2.push_back(s[i]);
                gen(i + 4, v1, v2, 8 * mul, d1 + 2 * (s[i] == 'x'), d0 + 2 * (s[i] == 'o'));
                v2.pop_back();
                for (int t = 0; t < 3; ++t) {
                    v1.pop_back();
                }
            }


            if (((int) v1.size() + 2) * 2 <= (int) s.size()) {
                v1.push_back(s[i]);
                v1.push_back(s[i]);
                v2.push_back(s[i]);
                v2.push_back(s[i]);
                gen(i + 4, v1, v2, 6 * mul, d1, d0);
                v1.pop_back();
                v1.pop_back();
                v2.pop_back();
                v2.pop_back();
            }
        } else if (i + 2 <= (int) s.size() && s[i] == s[i + 1]) {
            if (((int) v1.size() + 2) * 2 <= (int) s.size()) {
                v1.push_back(s[i]);
                v1.push_back(s[i]);
                gen(i + 2, v1, v2, 2 * mul, d1 + 2 * (s[i] == 'x'), d0 + 2 * (s[i] == 'o'));
                v1.pop_back();
                v1.pop_back();
            }

            if (((int) v1.size() + 1) * 2 <= (int) s.size()) {
                v1.push_back(s[i]);
                v2.push_back(s[i]);
                gen(i + 2, v1, v2, 2 * mul, d1, d0);
                v1.pop_back();
                v2.pop_back();
            }
        } else {
            v1.push_back(s[i]);
            gen(i + 1, v1, v2, 2 * mul, d1 + (s[i] == 'x'), d0 + (s[i] == 'o'));
            v1.pop_back();
        }
    } else if (v1.size() > v2.size()) {
        if (i + 4 <= (int) s.size() && s[i] == s[i + 1] && s[i] == s[i + 2] && s[i] == s[i + 3]) {
            if (((int) v1.size() + 4) * 2 <= (int) s.size()) {
                for (int t = 0; t < 4; ++t) {
                    v1.push_back(s[i]);
                }
                gen(i + 4, v1, v2, mul, d1 + 4 * (s[i] == 'x'), d0 + 4 * (s[i] == 'o'));
                for (int t = 0; t < 4; ++t) {
                    v1.pop_back();
                }
            }

            if (((int) v1.size() + 3) * 2 <= (int) s.size() && v1[v2.size()] == s[i]) {
                for (int t = 0; t < 3; ++t) {
                    v1.push_back(s[i]);
                }
                v2.push_back(s[i]);
                gen(i + 4, v1, v2, 4 * mul, d1 + 2 * (s[i] == 'x'), d0 + 2 * (s[i] == 'o'));
                v2.pop_back();
                for (int t = 0; t < 3; ++t) {
                    v1.pop_back();
                }
            }

            if (((int) v1.size() + 2) * 2 <= (int) s.size() && v1.size() >= v2.size() + 2
                && v1[v2.size()] == s[i] && v1[v2.size() + 1] == s[i]) {
                v1.push_back(s[i]);
                v1.push_back(s[i]);
                v2.push_back(s[i]);
                v2.push_back(s[i]);
                gen(i + 4, v1, v2, 6 * mul, d1, d0);
                v1.pop_back();
                v1.pop_back();
                v2.pop_back();
                v2.pop_back();
            }

            if (((int) v1.size() + 2) * 2 <= (int) s.size() && v1.size() == v2.size() + 1
                && v1[v2.size()] == s[i]) {
                v1.push_back(s[i]);
                v1.push_back(s[i]);
                v2.push_back(s[i]);
                v2.push_back(s[i]);
                gen(i + 4, v1, v2, 6 * mul, d1, d0);
                v1.pop_back();
                v1.pop_back();
                v2.pop_back();
                v2.pop_back();
            }

            if (((int) v1.size() + 1) * 2 <= (int) s.size()
                && ((int) v2.size() + 3) * 2 <= (int) s.size()
                && (v1[v2.size()] == s[i] && (v1.size() == v2.size() + 1 || v1[v2.size() + 1] == s[i])
                    && (v1.size() <= v2.size() + 2 || v1[v2.size() + 2] == s[i]))) {
                v1.push_back(s[i]);
                v2.push_back(s[i]);
                v2.push_back(s[i]);
                v2.push_back(s[i]);
                d1 -= 2 * (s[i] == 'x');
                d0 -= 2 * (s[i] == 'o');
                bool swap = false;
                if (v1.size() < v2.size()) {
                    ::swap(v1, v2);
                    d0 = -d0;
                    d1 = -d1;
                    swap = true;
                }
                gen(i + 4, v1, v2, 4 * mul, d1, d0);
                if (swap) {
                    ::swap(v1, v2);
                    d0 = -d0;
                    d1 = -d1;
                }
                d1 += 2 * (s[i] == 'x');
                d0 += 2 * (s[i] == 'o');
                v1.pop_back();
                v2.pop_back();
                v2.pop_back();
                v2.pop_back();
            }

            if (((int) v2.size() + 4) * 2 <= (int) s.size()
                && (v1[v2.size()] == s[i]
                    && (v1.size() == v2.size() + 1 || v1[v2.size() + 1] == s[i])
                    && (v1.size() <= v2.size() + 2 || v1[v2.size() + 2] == s[i])
                    && (v1.size() <= v2.size() + 3 || v1[v2.size() + 3] == s[i]))) {
                v2.push_back(s[i]);
                v2.push_back(s[i]);
                v2.push_back(s[i]);
                v2.push_back(s[i]);
                d1 -= 4 * (s[i] == 'x');
                d0 -= 4 * (s[i] == 'o');
                bool swap = false;
                if (v1.size() < v2.size()) {
                    ::swap(v1, v2);
                    d0 = -d0;
                    d1 = -d1;
                    swap = true;
                }
                gen(i + 4, v1, v2, mul, d1, d0);
                if (swap) {
                    ::swap(v1, v2);
                    d0 = -d0;
                    d1 = -d1;
                }
                d1 += 4 * (s[i] == 'x');
                d0 += 4 * (s[i] == 'o');
                v2.pop_back();
                v2.pop_back();
                v2.pop_back();
                v2.pop_back();
            }

        } else if (i + 2 <= (int) s.size() && s[i] == s[i + 1]) {
            if (((int) v1.size() + 2) * 2 <= (int) s.size()) {
                v1.push_back(s[i]);
                v1.push_back(s[i]);
                gen(i + 2, v1, v2, mul, d1 + 2 * (s[i] == 'x'), d0 + 2 * (s[i] == 'o'));
                v1.pop_back();
                v1.pop_back();
            }

            if (((int) v1.size() + 1) * 2 <= (int) s.size() && v1[v2.size()] == s[i]) {
                v1.push_back(s[i]);
                v2.push_back(s[i]);
                gen(i + 2, v1, v2, 2 * mul, d1, d0);
                v1.pop_back();
                v2.pop_back();
            }

            if (((int) v2.size() + 2) * 2 <= (int) s.size()
                && v1[v2.size()] == s[i]
                && (v1.size() == v2.size() + 1 || v1[v2.size() + 1] == s[i])) {
                v2.push_back(s[i]);
                v2.push_back(s[i]);
                d1 -= 2 * (s[i] == 'x');
                d0 -= 2 * (s[i] == 'o');
                bool swap = false;
                if (v1.size() < v2.size()) {
                    ::swap(v1, v2);
                    d0 = -d0;
                    d1 = -d1;
                    swap = true;
                }
                gen(i + 2, v1, v2, mul, d1, d0);
                if (swap) {
                    ::swap(v1, v2);
                    d0 = -d0;
                    d1 = -d1;
                }
                d1 += 2 * (s[i] == 'x');
                d0 += 2 * (s[i] == 'o');
                v2.pop_back();
                v2.pop_back();
            }
        } else if ((v1.size() + 1) * 2 <= s.size()) {
            if (v1[v2.size()] == s[i]) {
                v2.push_back(s[i]);
                gen(i + 1, v1, v2, mul, d1 - (s[i] == 'x'), d0 - (s[i] == 'o'));
                v2.pop_back();
            }

            v1.push_back(s[i]);
            gen(i + 1, v1, v2, mul, d1 + (s[i] == 'x'), d0 + (s[i] == 'o'));
            v1.pop_back();
        } else {
            if (v1[v2.size()] == s[i]) {
                v2.push_back(s[i]);
                gen(i + 1, v1, v2, mul, d1 - (s[i] == 'x'), d0 - (s[i] == 'o'));
                v2.pop_back();
            }
        }
    }
}

int main() {
    cin >> s;
    int c1 = 0, c2 = 0;
    for (char c : s) {
        c1 += (c == 'o');
        c2 += (c != 'o');
    }
    if (c1 % 2 != 0 || c2 % 2 != 0) {
        cout << 0 << endl;
    } else {
        zeros.resize(s.size() + 1);
        ones.resize(s.size() + 1);
        for (int i = (int) s.size() - 1; i >= 0; --i) {
            zeros[i] = zeros[i + 1] + (s[i] == 'o');
            ones[i] = ones[i + 1] + (s[i] == 'x');
        }
        string v1, v2;
        gen(0, v1, v2, 1ll, 0, 0);
        cout << ans << endl;
    }
    return 0;
}


