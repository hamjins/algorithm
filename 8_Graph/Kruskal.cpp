#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#define PI acos(-1.0)
using namespace std;

//place, longitude, latitude
typedef struct node {
	string place;
	double lon, lat;
}node;

typedef struct edge {
	int u, v;
	double dist;

	bool operator <(edge &a) const {
		return this->dist < a.dist;
	}
}edge;
bool cmp(const edge& a, const edge& b) {
	return a.u < b.u;
}

vector<node> vec;
vector<edge> edg;
vector<edge> W;
int p[14378];
int SIZE[14378];

//converts the given degree to radian
double deg2rad(double deg) {
	return (double)(deg*PI / (double)180);
}
//converts the given radian to degree
double rad2deg(double rad) {
	return (double)(rad*(double)180 / PI);
}

double calDistance(double lat1, double lon1, double lat2, double lon2) {
	double theta, dist;
	theta = lon1 - lon2;
	dist = sin(deg2rad(lat1))*sin(deg2rad(lat2)) + cos(deg2rad(lat1))*cos(deg2rad(lat2))*cos(deg2rad(theta));
	dist = acos(dist);   dist = rad2deg(dist);
	dist = dist * 60 * 1.1515;
	dist = dist*1.609344; // convert mile to km
	dist = dist*1000.0; // convert km to m
	return dist;
}

double calNodeDistance(node Node1, node Node2) {
	return calDistance(Node1.lat, Node1.lon, Node2.lat, Node2.lon);
}

void read(string filename) {
	ifstream file(filename);
	string line, word;
	while (getline(file, line)) {
		node newNode;
		istringstream lstream(line);
		getline(lstream, word, '\t'); newNode.place = word;
		getline(lstream, word, '\t'); newNode.lon = atof(word.c_str());
		getline(lstream, word, '\t'); newNode.lat = atof(word.c_str());
		vec.push_back(newNode);
	}
}

struct find_roc {
	string place;
	find_roc(string nom) : place(nom) {}
	bool operator () (const node& m) const {
		return m.place == place;
	}
};

void adjacency(string filename) {
	ifstream file(filename);
	string line, word, tmp = "";
	vector<node>::iterator i, j;
	while (getline(file, line)) {
		edge temp;
		istringstream lstream(line);
		getline(lstream, word, '\t');
		if (word != tmp) {
			i = find_if(vec.begin(), vec.end(), find_roc(word));
			tmp = word;
		}
		getline(lstream, word, '\t');
		j = find_if(vec.begin(), vec.end(), find_roc(word));
		int src = i - vec.begin(), dst = j - vec.begin();
		temp.u = src; temp.v = dst; temp.dist = calNodeDistance(*i, *j);
		edg.push_back(temp);
	}
}

int FIND_SET_PC(int);
void WEIGHTED_UNION(int, int);
void Kruskal();
void print(ofstream&);

int main() {
	ios_base::sync_with_stdio(false);
	edg.reserve(42958);
	vector<edge> W;
	W.reserve(28754);
	read("alabama.txt");
	adjacency("roadList2.txt");
	for (int i = 0; i < 14378; i++) SIZE[i] = 1;
	ofstream out("mst.txt");
	Kruskal();
	print(out);
}

//WUPC(Weighted Union with Path Compression)
int FIND_SET_PC(int v) {
	while (v != p[v]) {
		p[v] = p[p[v]];
		v = p[v];
	}
	return p[v];
}

void WEIGHTED_UNION(int u, int v) {
	int x = FIND_SET_PC(u);
	int y = FIND_SET_PC(v);
	if (SIZE[x] > SIZE[y]) {
		p[x] = y;
		SIZE[x] = SIZE[x] + SIZE[y];
	}
	else {
		p[y] = x;
		SIZE[y] = SIZE[y] + SIZE[x];
	}
}

void Kruskal() {
	for (int i = 0; i < 14378; i++) p[i] = i;
	sort(edg.begin(), edg.end());
	for (int i = 0; i < 42958; i++) {
		//cout << FIND_SET_PC(edg[i].u) << "\t" << FIND_SET_PC(edg[i].v) << "\n";
		if (FIND_SET_PC(edg[i].u) != FIND_SET_PC(edg[i].v)) {
			edge tmp1, tmp2;
			tmp1.u = edg[i].u; tmp1.v = edg[i].v; tmp1.dist = edg[i].dist;
			W.push_back(tmp1);
			tmp2.u = edg[i].v; tmp2.v = edg[i].u; tmp2.dist = edg[i].dist;
			W.push_back(tmp2);
			WEIGHTED_UNION(edg[i].u, edg[i].v);
		}
	}
}

void print(ofstream& out) {
	sort(W.begin(), W.end(), cmp);
	int tmp = 0;
	out << tmp << " " << vec[0].lon << " " << vec[0].lat << " ";
	for (int i = 0; i < W.size(); i++) {
		if (W[i].u != tmp) {
			out << "\n";
			tmp = W[i].u;
			out << tmp << " " << vec[tmp].lon << " " << vec[tmp].lat << " ";
		}
		out << W[i].v << " ";
	}
}