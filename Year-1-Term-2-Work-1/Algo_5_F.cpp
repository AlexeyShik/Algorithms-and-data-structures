#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define fileio freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)
#define pb push_back
#define pll pair<ll, ll>
#define pii pair<int, int>
#pragma GCC optimize("O3")

using namespace std;
typedef long long ll;
typedef long double ld;
const ll mod = 1e9;
const ll inf = 1e18;

struct node {
    ll y, sz, x;
    node *left, *right;
    node(ll val) {
        sz = 1;
        x = val;
        y = (rand() << 15) | rand();
        left = right = nullptr;
    }
};

inline ll sz(node * root) {
	if (!root)
		return 0;
	return root->sz;
}

inline void update(node * root) {
	if (!root)
		return;
	root->sz = sz(root->left) + 1 + sz(root->right);
}

inline void print(node * root) {
	if (!root)
		return;
	print(root->left);
	cout << root->x << ' ';
	print(root->right);
}

inline pair <node *, node *> split(node * root, ll cnt) {
    if (!root)
        return {nullptr, nullptr};
    if (cnt <= sz(root->left)) {
		pair <node *, node *> res = split(root->left, cnt);
        root->left = res.second;
        update(root);
        return {res.first, root};
    } else {
        pair <node *, node *> res = split(root->right, cnt - sz(root->left) - 1);
        root->right = res.first;
        update(root);
        return {root, res.second};
    }
}

inline node * merge(node * root1, node * root2) {
    if (!root1) {
        return root2;
    }
	if (!root2) {
        return root1;
    }
    if (root1->y < root2->y) {
        root1->right = merge(root1->right, root2);
        update(root1);
        return root1;
    } else {
        root2->left = merge(root1, root2->left);
        update(root2);
        return root2;
    }
}

inline node * insert(node * root, node * v, ll k) {
    if (!root)
    	return v;
    if (!v)
    	return root;
    if (v->y < root->y) {
    	auto p = split(root, k);
    	v->left = p.first;
    	v->right = p.second;
    	update(v);
    	return v;
	}
	if (sz(root->left) >= k)
		root->left = insert(root->left, v, k);
	else
		root->right = insert(root->right, v, k - sz(root->left) - 1);
	update(root);
	return root;
}

inline node * erase(node * root, ll k) {
	if (!root)
		return nullptr;
	if (sz(root->left) == k)
		return merge(root->left, root->right);
	if (sz(root->left) > k)
		root->left = erase(root->left, k);
	else
		root->right = erase(root->right, k - sz(root->left) - 1);
	update(root);
	return root;
}

inline void make_val(node * root, ll val, ll cnt) {
	if (!root)
		return;
	if (sz(root->left) == cnt) {
		root->x = val;
		return;
	}
	if (sz(root->left) > cnt)
		make_val(root->left, val, cnt);
	else
		make_val(root->right, val, cnt - sz(root->left) - 1);
}

inline node * make_swap(node * root, ll l, ll r) {
	auto p1 = split(root, r + 1);
	auto p2 = split(p1.first, l);
	r -= sz(p2.first);
	l -= sz(p2.first);
	auto p3 = split(p2.second, r);
	p2.second = merge(p3.second, p3.first);
	p1.first = merge(p2.first, p2.second);
	root = merge(p1.first, p1.second);
	return root;
}

inline void go(node * root, vector <ll> &vals) {
	if (!root)
		return;
	go(root->left, vals);
	vals.pb(root->x);
	go(root->right, vals);
}

inline int get(vector <int> &zeros, int i) {
	return zeros[i] = (zeros[i] == i ? i : get(zeros, zeros[zeros[i]]));
}

int main() {
	fastio;
	node * root = nullptr;
	ll n, m;
	cin >> n >> m;
	const ll maxm = 2 * max(n, m) + 10;
	for (int i = 0; i < maxm; ++i) {
		node * v = new node(0);
		root = insert(root, v, i);
	}
	vector <int> zeros((int)maxm);
	for (int i = 0; i < maxm; ++i)
		zeros[i] = i;
	for (int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		x--;
		zeros[x] = get(zeros, zeros[x]);
		if (zeros[x] == x) {
			make_val(root, i, x);
			zeros[x] = get(zeros, zeros[x] + 1);
		} else {
			make_val(root, i, zeros[x]);
			root = make_swap(root, x, zeros[x]);
			zeros[zeros[x]] = get(zeros, zeros[zeros[x]] + 1);
			zeros[x] = get(zeros, zeros[x]);
		}
	}
	vector <ll> vals;
	go(root, vals);
	int last = (int)vals.size() - 1;
	for (; last >= 0; --last)
		if (vals[last] != 0)
			break;
	cout << last + 1 << endl;
	for (int i = 0; i <= last; ++i)
		cout << vals[i] << ' ';
	return 0;
}
