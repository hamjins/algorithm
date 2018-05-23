#include <iostream>
#include <fstream>
using namespace std;

class Maze {
	//2차원 배열 동적 생성
	int** maze;
	//K>dist인 경로 개수
	int dist;
	int N, K;
	
	//열거형. WALLCOLOR =1 , PATHCOLOR =2 상수 지정 
	enum { WALLCOLOR = 1, PATHCOLOR };

public:
	//파일입출력 레퍼런스(주소,별명)로 받기
	Maze(ifstream &in);
	void find_dist(int x, int y, int dist);
	int get_dist() { return dist; }
	void print();
	~Maze();
};

//직접 만든 생성자, JAVA 생성자와 비슷 ex) Student student=new Student; .. . 
Maze::Maze(ifstream &in): dist(0) {
	//in : txt파일에서 입력 받아오기
	in >> N;
	//2차원 배열 N*N 동적할당 
	maze = new int*[N];
	for (int i = 0; i < N; i++) maze[i] = new int[N];
	//in : maze[i][j] 에 txt파일 입력 받아오기
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) in >> maze[i][j];
	}
	//K 값 받아오기
	in >> K;
}

void Maze::find_dist(int x, int y, int dist) {
	if (x < 0 || y < 0 || x >= N || y >= N) return;
	//dist > K 이면, 함수 종료
	else if (dist > K) return;
	//벽이거나, 이미 지나온 길이면 함수 종료
	else if (maze[x][y] == WALLCOLOR || maze[x][y] == PATHCOLOR) return;
	else if (x == N - 1 && y == N - 1) {
		//this 포인터 : 멤버변수 지칭 (매개변수 dist와 같은 변수이름이라 this 포인터 이용)
		++(this->dist); return;
	}
	else {
		//현재 좌표 위치 표시
		maze[x][y] = PATHCOLOR;
		find_dist(x - 1, y, dist + 1); find_dist(x, y + 1, dist + 1); find_dist(x + 1, y, dist + 1); find_dist(x, y - 1, dist + 1);
		//좌표 초기화(다른 경로도 확인해야 하므로 필요)
		maze[x][y] = 0;
	}
}

void Maze::print() {
	//멤버변수 배열 프린트
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) printf("%d ", maze[i][j]);
		printf("\n");
	}
}

//소멸자, 동적 할당 시켜준 변수는 메모리에서 자동 해제 안되므로 직접 해제 
Maze::~Maze() {
	//포인터 배열이 가르키는 인덱스마다 배열 메모리 해제
	for (int i = 0; i < N; i++)delete[]maze[i];
	//포인터 배열 메모리 해제 
	delete[]maze;
}

int main() {
	int T;
	//T <=10 이므로, Maze 객체를 가리킬 수 있는 포인터 배열 10개만 선언한다
	Maze *maze[10];
	//파일입출력 받아오기
	ifstream in("input.txt");
	in >> T;
	for (int i = 0; i < T; i++) {
		//maze[0]~maze[T-1] 만큼 Maze 객체 생성
		maze[i] = new Maze(in);
		maze[i]->find_dist(0, 0, 0);
		printf("%d\n", maze[i]->get_dist());
	}
}