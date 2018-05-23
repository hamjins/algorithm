#include <iostream>
#include <fstream>
using namespace std;

class Maze {
	//2���� �迭 ���� ����
	int** maze;
	//K>dist�� ��� ����
	int dist;
	int N, K;
	
	//������. WALLCOLOR =1 , PATHCOLOR =2 ��� ���� 
	enum { WALLCOLOR = 1, PATHCOLOR };

public:
	//��������� ���۷���(�ּ�,����)�� �ޱ�
	Maze(ifstream &in);
	void find_dist(int x, int y, int dist);
	int get_dist() { return dist; }
	void print();
	~Maze();
};

//���� ���� ������, JAVA �����ڿ� ��� ex) Student student=new Student; .. . 
Maze::Maze(ifstream &in): dist(0) {
	//in : txt���Ͽ��� �Է� �޾ƿ���
	in >> N;
	//2���� �迭 N*N �����Ҵ� 
	maze = new int*[N];
	for (int i = 0; i < N; i++) maze[i] = new int[N];
	//in : maze[i][j] �� txt���� �Է� �޾ƿ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) in >> maze[i][j];
	}
	//K �� �޾ƿ���
	in >> K;
}

void Maze::find_dist(int x, int y, int dist) {
	if (x < 0 || y < 0 || x >= N || y >= N) return;
	//dist > K �̸�, �Լ� ����
	else if (dist > K) return;
	//���̰ų�, �̹� ������ ���̸� �Լ� ����
	else if (maze[x][y] == WALLCOLOR || maze[x][y] == PATHCOLOR) return;
	else if (x == N - 1 && y == N - 1) {
		//this ������ : ������� ��Ī (�Ű����� dist�� ���� �����̸��̶� this ������ �̿�)
		++(this->dist); return;
	}
	else {
		//���� ��ǥ ��ġ ǥ��
		maze[x][y] = PATHCOLOR;
		find_dist(x - 1, y, dist + 1); find_dist(x, y + 1, dist + 1); find_dist(x + 1, y, dist + 1); find_dist(x, y - 1, dist + 1);
		//��ǥ �ʱ�ȭ(�ٸ� ��ε� Ȯ���ؾ� �ϹǷ� �ʿ�)
		maze[x][y] = 0;
	}
}

void Maze::print() {
	//������� �迭 ����Ʈ
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) printf("%d ", maze[i][j]);
		printf("\n");
	}
}

//�Ҹ���, ���� �Ҵ� ������ ������ �޸𸮿��� �ڵ� ���� �ȵǹǷ� ���� ���� 
Maze::~Maze() {
	//������ �迭�� ����Ű�� �ε������� �迭 �޸� ����
	for (int i = 0; i < N; i++)delete[]maze[i];
	//������ �迭 �޸� ���� 
	delete[]maze;
}

int main() {
	int T;
	//T <=10 �̹Ƿ�, Maze ��ü�� ����ų �� �ִ� ������ �迭 10���� �����Ѵ�
	Maze *maze[10];
	//��������� �޾ƿ���
	ifstream in("input.txt");
	in >> T;
	for (int i = 0; i < T; i++) {
		//maze[0]~maze[T-1] ��ŭ Maze ��ü ����
		maze[i] = new Maze(in);
		maze[i]->find_dist(0, 0, 0);
		printf("%d\n", maze[i]->get_dist());
	}
}