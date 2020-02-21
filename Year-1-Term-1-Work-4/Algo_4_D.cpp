#include <iostream>
#include <vector>

using namespace std;

void print_items(int n, int w, vector <int> &weight, vector <vector <int> > &dp) {
	if (dp[n][w] == 0)
		return;
	if (dp[n][w] == dp[n - 1][w]) {
		print_items(n - 1, w, weight, dp);
	} else {
		print_items(n - 1, w - weight[n], weight, dp);
		cout << n << ' ';
	}
}

int count_items(int n, int w, vector <int> &weight, vector <vector <int> > &dp) {
	if (dp[n][w] == 0)
		return 0;
	if (dp[n][w] == dp[n - 1][w])
		return count_items(n - 1, w, weight, dp);
	return 1 + count_items(n - 1, w - weight[n], weight, dp);
}

int main() {
	freopen("knapsack.in", "r", stdin);
	freopen("knapsack.out", "w", stdout);
	int n, w;
	cin >> n >> w;
	vector <int> cost(n + 1), weight(n + 1);
	vector <vector <int> > dp(n + 1, vector <int>(w + 1));
	for (int i = 1; i <= n; ++i)
		cin >> weight[i];
	for (int i = 1; i <= n; ++i)
		cin >> cost[i];
	for (int i = 0; i <= n; ++i)
		dp[i][0] = 0;
	for (int i = 0; i <= w; ++i)
		dp[0][i] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= w; ++j)
			if (j >= weight[i])
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + cost[i]);
			else
				dp[i][j] = dp[i - 1][j];
	cout << count_items(n, w, weight, dp) << endl;
	print_items(n, w, weight, dp);
	return 0;
}
