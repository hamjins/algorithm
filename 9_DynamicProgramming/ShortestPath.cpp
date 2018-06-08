#include <iostream>
#include <fstream>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

int N, M, s, t;
int map[100][100];
int dist[100][100];
int sol[100][100];

void input(ifstream& in) {
   in >> N >> M;
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         if (i != j) map[i][j] = 0xFFFF;
         else map[i][j] = 0;
      }
   }

   for (int i = 0; i < M; i++) {
      int u = 0, v = 0;
      in >> u >> v;
      in >> map[u][v];
   }
   in >> s >> t;
}
int ans();

int main() {
   ifstream in("input1.txt");
   input(in);
   cout << ans() << "\n";
}

int ans() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			dist[i][j] = map[i][j];
			if (dist[i][j] != 0xfff) sol[i][j] = 1;
		}
	}

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					sol[i][j] = 1;
				}
				else if (i != k && j != k && dist[i][j] == dist[i][k] + dist[k][j]) {
					sol[i][j]++;
				}
			}
		}
	}
	return sol[s][t];
}
