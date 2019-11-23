#include <stdio.h>
#include <stdlib.h>

struct list{
	int *front;
	int *back;
	int val;
};

int main(){
	int t;
	scanf("%d", &t);
	list *curr = malloc(sizeof(list));
	curr->front = curr->back = nullptr;
	curr->val = -1e9;
	size_t i, j;
	for (i = 0; i < t; ++i){
		char c;
		scanf(" %c", &c);
		if (c == '+'){
			sz++;
			int x;
			scanf(" %d", &x);
			list *tmp = malloc(sizeof(list));
			tmp->val = x;
			tmp->back = curr;
			tmp->front = nullpr;
			curr = tmp;
		}
		else{
			printf("%d\n", curr->val);
			list *tmp = curr->back;
			free(curr);
			curr = tmp;
		}
	}
	free(st);
	return 0;
}
