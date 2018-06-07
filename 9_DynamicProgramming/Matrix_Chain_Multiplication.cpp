#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int N, **m, *p, **s;
void input(ifstream&);
void ans(int);
void print();

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	input(in);
	ans(N);
	print();
	in.close();
}

void input(ifstream& in) {
	in >> N;
	p = new int[N + 1];
	m = new int*[N + 1];
	for (int i = 0; i < N + 1; i++) m[i] = new int[N + 1];
	s = new int *[N + 1];
	for (int i = 0; i < N + 1; i++) s[i] = new int[N + 1];
	for (int i = 0; i < N + 1; i++) in >> p[i];
}

//Optimal Substructure
void ans(int n) {
	for (int i = 1; i <= n; i++) s[1][i] = 1;
	for (int i = 1; i <= n; i++) m[i][i] = 0;
	for (int r = 1; r <= n - 1; r++) { //n-1
		for (int i = 1; i <= n - r; i++) { //°¢ ´ë°¢¼±ÀÇ °ªÀÇ °³¼ö
			int j = i + r; //col
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			for (int k = i + 1; k <= j - 1; k++) {
				if (m[i][j] > m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]) {
					m[i][j] = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
					s[i][j] = k;
				}
			}
		}
	}
	cout << m[1][n] << "\n";
}

void print() {
	vector<vector<int>> vec(N + 1, vector<int>(2, 0)); //1: right, 0:left
	bool* visited = (bool*)calloc(sizeof(bool), N + 1);
	for (int i = N; i > 2; i--) {
	    int	src = 0, dst = 0, cur = s[1][i];
		if (visited[cur]) continue;
		visited[cur] = true;
		vec[cur][1]++;
		vec[cur + 1][0]++;
		for (int j = cur + 1; j <= N; j++) {
			if (vec[j][1] != 0 || j == N) {
				dst = j; break;
			}
		}
		vec[dst][1]++;
		for (int k = cur; k >= 1; k--) {
			if (vec[k][0] != 0 || k == 1) {
				src = k; break;
			}
		}
		vec[src][0]++;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < vec[i][0]; j++) cout << "(";
		cout << "A" << i;
		for (int k = 0; k < vec[i][1]; k++) cout << ")";
	}
	cout << "\n";
}
