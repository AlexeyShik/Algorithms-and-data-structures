#include <stdio.h>
#include <stdlib.h>

int main(){
	int t;
	scanf("%d", &t);
	int *st = (int*)malloc(2 * sizeof(int));
	size_t i, j, sz = 0, next_sz = 4;
	for (i = 0; i < t; ++i){
		char c;
		scanf(" %c", &c);
		if (c == '+'){
			sz++;
			if (sz + 1 == next_sz){
				next_sz *= 2;
				int *tmp = (int*)malloc(next_sz * sizeof(int));
				for (j = 0; j < sz; ++j)
					tmp[j] = st[j];
				int *a = tmp;
				tmp = st;
				st = a;
				free(tmp);
			}
			if (4 * sz < next_sz){
				next_sz /= 2;
				int *tmp = (int*)malloc(next_sz * sizeof(int));
				for (j = 0; j < sz; ++j)
					tmp[j] = st[j];
				int *a = tmp;
				tmp = st;
				st = a;
				free(tmp);
			}
			int x = i;
			scanf(" %d", &x);
			st[sz] = x;
		}
		else{
			printf("%d\n", st[sz]);
			sz--;
		}
	}
	free(st);
	return 0;
}
