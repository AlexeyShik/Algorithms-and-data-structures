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
    node(ll val, ll id0, ll pr) {
        x = val;
        sz = 1;
        id = id0;
        y = pr;
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

node * merge(node * root1, node * root2) {
    if (!root1)
        return root2;
    if (!root2)
        return root1;
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

vector <pair <pair <ll, ll>, ll> > v, ans;

ll fill(node *root, ll p = -1) {
	if (!root)
		return -1;
	ans[(int)root->id].first.first = p;
	ans[(int)root->id].first.second = fill(root->left, root->id);
	ans[(int)root->id].second = fill(root->right, root->id);
	return root->id;
}

int main() {
	fastio;
	int n;
	cin >> n;
	v.resize(n);
	ans.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i].first.first >> v[i].first.second;
		v[i].second = i;
	}
	sort(v.begin(), v.end());
	queue <node*> q;
	for (int i = 0; i < n; ++i)
		q.push(new node(v[i].first.first, v[i].second, v[i].first.second));
	while (q.size() > 1) {
		queue <node*> nq;
		while (q.size() > 1) {
			node *q1 = q.front();
			q.pop();
			node *q2 = q.front();
			q.pop();
			nq.push(merge(q1, q2));
		}
		if (q.size() == 1) {
			nq.push(q.front());
			q.pop();
		}
		swap(q, nq);
	}
	fill(q.front());
	cout << "YES" << endl;
	for (auto x : ans)
		cout << x.first.first + 1 << ' ' << x.first.second + 1 << ' ' << x.second + 1 << endl;
	return 0;
}
