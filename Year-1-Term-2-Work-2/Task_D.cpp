#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>

#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fileio freopen("multimap.in", "r", stdin), freopen("multimap.out", "w", stdout)
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
const int funcs = 1e5;
const ll mod = 1e9 + 7;
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
    int get_id(const string &x) {
        int ans = 0;
        for (const char &c : x) {
            ans = (a * ans + b + (int)mod + c) % p;
        }
        return ans;
    }
};

vector <hash_func> h;

void fill() {
    for (int a = 1; a <= 100; ++a) {
        for (int b = 1; b <= 100; ++b) {
            for (int i = 0; i < 10; ++i) {
                h.emplace_back(a, b, simple[i]);
            }
        }
    }
}

struct hash_set {
    size_t m;
    size_t sz;
    int j;
    vector <list<string> > table;
    hash_set(int m) {
        this->m = m;
        j = rand() % funcs;
        sz = 0;
        table.resize(m);
    }
    void resize() {
        m = 2 * sz;
        vector <list<string> > tmp(m);
        for (const auto &l : table) {
            for (const auto &x : l) {
                tmp[h[j].get_id(x) % m].push_back(x);
            }
        }
        swap(table, tmp);
        tmp.clear();
    }
    void insert(const string &x) {
        int i = h[j].get_id(x) % m;
        if (find(table[i].begin(), table[i].end(), x) == table[i].end()) {
            table[i].push_back(x);
            ++sz;
        }
        if (sz > 4 * m) {
            resize();
        }
    }
    bool exists(const string &x) {
        int i = h[j].get_id(x) % m;
        return find(table[i].begin(), table[i].end(), x) == table[i].end();
    }
    void erase(const string &x) {
        int i = h[j].get_id(x) % m;
        if (find(table[i].begin(), table[i].end(), x) != table[i].end()) {
            table[i].remove(x);
            sz--;
        }
    }
    void print() {
        for (auto t : table) {
            for (auto elem : t) {
                cout << elem << ' ';
            }
        }
        cout << endl;
    }
    int size() {
        return sz;
    }
    bool isEmpty() {
        return sz == 0;
    }
};

struct node {
    hash_set *set;
    int key_hash;
    string key;
    node() {
        key = "";
        set = nullptr;
        key_hash = 0;
    }
    node(const string &x, const string &y, int hx) {
        key = x;
        key_hash = hx;
        set = new hash_set(2);
        set->insert(y);
    }
};

struct hash_map {
    vector<list<node*>> nodes;
    int j, m;
    hash_map(int m0) {
        nodes.resize(m0);
        m = m0;
        j = rand() % (funcs - 1);
    }
    list<node*> :: iterator find(const string &x) {
        int i = h[j].get_id(x) % m;
        int t = h[j + 1].get_id(x) % m;
        auto p = nodes[i].begin();
        for (; p != nodes[i].end(); ++p) {
            if ((*p)->key_hash == t && x == (*p)->key) {
                return p;
            }
        }
        return nodes[i].end();
    }
    void put(const string &x, const string &y) {
        int i = h[j].get_id(x) % m;
        auto p = find(x);
        if (p == nodes[i].end()) {
            nodes[i].push_back(new node(x, y, h[j + 1].get_id(x) % m));
        } else {
            (*p)->set->insert(y);
        }
    }
    void get(const string &x) {
        int i = h[j].get_id(x) % m;
        auto p = find(x);
        if (p == nodes[i].end()) {
            cout << 0 << endl;
        } else {
            cout << (*p)->set->size() << ' ';
            (*p)->set->print();
        }
    }
    void erase(const string &x, const string &y) {
        int i = h[j].get_id(x) % m;
        auto p = find(x);
        if (p == nodes[i].end()) {
            return;
        }
        (*p)->set->erase(y);
    }
    void erase_all(const string &x) {
        int i = h[j].get_id(x) % m;
        auto p = find(x);
        if (p == nodes[i].end()) {
            return;
        }
        nodes[i].erase(p);
    }
};

int main() {
    fastio;
    fileio;
    srand(time(nullptr));
    fill();
    hash_map hm(1e5);
    string s;
    while (cin >> s) {
        string x;
        cin >> x;
        if (s[0] == 'p') {
            string y;
            cin >> y;
            hm.put(x, y);
        } else if (s[0] == 'g') {
            hm.get(x);
        } else if (s[s.size() - 1] == 'e') {
            string y;
            cin >> y;
            hm.erase(x, y);
        } else {
            hm.erase_all(x);
        }
    }
    return 0;
}
