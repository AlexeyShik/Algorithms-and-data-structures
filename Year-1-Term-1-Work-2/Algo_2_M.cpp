#include <bits/stdc++.h>
typedef long long ll;
 
using namespace std;
 
inline int get(int mask, int i) {
    return (mask & (1 << i)) > 0;
}
 
inline void set0(int &mask, int i) {
    mask &= (~(1 << i));
}
 
inline void set1(int &mask, int i) {
    mask |= (1 << i);
}
 
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector <vector <pair <int, int> > > cmp(k);
    for (int i = 0; i < k; ++i) {
        int r;
        cin >> r;
        for (int j = 0; j < r; ++j) {
            int x, y;
            cin >> x >> y;
            x--, y--;
            if (x > y)
                swap(x, y);
            cmp[i].push_back({x, y});
        }
    }
    bool gg = true;
    for (int mask = 0; mask < (1 << n); ++mask) {
        int cmask = mask;
        for (int i = 0; i < k; ++i) {
            for (size_t j = 0; j < cmp[i].size(); ++j) {
                if (get(cmask, cmp[i][j].first) < get(cmask, cmp[i][j].second)) {
                    set1(cmask, cmp[i][j].first);
                    set0(cmask, cmp[i][j].second);
                }
            }
        }
        bool sorted = true;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                sorted &= (get(cmask, i) >= get(cmask, j));
        gg &= sorted;
        if (!gg) {
        	cout << mask << ' ';
        	break;
        }
    }
    cout << (gg ? "Yes" : "No");
    return 0;
}
