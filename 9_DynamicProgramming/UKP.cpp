#include <iostream>
#include <algorithm>
using namespace std;

int N, *v; //index: piece

void input() {
	cin >> N;
	v = new int[N + 1];
	for (int i = 1; i < N + 1; i++) cin >> v[i];
}
int ans(int, int);

int main() {
	ios_base::sync_with_stdio(false);
	input();
	cout << ans(N, N) << "\n";
	delete[]v;
}

int ans(int n, int W) {
	int *dp = new int[W + 1];
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i <= W; i++) {
		for (int w = 0; w <= n; w++) {
			for (int i = 1; i <= W; i++) {
				for (int w = 1; w <= n; w++) {
					if (w <= i) dp[i] = max(dp[i], dp[i - w] + v[w]);
				}
			}
			return dp[W];
		}
