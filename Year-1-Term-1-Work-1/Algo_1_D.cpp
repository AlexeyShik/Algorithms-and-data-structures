#include <stdio.h>
#include <stdlib.h>

struct list {
	list *front;
	list *back;
	int val;
};

int main() {
	unsigned int t;
	scanf("%d", &t);
	list *tail = (list*)malloc(sizeof(list));
	tail->front = tail->back = nullptr;
	tail->val = -1e9;
	list *head = (list*)malloc(sizeof(list));
	tail->front = head;
	head->back = tail;
	head->front = nullptr;
	char f;
	scanf(" %c", &f);
	int y;
	scanf(" %d", &y);
	tail->val = y;
	for (unsigned i = 1; i < t; ++i) {
		char c;
		scanf(" %c", &c);
		if (c == '+') {
			int x;
			scanf(" %d", &x);
			head->val = x;
			list *tmp = (list*)malloc(sizeof(list));
			tmp->back = head;
			head->front = tmp;
			tmp->front = nullptr;
			head = tmp;
		} else {
			printf("%d\n", tail->val);
			list *tmp = tail->front;
			free(tail);
			tail = tmp;
		}
	}
	return 0;
}
