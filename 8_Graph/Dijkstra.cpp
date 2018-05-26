#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <ostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <algorithm>
#define PI acos(-1.0)
using namespace std;

struct compare {
	bool operator()(const pair<int, double>& a, const pair<int, double>& b) {
		return a.second > b.second;
	}
};
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

void Dijkstra(string, string);

int main() {
	ios_base::sync_with_stdio(false);
	read("alabama.txt");
	adjacency("roadList2.txt");

	string operand;
	do {
		string src, dst;
		cout << "$ ";
		getline(cin, operand);
		istringstream store(operand);
		getline(store, src, '\t');
		getline(store, dst);
		Dijkstra(src, dst);
	} while (operand != "eixt");
}

//repeat n-1
void Dijkstra(string src, string dst) {
	vector<node>::iterator u = lower_bound(vec.begin(), vec.end(), src, lCmp);
	vector<node>::iterator v = lower_bound(vec.begin(), vec.end(), dst, lCmp);
	int i = u - vec.begin(), j = v - vec.begin();
	vector<double> dist(14378, INT_MAX);
	priority_queue <pair<double, int>,vector<pair<double,int>>,compare> pq;
	pq.push(make_pair(i, 0));

	while (!pq.empty()) {
		int here = pq.top().first;
		cout << vec[here].place << "\n";
		double cost = pq.top().second;
		if (j == here) break;
		pq.pop();

		if (dist[here] < cost) continue;

		for (pair<vector<node>::iterator, double> v : vec[here].edge) {
			int there = v.first - vec.begin();
			double nextDist = cost + v.second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(there, nextDist));
			}
		}
	}
	cout << "Distance From Source :: " << dist[j] << "\n";
}