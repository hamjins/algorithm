#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
using namespace std;

int L[1000][1000], s[1000][1000];
string str1, str2;
deque<int> deq;
enum { lef, top, dia };

int ans(int, int);
void print();

int main() {
	cin >> str1 >> str2;
	cout << ans(str2.length(), str1.length()) << "\n";
	print();
}

int ans(int m, int n) {
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (str2.at(i - 1) == str1.at(j - 1)) {
				L[i][j] = L[i - 1][j - 1] + 1; s[i][j] = dia;
			}
			else if (L[i - 1][j] > L[i][j - 1]) {
				L[i][j] = L[i - 1][j]; s[i][j] = top;
			}
			else {
				L[i][j] = L[i][j - 1]; s[i][j] = lef;
			}
		}
	}
	return L[m][n];
}

void print() {
	int i = str2.length(), j = str1.length();
	while (i > 0 && j > 0) {
		if (s[i][j] == dia) {
			deq.push_front(i-1); --i, --j;
		}
		else if (s[i][j] == lef) --j;
		else --i;
	}
	for (int n : deq) cout << str2.at(n);
	cout << "\n";
}