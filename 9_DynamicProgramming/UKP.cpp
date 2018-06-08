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

	//무게제한 0부터 W까지
	for (int i = 0; i <= W; i++) {
		//0번 짐부터 n번 짐까지 순회하면서 최대 가치 찾기
		for (int w = 0; w <= n; w++) {
			//가방의 무게제한이 i번 짐의 무게보다 크다면, i번 짐을 챙겼을 때의 최대가치 계산
			if (w <= i) dp[i] = max(dp[i], dp[i - w] + v[w]);
		}
	}
	return dp[W];
}