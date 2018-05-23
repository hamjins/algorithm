#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <ctime>
#define NHASH 4093  //size of hash table
#define MULTIPLIER 31
using namespace std;

typedef struct suffix {
	string sword; //suffix
	int freq;    //등장횟수
	suffix *next;//다음 노드의 주소
}suffix;

typedef struct prefix {
	string pword1; //prefix를 구성하는 첫 단어
	string pword2; //prefix를 구성하는 두 번째 단어
	suffix *suf;   //suffix들의 연결리스트의 첫 번째 노드 주소
	int sumFreq;   //suffix들의 등장횟수(freq)의 합
}prefix;

typedef struct node {
	prefix* data;
	node* next;
}node;

node* htable[NHASH]; // hash table

unsigned int Hash(string key1, string key2) {
	unsigned int h = 0;
	vector<unsigned char> vec1(key1.begin(), key1.end());
	vector<unsigned char> vec2(key2.begin(), key2.end());
	vector<unsigned char>::iterator iter;
	for (iter = vec1.begin(); iter != vec1.end(); iter++) h = MULTIPLIER*h + *iter;
	for (iter = vec2.begin(); iter != vec2.end(); iter++) h = MULTIPLIER*h + *iter;
	return h%NHASH;
}

node* createNode(string key1, string key2, string suf) {
	node* newNode = new node;
	newNode->data = new prefix;
	newNode->data->suf = new suffix;
	newNode->next = NULL;
	newNode->data->pword1 = key1;
	newNode->data->pword2 = key2;
	newNode->data->sumFreq = 1;

	newNode->data->suf->sword = suf;
	newNode->data->suf->freq = 1;
	newNode->data->suf->next = NULL;
	return newNode;
}

void read(string);
void input(string, string, string);
void print();

int main() {
	ios_base::sync_with_stdio(false);
	read("HarryPotter.txt");
	print();
}

void read(string filename) {
	ifstream file(filename);
	string inputstring = "";
	string line, word;
	std::deque<string> deq;
	bool addflag = false;

	//tightly attach when '-' exist on last
	while (!getline(file, line).eof()) {
		line = line.erase(line.find_last_not_of(" \t\n\v") + 1);
		//if (line.size() != 0) line = line.erase(0, line.find_first_not_of(" \t\n\v"));
		if (line.size() > 0 && line[line.size() - 1] == '-') {
			addflag = true;
			line.pop_back();
		}
		inputstring += line;
		if (addflag) continue;
		istringstream sstream(inputstring);
		while (getline(sstream, word, ' ')) {
			deq.push_back(word);
			if (deq.size() == 3) {
				input(deq[0], deq[1], deq[2]);
				deq.pop_front();
			}
		}
		if (!addflag) { inputstring = ""; }
	}
}

void input(string key1,string key2, string suf) {
	node* newNode = createNode(key1, key2, suf);
	unsigned int i = Hash(key1, key2);

	if (htable[i] == nullptr) htable[i] = newNode;
	else {
		node* cur = htable[i];
		node* p;
		while (cur) {
			if ((cur->data->pword1 == newNode->data->pword1) && (cur->data->pword2 == newNode->data->pword2)) {
				cur->data->sumFreq++;

				suffix* scur = cur->data->suf;
				suffix* sp = nullptr;
				while (scur) {
					if (scur->sword == newNode->data->suf->sword) {
						scur->freq++; break;
					}
					sp = scur;
					scur = scur->next;
				}
				if (scur == nullptr) sp->next = newNode->data->suf;
				break;
			}
			p = cur;
			cur = cur->next;
		}
		if (cur == nullptr) p->next = newNode;
	}
}

void print() {
	srand((unsigned)time(NULL));
	string first = "CHAPTER";
	string second = "ONE";
	vector<string> vec;
	unsigned int i = Hash(first, second);

	node* cur = htable[i];
	cout << cur->data->pword1 << ' ' << cur->data->pword2 << ' ';
	for (int n = 0; n < 998; n++) {
		cur = htable[i];
		while (cur) {
			if (cur->data->pword1 == first &&cur->data->pword2 == second) break;
			cur = cur->next;
		}

		if (cur == nullptr || cur->data->suf == nullptr) break;
		suffix* scur = cur->data->suf;
		while (scur) {
			for (int k = 0; k < scur->freq; k++) vec.push_back(scur->sword);
			scur = scur->next;
		}
		
		unsigned int suf = rand() % vec.size();
		cout << vec[suf] << ' ';
		first = cur->data->pword2;
		second = vec[suf];
		vec.clear();
		i = Hash(first, second);
	}
}