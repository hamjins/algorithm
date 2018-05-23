#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#define PI acos(-1.0)
using namespace std;
int n;
//place, longitude, latitude
typedef struct node {
	string place;
	double lon, lat;
	vector<pair<vector<node>::iterator, double>> edge;
}node;
bool sCmp(node& a, node& b) {
	return a.place < b.place;
}
bool lCmp(node& a, string place) {
	return a.place < place;
}

vector<node> vec;
bool visited[14378];
int dist[14378];
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
	sort(vec.begin(), vec.end(), sCmp);
}

void adjacency(string filename) {
	ifstream file(filename);
	string line, word, tmp = "";
	vector<node>::iterator i, j;
	while (getline(file, line)) {
		pair<vector<node>::iterator, double> newPair;
		istringstream lstream(line);
		getline(lstream, word, '\t');
		if (word != tmp) {
			i = lower_bound(vec.begin(), vec.end(), word, lCmp);
			tmp = word;
		}
		getline(lstream, word, '\t');
		j = lower_bound(vec.begin(), vec.end(), word, lCmp);
		newPair.first = j;
		newPair.second = calNodeDistance(*i, *j);
		int src = i - vec.begin(), dst = j - vec.begin();
		vec[src].edge.push_back(newPair);
		newPair.first = i;
		vec[dst].edge.push_back(newPair);
	}
}

void BFS(vector<node>::iterator v);
void DFS(ofstream& out,int v);

int main() {
	ios_base::sync_with_stdio(false);
	read("alabama.txt");
	adjacency("roadList2.txt");

	string operand;
	do {
		string first_word;
		cout << "$ ";
		getline(cin, operand);

		istringstream store(operand);
		getline(store, first_word, ' ');
		if (first_word == "10HOPS") {
			for (int i = 0; i < 14378; i++) visited[i] = false;
			for (int i = 0; i < 14378; i++) dist[i] = 0;
			string src;
			getline(store, src);
			vector<node>::iterator iter = lower_bound(vec.begin(), vec.end(), src, lCmp);
			BFS(iter);
		}
		else if (first_word == "DFS") {
			for (int i = 0; i < 14378; i++) visited[i] = false;
			string src;
			getline(store, src);
			vector<node>::iterator iter = lower_bound(vec.begin(), vec.end(), src, lCmp);
			int v = iter - vec.begin();
			ofstream out("DFS.txt");
			DFS(out, v);
		}
	} while (operand != "exit");
}

void DFS(ofstream& out, int v) {
	visited[v] = true;
	n++;
	out <<  n<<" | "<<vec[v].place << "\t" << vec[v].lon << "\t" << vec[v].lat << endl;
	for (pair<vector<node>::iterator, double> u : vec[v].edge) {
		vector<node>::iterator itr = lower_bound(vec.begin(), vec.end(), u.first->place, lCmp);
		int dst = itr - vec.begin();
		if (!visited[dst]) DFS(out, dst);
	}
}

void BFS(vector<node>::iterator v) {
	queue<vector<node>::iterator> que;
	que.push(v);
	int fst = v - vec.begin();
	visited[fst] = true;

	while(!que.empty()){
		vector<node>::iterator itr = que.front();
		int src = itr - vec.begin();
		if (dist[src] > 10) break;
		que.pop();
		cout << vec[src].place << "\t" << vec[src].lon << "\t" << vec[src].lat << endl;
		for (pair<vector<node>::iterator, double> u : vec[src].edge) {
			vector<node>::iterator iter = lower_bound(vec.begin(), vec.end(), u.first->place, lCmp);
			int dst = iter - vec.begin();
			if (!visited[dst]) {
				dist[dst] = dist[src] + 1;
				que.push(u.first);
				visited[dst] = true;
			}
		}
	}
}