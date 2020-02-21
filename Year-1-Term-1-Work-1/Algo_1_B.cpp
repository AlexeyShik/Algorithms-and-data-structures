#include <stdio.h>
#include <stdlib.h>

struct list {
	list *back;
	int val;
};

int main() {
	unsigned int t;
	scanf("%d", &t);
	list *curr = (list*)malloc(sizeof(list));
	curr->back = nullptr;
	curr->val = -1e9;
	for (unsigned i = 0; i < t; ++i) {
		char c;
		scanf(" %c", &c);
		if (c == '+') {
			int x;
			scanf(" %d", &x);
			list *tmp = (list*)malloc(sizeof(list));
			tmp->val = x;
			tmp->back = curr;
			curr = tmp;
		} else {
			printf("%d\n", curr->val);
			list *tmp = curr->back;
			free(curr);
			curr = tmp;
		}
	}
	return 0;
}
