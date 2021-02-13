#include <iostream>
#include <vector>

using namespace std;

enum color {
    WHITE, GRAY, BLACK
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> last(n, -1), v(m), max_number(n, -1);
    for (int i = 0; i < m; ++i) {
        cin >> v[i];
        --v[i];
        last[v[i]] = i;
    }
    vector<pair<int, int>> g;
    vector<color> used(n, WHITE);
    for (int i = 0; i < m; ++i) {
        if (used[v[i]] == WHITE) {
            if (i != 0 && last[v[i - 1]] != i - 1) {
                max_number[v[i - 1]] = max(max_number[v[i - 1]], v[i]);
            }
            for (int j = 0; j < n; ++j) {
                if (used[j] == GRAY && v[i] >= max_number[j]) {
                    g.emplace_back(j, v[i]);
                }
            }
        }
        used[v[i]] = i == last[v[i]] ? BLACK : GRAY;
    }
    cout << g.size() << endl;
    for (auto e : g) {
        cout << e.first + 1 << ' ' << e.second + 1 << endl;
    }
    return 0;
}
