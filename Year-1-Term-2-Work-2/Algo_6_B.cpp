#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fileio freopen("map.in", "r", stdin), freopen("map.out", "w", stdout)
#define pb push_back
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
typedef long double ld;
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
};

vector <hash_func> h;

struct string_hash {
	int h1, h2;
	string_hash(string &s) {
		h1 = h2 = 0;
		for (char c : s) {
			h1 = (h1 * 41 + (int)c) % (int)(1e9 + 7);
			h2 = (h2 * 43 + (int)c) % (int)(1e9 + 9);
		}
	}
	bool operator ==(const string_hash &right) {
    	return h1 == right.h1 && h2 == right.h2;
	}
};

void fill() {
	for (int a = 1; a <= 100; ++a) {
        for (int b = 1; b <= 100; ++b) {
            for (int i = 0; i < 10; ++i) {
                h.push_back(hash_func(a, b, simple[i]));
            }
        }
    }
}

struct hash_map {
	size_t m;
	size_t sz;
	int j;
	vector <list<string_hash> > hash;
	vector <list<pair<string, string> > > str;
	hash_map(int m) {
		fill();
		this->m = m;
		j = rand() % funcs;
		sz = 0;
		hash.resize(m);
		str.resize(m);
	}
	void resize() {
		m = 3 * sz;
        vector <list<string_hash> > tmp(m);
        vector <list<pair<string, string> > > smp(m);
        for (auto l : str) {
        	for (auto x : l) {
        		string_hash pp = string_hash(x.first);
        		int k = h[j].get_id(pp.h1) % m;
            	tmp[k].push_back(pp);
            	smp[k].push_back(x);
			}
		}
		swap(hash, tmp);
		swap(str, smp);
		tmp.clear();
		smp.clear();
	}
	void put(string &x, string &y) {
		erase(x);
		string_hash pp = string_hash(x);
        int i = h[j].get_id(pp.h1) % m;
        hash[i].push_back(pp);
        str[i].push_back({x, y});
        ++sz;
        if (sz > 3 * m && m < 1e6) {
            resize();
		}
	}
	string get(string &x) {
		string_hash pp = string_hash(x);
        int i = h[j].get_id(pp.h1) % m;
        auto p2 = str[i].begin();
		for (auto p1 = hash[i].begin(); p1 != hash[i].end(); ++p1, ++p2) {
			if (*p1 == pp) {
				return p2->second;
			}
		}
		return "none";
	}
	void erase(string &x) {
		string_hash hx = string_hash(x);
        int i = h[j].get_id(hx.h1) % m;
		if (find(hash[i].begin(), hash[i].end(), hx) != hash[i].end()) {
			string y = get(x);
			if (y == "none") {
				return;
			}
            hash[i].remove(hx);
            str[i].remove({x, y});
        }
	}
};

int main() {
    fastio;
    fileio;
    srand(time(nullptr));
    hash_map hm(2);
    string s;
    while (cin >> s) {
        string x;
        cin >> x;
        if (s[0] == 'p') {
        	string y;
        	cin >> y;
            hm.put(x, y);
        } else if (s[0] == 'g') {
            cout << hm.get(x) << endl;
        } else {
           hm.erase(x);
        }
    }
    return 0;
}
