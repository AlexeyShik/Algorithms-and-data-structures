#include <iostream>

using namespace std;

struct list{
	list *back;
	char val;
};

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    string s;
    while (cin >> s) {
    	list* st = (list*)malloc(sizeof(list));
		st->back = nullptr;
		st->val = 'x';
		int corr = 1;
		for (register char c : s) {
			if (c == '(' || c == '[') {
				list *tmp = (list*)malloc(sizeof(list));
				tmp->back = st;
				tmp->val = c;
				st = tmp;
			} else {
				if ((c == ')' && st->val == '(') || (c == ']' && st->val == '[')) {
					list *tmp = st->back;
					free(st);
					st = tmp;
				} else {
    				corr = 0;
    			}
    		}
        }
        if (st->back != nullptr || corr == 0)
        	cout << "NO" << endl;
        else
			cout << "YES" << endl;
    }
    return 0;
}
