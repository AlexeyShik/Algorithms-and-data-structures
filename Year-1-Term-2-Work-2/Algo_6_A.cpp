#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fileio freopen("set.in", "r", stdin), freopen("set.out", "w", stdout)
#define pb push_back
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
typedef long double ld;
const int funcs = 1e5;
const ll mod = 1e18 + 7;
const ll inf = 1e18;

vector <int> simple = {1000003, 1000033, 1000037, 1000039,
     1000081, 1000099, 1000117, 1000121, 1000133, 1000151};

struct hash_func {
    int a, b, p;
    hash_func(int a, int b, int p) {
        this->a = a;
        this->b = b;
        this->p = p;
    }
    int get_id(int x) {
        return (int)((1ll * a * x + b + mod) % p);
    }
};

vector <hash_func> h;

void fill() {
	for (int a = 1; a <= 100; ++a) {
        for (int b = 1; b <= 100; ++b) {
            for (int i = 0; i < 10; ++i) {
                h.push_back(hash_func(a, b, simple[i]));
            }
        }
    }
}

struct hash_table {
	size_t m;
	size_t sz;
	int j;
	vector <list<int> > table;
	hash_table(int m) {
		fill();
		this->m = m;
		j = rand() % funcs;
		sz = 0;
		table.resize(m);
	}
	void resize() {
		m = 3 * sz;
        vector <list<int> > tmp(m);
        for (auto l : table) {
        	for (auto x : l) {
            	tmp[h[j].get_id(x) % m].push_back(x);
			}
		}
		swap(table, tmp);
		tmp.clear();
	}
	void insert(int x) {
		int i = h[j].get_id(x) % m;
		if (find(table[i].begin(), table[i].end(), x) == table[i].end()) {
            table[i].push_back(x);
            ++sz;
            if (sz > 3 * m && m < 1e6) {
                resize();
			}
        }
	}
	bool exists(int x) {
		int i = h[j].get_id(x) % m;
		return find(table[i].begin(), table[i].end(), x) == table[i].end();
	}
	void erase(int x) {
		int i = h[j].get_id(x) % m;
		if (find(table[i].begin(), table[i].end(), x) != table[i].end()) {
            table[i].remove(x);
        }
	}
};

int main() {
    fastio;
    fileio;
    srand(time(nullptr));
    hash_table ht(2);
    string s;
    while (cin >> s) {
        int x;
        cin >> x;
        if (s[0] == 'i') {
            ht.insert(x);
        } else if (s[0] == 'e') {
            cout << (ht.exists(x) ? "false" : "true") << endl;
        } else {
           ht.erase(x);
        }
    }
    return 0;
}
