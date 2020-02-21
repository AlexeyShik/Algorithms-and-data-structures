#include <stdio.h>
#include <stdlib.h>

int main(){
	int t;
	scanf("%d", &t);
	int *q = (int*)malloc(2 * sizeof(int));
	size_t i, j, sz = 0, next_sz = 4, beg = 0;
	for (i = 0; i < t; ++i){
		char c;
		scanf(" %c", &c);
		if (c == '+'){
			if (sz + 1 == next_sz){
				next_sz *= 2;
				int *tmp = (int*)malloc(next_sz * sizeof(int));
				for (j = 0; j < sz; ++j)
					tmp[j] = q[j];
				q = tmp;
			}
			int x = i;
			scanf(" %d", &x);
			q[sz++] = x;
		}
		else{
			printf("%d\n", q[beg]);
			beg++;
		}
	}
	free(q);
	return 0;
}
