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
const ll inf = 1e9;

struct node {
    ll x, y, sz, id;
    node *left, *right;
    node(ll val, ll id0) {
        x = val;
        sz = 1;
        id = id0;
        y = (rand() << 10) | rand();
        left = right = nullptr;
    }
};

ll sz(node * root) {
	if (!root)
		return 0;
	return root->sz;
}

void update(node * root) {
	if (!root)
		return;
	root->sz = sz(root->left) + 1 + sz(root->right);
}

void print(node * root) {
	if (!root)
		return;
	print(root->left);
	cout << root->x << ' ';
	print(root->right);
}

pair <node *, node *> split(node * root, ll val, ll id) {
    if (!root)
        return {nullptr, nullptr};
    if (root->x < val || (root->x == val && root->id < id)) {
        pair <node *, node *> res = split(root->right, val, id);
        root->right = res.first;
        update(root);
        return{root, res.second};
    } else {
        pair <node *, node *> res = split(root->left, val, id);
        root->left = res.second;
        update(root);
        return {res.first, root};
    }
}

node * merge(node * root1, node * root2) {
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

node * insert(node * root, node * v) {
    if (!root)
    	return v;
    if (!v)
    	return root;
    if (v->y < root->y) {
    	auto p = split(root, v->x, v->id);
    	v->left = p.first;
    	v->right = p.second;
    	update(v);
    	return v;
	}
	if (v->x < root->x || (v->x == root->x && v->id < root->id))
		root->left = insert(root->left, v);
	else
		root->right = insert(root->right, v);
	update(root);
	return root;
}

node * erase(node * root, ll val, ll id) {
	if (!root)
		return nullptr;
	if (root->x == val)
		return merge(root->left, root->right);
	if (val < root->x || (val == root->x && id < root->id))
		root->left = erase(root->left, val, id);
	else
		root->right = erase(root->right, val, id);
	update(root);
	return root;
}

ll kth(node * root, ll k) {
	if (!root)
		return -inf;
	if (sz(root->left) == k)
		return root->x;
	if (k < sz(root->left))
		return kth(root->left, k);
	else
		return kth(root->right, k - sz(root->left) - 1);
}

int main() {
	node *root = nullptr;
	int n;
	int size = 0;
	cin >> n;
	while (n--) {
		int c, k;
		cin >> c >> k;
		if (c == 0) {
			cout << kth(root, size - k) << endl;
		} else if (c == 1) {
			root = insert(root, new node(k, n));
			++size;
		} else {
			root = erase(root, k, n);
			--size;
		}
	}
	return 0;
}
