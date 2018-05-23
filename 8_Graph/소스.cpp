#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

//vertex,edge
int N, M, V;

class graph {
	int** adjMat;
	vector<bool> visited;
public:
	graph() {
		adjMat = new int*[N];
		for (int i = 0; i < N; i++) adjMat[i] = new int[N];
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) adjMat[i][j] = 0;
		}
		for (int i = 0; i < N; i++) visited.push_back(false);
	}

	void addEdge(int src, int dst) {
		if (adjMat[src][dst] == 1 && adjMat[dst][src] == 1) return;
		adjMat[src][dst]++;
		adjMat[dst][src]++;
	}

	void BFS(int s) {
		queue<int> que;
		vector<bool> visited(N, false);
		que.push(s);
		visited[s] = true;
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			for (int i = 0; i < N; i++) {
				if (adjMat[u][i] == 1 && visited[i] == false) {
					que.push(i); visited[i] = true;
				}
			}
			cout << u + 1 << " ";
		}
	}

	void DFS(int s) {
		visited[s] = true;
		cout << s + 1 << " ";
		//for each node u adjacent to x do 
		for (int i = 0; i < N; i++) {
			if (adjMat[s][i] == 1 && visited[i] == false) DFS(i);
		}
	}

	//그래프가 disconnected 이거나 혹은 방향 그래프라면 DFS에 의해서 모든 노드가 방문되지 않을 수 있음
	void DFS_ALL() {
		for (int i = 0; i < 14378; i++) visited[i] = false;
		for (int v = 0; v < 14378; v++) {
			if (visited[v] == false) DFS(v);
		}
	}

	~graph() {
		for (int i = 0; i < N; i++) delete[]adjMat[i];
		delete[] adjMat;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin >> N >> M >> V;
	graph test;

	for (int i = 0; i < M; i++) {
		int src, dst;
		cin >> src >> dst;
		test.addEdge(src - 1, dst - 1);
	}
	test.DFS(V - 1);
	cout << endl;
	test.BFS(V - 1);
	cout << endl;
}

