#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;
struct list {
	list *back;
	int val;
	int maxim;
};

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	list *st1 = (list*)malloc(sizeof(list));
	list *st2 = (list*)malloc(sizeof(list));
	st1 = st2 = nullptr;
	int a, b, c, l1 = 0, l2 = 0;
	cin >> a >> b >> c;
	bool st2empty = true;
	long long sum = 0;
	for (register int i = 0; i < n; ++i) {
		list *tmpi = (list*)malloc(sizeof(list));
		int x;
		if (i < k) {
			cin >> x;
		} else {
			x = (a * l2 + b * l1 + c);
		}
		l2 = l1;
		l1 = x;
		tmpi->val = x;
		tmpi->maxim = st1 != nullptr ? std :: min(tmpi->val, st1->maxim) : tmpi->val;
		tmpi->back = st1;
		swap(st1, tmpi);
		if (!tmpi)
			free(tmpi);
		if (i + 1 >= m) {
			if (st2empty) {
				while (st1 != nullptr) {
					list *tmp = (list*)malloc(sizeof(list)), *ctmp = (list*)malloc(sizeof(list));
					tmp->val = st1->val;
					if (st2empty) {
						tmp->maxim = tmp->val;
					} else {
						tmp->maxim = min(tmp->val, st2->maxim);
					}
					tmp->back = st2;
					swap(st2, tmp);
					if (!tmp)
						free(tmp);
					if (st2empty) {
						st2empty = false;
					}
					ctmp = st1;
					st1 = st1->back;
					if (!ctmp)
						free(ctmp);
				}
			}
			long long ans = (st1 == nullptr ? st2->maxim : st1->maxim);
			if (st1 != nullptr && st2 != nullptr) {
				ans = min(st1->maxim, st2->maxim);
			}
			sum = (long long)ans + sum;
			list *tmp = (list*)malloc(sizeof(list));
			tmp = st2->back;
			free(st2);
			swap(st2, tmp);
			if (st2 == nullptr) {
				st2empty = true;
			}
		}
	}
	cout << sum;
	return 0;
}


/*10000000 15 5
283471207 23947205 3
17625384 939393931 1838388 912740247 290470294*/
