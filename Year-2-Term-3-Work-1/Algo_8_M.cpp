#include <iostream>
#include <vector>

using namespace std;

enum color {
    WHITE, GRAY, BLACK
};

inline bool dfs(int u, vector<color> &used, vector<int> &order, vector<vector<int> > &g) {
    used[u] = GRAY;
    for (int v : g[u]) {
        if (used[v] == GRAY || (used[v] == WHITE && !dfs(v, used, order, g))) {
            return false;
        }
    }
    used[u] = BLACK;
    order.push_back(u);
    return true;
}

int main() {
    const int n = 'z' - 'a' + 1;
    int sz;
    cin >> sz;
    vector<string> words(sz);
    vector<bool> is_zero(n, true);
    for (auto &word : words) {
        cin >> word;
        if (word.size() > 1) {
            is_zero[word[0] - 'a'] = false;
        }
    }
    vector<vector<bool>> mapped(n, vector<bool>(n, false));
    vector<vector<int>> g(n);
    for (int i = 0; i < sz; ++i) {
        for (int j = i + 1; j < sz; ++j) {
            if (words[i].size() > words[j].size() || words[i] == words[j]) {
                cout << "No";
                return 0;
            }
            if (words[i].size() < words[j].size()) {
                continue;
            }
            for (int t = 0; t < (int) words[i].size(); ++t) {
                int a = words[i][t] - 'a', b = words[j][t] - 'a';
                if (a != b) {
                    if (mapped[b][a]) {
                        cout << "No";
                        return 0;
                    }
                    if (!mapped[a][b]) {
                        g[b].push_back(a);
                        mapped[a][b] = true;
                        is_zero[b] = false;
                    }
                    break;
                }
            }
        }
    }
    vector<color> used(n, WHITE);
    vector<int> order;
    int zero = -1;
    for (int i = 0; i < n; ++i) {
        if (is_zero[i]) {
            zero = i;
            break;
        }
    }
    if (zero == -1) {
        cout << "No";
        return 0;
    }
    if (!dfs(zero, used, order, g)) {
        cout << "No";
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (used[i] == WHITE && !dfs(i, used, order, g)) {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes" << endl;
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[order[i]] = i;
    }
    for (int elem : ans) {
        cout << elem << ' ';
    }
    return 0;
}
