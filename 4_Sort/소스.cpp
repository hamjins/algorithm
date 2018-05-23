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

	//�� ���
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
		string first_word; // read < file name > �� ���ؼ� 
		cout << "$ ";
		getline(cin, operand);

		istringstream store(operand);
		getline(store, first_word, ' ');

		if (first_word == "read") // ���� �����Կ� 
		{
			string filename;
			getline(store, filename, ' ');
			MakeVecfromFile(peoples, filename);
		}
		else if (operand == "sort by name") // �̸� �� ���� 
		{
			SortbyAttr(peoples, name);
		}
		else if (operand == "sort by address") // �ּ� �� ����
		{
			SortbyAttr(peoples, Address);
		}
		else if (operand == "print") // ���
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

//���ϴ� attribute�� ����
void SortbyAttr(vector<people>& vec, int attr) {
	//�񱳽Ŀ� lambda�� ����
	sort(std::begin(vec), std::end(vec), [attr](people a, people b) { return a.pd[attr] < b.pd[attr]; });
}

//�����
void PrintAll(vector<people> vec) {
	for (size_t i = 0; i<vec.size(); i++)
		vec[i].print();
}

void MakeVecfromFile(vector<people>& vec, string filename) {
	ifstream file(filename);
	string line, stn, word;
	//�� �� �о����
	/*
	string�� getline �Լ�
	getline(stream,string)
	*/
	while (getline(file, line))
	{
		people newpeople;
		istringstream lstream(line);
		// | �� ������
		int pindex = name;
		while (getline(lstream, stn, '|')) {
			istringstream sstream(stn);
			string inputstring("");
			// �������� �����ٰ� Ÿ��Ʈ�ϰ� �ٽú���
			while (getline(sstream, word, ' ')) {
				if (!word.empty())
					inputstring += " " + word;
			}
			// ����ü�� �ֱ���
			newpeople.pd[pindex++] = inputstring;
		}
		//���Ϳ��� �����ô�
		vec.push_back(newpeople);
	}
}