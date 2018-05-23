#include <iostream>
#include <fstream>

using namespace std;

class Maze {
	int** maze;
	int N;
	enum { WALLCOLOR = 1, PATHCOLOR, BLOCKEDCOLOR };
	class vec2 {
	public:
		int x;
		int y;
		vec2(int x, int y) : x(x), y(y) {};
		//dot product
		int operator *(vec2 d) { return x*d.x + y*d.y; };
		vec2 left() { return vec2(-y, x); };
		vec2 right() { return vec2(y, -x); };
	};
	bool collision_check(int x, int y) { return (x < 0 || y < 0 || x >= N || y >= N || maze[y][x] == WALLCOLOR); };
public:
	Maze(ifstream &in);
	bool print_sol(int x, int y, vec2 dir); //reculsive
	bool get_bpath() { return print_sol(0, 0, vec2(0, 0)); }; //starter
	void print();
	~Maze();
};

Maze::Maze(ifstream &in) {
	in >> N;
	maze = new int*[N];
	for (int i = 0; i < N; i++) {
		maze[i] = new int[N];
		for (int j = 0; j < N; j++) {
			in >> maze[i][j];
		}
	}
}

bool Maze::print_sol(int x, int y, vec2 dir) {
	//arrived
	if (x == N - 1 && y == N - 1) return true;
	//collision check
	if (collision_check(x, y)) return false;
	//status check
	if (maze[y][x] == BLOCKEDCOLOR) return false;
	//visit & record
	if (maze[y][x] == PATHCOLOR) maze[y][x]++;
	else maze[y][x] = PATHCOLOR;
	//init check
	if (dir*vec2(1, 1) == 0) {
		vec2 dirs[2] = { vec2(1,0),vec2(0,1) };
		if (print_sol(x + dirs[0].x, y + dirs[0].y, dirs[0]) ||
			print_sol(x + dirs[1].x, y + dirs[1].y, dirs[1]))
			return true;
		return false;
	}

	//foward check
	if (collision_check(x + dir.x, y + dir.y))
	{
		//turn~ turn~
		vec2 ldir = dir.left();
		vec2 rdir = dir.right();
		if (print_sol(x + ldir.x, y + ldir.y, ldir) || print_sol(x + rdir.x, y + rdir.y, rdir))
			return true;
		return false;
	}
	else return print_sol(x + dir.x, y + dir.y, dir); //going foward
}

void Maze::print(void) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
}

Maze::~Maze() {
	for (int i = 0; i < N; i++) {
		delete[] maze[i];
	}
	delete[] maze;
}

int main() {
	int T;
	Maze *maze;
	ifstream in("input.txt");
	in >> T;
	for (int i = 0; i < T; i++) {
		maze = new Maze(in);
		
		cout << ((maze->get_bpath()) ? "YES" : "NO") << endl;
		delete maze;
	}
	in.close();
}