#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>    
#include <fstream>
#include <ostream>
#include <vector>

using namespace std;

//enum for easy access to pd array
enum { name, Company, Address, Zipcode, Phones, Email };

typedef struct people {
	//person_detail
	string pd[6];
	//person_detail_label
	string pdl[6] = { "name","Company","Address","Zipcode","Phones","Email" };

	//걍 출력
	void print() {
		cout << pd[name] << endl;
		for (int i = 1; i<6; i++)
			cout << "\t" + pdl[i] + ":" << pd[i] << endl;
	}

}people;

void SortbyAttr(vector<people>& vec, int attr);
void PrintAll(vector<people> vec);
void MakeVecfromFile(vector<people>& vec, string filename);


int main()
{
	vector<people> peoples;
	string operand;
	istringstream store;
	do
	{
		string first_word; // read < file name > 을 위해서 
		cout << "$ ";
		getline(cin, operand);

		istringstream store(operand);
		getline(store, first_word, ' ');

		if (first_word == "read") // 파일 읽을게요 
		{
			string filename;
			getline(store, filename, ' ');
			MakeVecfromFile(peoples, filename);
		}
		else if (operand == "sort by name") // 이름 순 정렬 
		{
			SortbyAttr(peoples, name);
		}
		else if (operand == "sort by address") // 주소 순 정렬
		{
			SortbyAttr(peoples, Address);
		}
		else if (operand == "print") // 출력
		{
			PrintAll(peoples);
		}
		else if (operand != "exit")
		{
			cout << "Please check operand name:>\nread address.txt/sort by name/sort by address/print/exit\n";
		}
	} while (operand != "exit");

	return 0;
}

//원하는 attribute로 정렬
void SortbyAttr(vector<people>& vec, int attr) {
	//비교식에 lambda를 썼음
	sort(std::begin(vec), std::end(vec), [attr](people a, people b) { return a.pd[attr] < b.pd[attr]; });
}

//다출력
void PrintAll(vector<people> vec) {
	for (size_t i = 0; i<vec.size(); i++)
		vec[i].print();
}

void MakeVecfromFile(vector<people>& vec, string filename) {
	ifstream file(filename);
	string line, stn, word;
	//한 줄 읽어오기
	/*
	string의 getline 함수
	getline(stream,string)
	*/
	while (getline(file, line))
	{
		people newpeople;
		istringstream lstream(line);
		// | 로 나누고
		int pindex = name;
		while (getline(lstream, stn, '|')) {
			istringstream sstream(stn);
			string inputstring("");
			// 공백으로 나눴다가 타이트하게 다시붙임
			while (getline(sstream, word, ' ')) {
				if (!word.empty())
					inputstring += " " + word;
			}
			// 구조체에 넣구요
			newpeople.pd[pindex++] = inputstring;
		}
		//벡터에도 넣읍시다
		vec.push_back(newpeople);
	}
}