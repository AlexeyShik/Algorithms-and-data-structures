#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
vector <ll> f, pref;
vector <vector <ll> > dp;
vector <vector <int> > opt;
vector <vector <bool> > ans;

void gen(int i, int j) {
    if (i == j)
        return;
    int k = opt[i][j];
    for (int t = i; t <= j; ++t) {
        ans[t].push_back(t > k);
    }
    gen(i, k);
    gen(k + 1, j);
}

int main() {
	freopen("optimalcode.in", "r", stdin);
	freopen("optimalcode.out", "w", stdout);
    int n;
    cin >> n;
    f.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> f[i];
    dp.resize(n, vector <ll> (n, 1e15));
    opt.resize(n, vector <int> (n, 0));
    pref.resize(n, 0);
    pref[0] = f[0];
    for (int i = 1; i < n; ++i)
        pref[i] = pref[i - 1] + f[i];
    for (int i = 0; i < n; ++i) {
        opt[i][i] = i;
        dp[i][i] = 0;
    }
    for (int len = 1; len < n; ++len) {
        for (int i = 0; i + len < n; ++i) {
            int j = i + len;
            for (int k = (j > 0 ? opt[i][j - 1] : 0); k <= (i+1 < n ? opt[i+1][j] : i - 1); ++k) {
                if (k + 1 < n && dp[i][k] + dp[k + 1][j] <= dp[i][j]) {
                    dp[i][j] = dp[i][k] + dp[k + 1][j];
                    opt[i][j] = k;
                }
            }
            dp[i][j] += pref[j] - (i == 0 ? 0 : pref[i - 1]);
        }
    }
    cout << dp[0][n - 1] << endl;
    ans.resize(n);
    gen(0, n - 1);
    for (int i = 0; i < n; ++i) {
        for (auto c : ans[i]) {
            cout << (int)c;
        }
        cout << endl;
    }
    return 0;
}
