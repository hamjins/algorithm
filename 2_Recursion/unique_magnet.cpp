#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
using namespace std;

int t, k;
int map[4][8];
bool visited[4];

void turn(int num, int wise) {
	if (wise == 1) {
		int n = map[num][7];
		for (int i = 7; i > 0; i--) map[num][i] = map[num][i - 1];
		map[num][0] = n;
	}
	else {
		int n = map[num][0];
		for (int i = 0; i < 7; i++)map[num][i] = map[num][i + 1];
		map[num][7] = n;
	}
}

void solve(int num, int wise) {
	visited[num] = true;
	//¿À¸¥ÂÊ
	if (num < 3 && map[num][2] != map[num + 1][6] && !visited[num + 1]) solve(num + 1, -1 * wise);
	if (num > 0 && map[num][6] != map[num - 1][2] && !visited[num - 1]) solve(num - 1, -1 * wise);
	turn(num, wise);
}

void initVistied() {
	for (int i = 0; i < 4; i++) visited[i] = false;
}

int getResult() {
	int ans = 0;
	for (int i = 0; i < 4; i++) {
		if (map[i][0] == 1) ans += (1 << i);
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		cin >> k;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) cin >> map[i][j];
		}

		int num, wise;
		while (k--) {
			cin >> num >> wise;
			solve(num - 1, wise);
			initVistied();
		}
		cout << "#" << tc << " " << getResult() << "\n";
	}
}