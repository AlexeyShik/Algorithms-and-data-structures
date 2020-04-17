#include <iostream>
#include <vector>
#include <ctime>
#include <map>

using namespace std;
typedef long long ll;

const int funcs = 1e5;
int func_i = 0;
int func_j = 0;
ll mod = 0;
const vector <int> simple = {1000003, 1000033, 1000037, 1000039,
                       1000081, 1000099, 1000117, 1000121, 1000133, 1000151};

struct hash_func {
    int a, b, p;
    hash_func(int a, int b, int p) {
        this->a = a;
        this->b = b;
        this->p = p;
    }
    int get_id(int x) {
        return (int)((1ll * a * x + b) % p) % mod;
    }
};

vector <hash_func> h;

void fill() {
    for (int a = 0; a <= 10; ++a) {
        for (int b = 0; b <= 10; ++b) {
            for (int i = 0; i < 10; ++i) {
                h.emplace_back(simple[a], simple[b], simple[i]);
            }
        }
    }
}

vector <vector <int> > g;
vector <int> used, a, arr;
int current = 0;

bool dfs(int u) {
    used[u] = 1;
    bool curr = false;
    for (auto v : g[u]) {
        if (used[v] == 1) {
            return true;
        } else {
            a[v] = (current - a[u] + mod / 2) % (mod / 2);
            ++current;
            curr |= dfs(v);
        }
    }
    used[u] = 2;
    return curr;
}

int get(int x) {
    return (a[h[func_i].get_id(x)] + a[h[func_j].get_id(x)]) % mod;
}

int main() {
    srand(time(nullptr));
    int n;
    cin >> n;
    mod = 2 * n;
    fill();
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    bool loop = true;
    while (loop) {
        loop = false;
        func_i = abs(rand()) % (int)100;
        func_j = abs(rand()) % (int)100;
        g.resize(mod);
        used.resize(mod, 0);
        a.resize(mod, 0);
        vector <int> p(mod, 0);
        map <pair<int, int>, int> cnt;
        for (int i = 0; i < n; ++i) {
            cout << func_i << ' ' << func_j << endl;
            int u = h[func_i].get_id(arr[i]);
            int v = h[func_j].get_id(arr[i]);
            g[u].push_back(v);
            if (cnt[{u, v}] != 0) {
                loop = true;
                break;
            }
            cnt[{u, v}]++;
            p[v]++;
        }
        if (loop) {
            continue;
        }
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                a[i] = current;
                current++;
                loop = dfs(i);
                if (loop) {
                    break;
                }
            }
        }
    }
    for (int x : arr) {
        cout << get(x) << ' ';
    }
    return 0;
}