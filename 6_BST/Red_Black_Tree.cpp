#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
#include <iomanip>
using namespace std;

enum { name, company, address, zipcode, phones, email, red, black };

typedef struct People {
public:
	string pd[6];
	string pdl[6] = { "name","Company","Address","Zipcode","Phones","Email" };
	
	void print_struct() {
		cout << pd[name] << endl;
		for (int i = 1; i < 6; i++) cout << "\t" + pdl[i] + ":" << pd[i] << endl;
	}
}People;

class node{
public:
	People key;
	node* left;
	node* right;
	node* parent;
	int color;

	node(People key) :left(nullptr), right(nullptr), parent(nullptr) {
		for (int i = 0; i < 6; i++)
			this->key.pd[i] = key.pd[i];
	}
};


class BinaryTree {
public:
	node* root = nullptr;
	node* current;

	int getNodeColor(node* src) { return src != nullptr ? src->color : black; }
	
	node* SEARCH(string key) {
		current = root;
		while (current != nullptr&&current->key.pd[0] != key) {
			if (current->key.pd[0] < key) current = current->right;
			else current = current->left;
		}
		return current;
	}

	void find(string key) {
		node* y;
		current = root;
		while (current != nullptr&&current->key.pd[0] != key) {
			y = current;
			if (current->key.pd[0] < key) current = current->right;
			else current = current->left;
		}
		/*
		if(p->data.info[name]==name) p->data.print(); return p;
		if(p->data.info[name]>name) ceiling = p; find(p->left,name);
		if(p->data.info[name]<name) floor = p; find(p->right,name);
		*/
		if (current==nullptr) {
			People* newpeople = new People;
			newpeople->pd[0] = key;
			node* NewNode = INSERT(*newpeople);

			cout << "floor:: ";
			if(predecsessor(NewNode)!=nullptr)	print(predecsessor(NewNode));
			else cout << "There is no predecsessor" << endl;

			cout << "ceiling:: ";
			if(succesor(NewNode)!=nullptr) print(succesor(NewNode));
			else cout << "There is no succesor" << endl;
			DELETE(key);
			return;
		}
		else print(current);
	}

	//keep binary search tree property
	void leftRotate(node* x) {
			node* y = x->right;
			x->right = y->left;

			if (x->right != nullptr)x->right->parent = x;

			y->parent = x->parent;

			if (x->parent == nullptr) root = y;
			else if (x == x->parent->left) x->parent->left = y;
			else x->parent->right = y;
			y->left = x;
			x->parent = y;
	}

	void rightRotate(node *x) {
			node* y = x->left;
			x->left = y->right;

			if (x->left != nullptr) x->left->parent = x;
			y->parent = x->parent;

			if (x->parent == nullptr) root = y;
			else if (x == x->parent->left) x->parent->left = y;
			else x->parent->right = y;

			y->right = x;
			x->parent = y;
	}

	void RB_INSERT_FIXUP(node* z) {
		while (getNodeColor(z->parent) == red) {
			if (z->parent == z->parent->parent->left) {
				node* y = z->parent->parent->right;
				//case 1
				if (getNodeColor(y)== red) {
					z->parent->color = black;
					y->color = black;
					z->parent->parent->color = red;
					z = z->parent->parent;
				}
				else {
					//case 2
					if (z == z->parent->right) {
						z = z->parent;
						leftRotate(z);
					}
					//case 3
					z->parent->color = black;
					z->parent->parent->color = red;
					rightRotate(z->parent->parent);
				}
			}
			else {
				node* y = z->parent->parent->left;
				if (getNodeColor(y) == red) {
					z->parent->color = black;
					y->color = black;
					z->parent->parent->color = red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->left) {
						z = z->parent;
						rightRotate(z);
					}
					z->parent->color = black;
					z->parent->parent->color = red;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = black;
	}

	void RB_DELETE_FIXUP(node* x, node* parent) {
		while (x != root && getNodeColor(x) == black) {
			if (x == parent->left) {
				node* w = parent->right;
				if (getNodeColor(w) == red) {
					w->color = black;
					parent->color = red;
					leftRotate(parent);
					w = parent->right;
				}
				if (getNodeColor(w->left) == black && getNodeColor(w->right) == black) {
					w->color = red;
					x = parent;
				}
				else if (getNodeColor(w->right) == black) {
					w->left->color = black;
					w->color = red;
					rightRotate(w);
					w = parent->right;
				}
				if (getNodeColor(w) == black&&getNodeColor(w->right) == red) {
					w->color = parent->color;
					parent->color = black;
					w->right->color = black;
					leftRotate(parent);
					x = root;
				}
			}
			else {
				node* w = parent->left;
				if (w->color == red) {
					w->color = black;
					w->parent->color = red;
					rightRotate(parent);
					w = parent->left;
				}
				if (getNodeColor(w->right) == black&&getNodeColor(w->left) == black) {
					w->color = red;
					x = parent;
				}
				else if (getNodeColor(w->left) == black) {
					w->right->color = black;
					w->color = red;
					leftRotate(w);
					w = parent->left;
				}
				if (getNodeColor(w) == black&&getNodeColor(w->left) == red) {
					w->color = parent->color;
					parent->color = black;
					w->left->color = black;
					rightRotate(parent);
					x = root;
				}
			}
		}
		x->color = black;
	}

	node* minimum(node* root) {
		current = root;
		while (current->left != nullptr) current = current->left;
		return current;
	}
	node* maximum(node* root) {
		current = root;
		while (current->right != nullptr) current = current->right;
		return current;
	}
	node* succesor(node* tmp) {
		current = tmp;
		if (current->right != nullptr) return minimum(current->right);
		node* y = current->parent;
		while (y != nullptr&&current == y->right) {
			current = y;
			y = y->parent;
		}
		return y;
	}
	node* predecsessor(node *tmp) {
		current = tmp;
		if (current->left != nullptr) return maximum(current->left);
		node* y = current->parent;
		while (y != nullptr&&current == y->left) {
			current = y;
			y = y->parent;
		}
		return y;
	}

	node* INSERT(People key) {
		node* y = nullptr;
		current = root;
		node* NewNode = new node(key);
		while (current != nullptr) {
			y = current;
			if (current->key.pd[0] < key.pd[0]) current = current->right;
			else current = current->left;
		}
		NewNode->parent = y;
		if (y == nullptr) root = NewNode;
		else if (y->key.pd[0] < key.pd[0]) y->right = NewNode;
		else y->left = NewNode;
		NewNode->left = nullptr;
		NewNode->right = nullptr;
		NewNode->color = red;
		RB_INSERT_FIXUP(NewNode);
		return NewNode;
	}
	void DELETE(string key) {
		node* z = SEARCH(key);
		node* x;
		node* y;
		if (z->left == nullptr || z->right == nullptr) y = z;
		else y = succesor(z);
		//왼쪽자식이 nullptr이 아니라면, X는 y의 왼쪽자식
		if (y->left != nullptr) x = y->left;
		else x = y->right;
		
		if (x != nullptr) x->parent = y->parent;
		if (y->parent == nullptr) root = x;
		else if (y == y->parent->left) y->parent->left = x;
		else y->parent->right = x;
		
		if (y != z) z->key = y->key;
		if (y->color == black) RB_DELETE_FIXUP(x,y->parent);
		delete y;
	}

	void inorder(node* root) {
		if (root == nullptr) return;
		inorder(root->left);
		print(root);
		inorder(root->right);
	}
	void trace(string key) {
		current = root;
		while (current != nullptr&&current->key.pd[0] != key) {
			print(current);
			if (current->key.pd[0] < key) current = current->right;
			else current = current->left;
		}
		print(current);
	}

	void print(node* current) {
		cout << current->key.pd[name] << endl;
		for (int i = 1; i < 6; i++) cout << "\t" + current->key.pdl[i] + ":" << current->key.pd[i] << endl;
	}
	void save(ofstream& out,node* current) {
		if (current == nullptr) return;
		save(out, current->left);
		out <<setw(10)<< left<<current->key.pd[0] << "|";
		out << setw(30) << left << current->key.pd[1] << "|";
		out << setw(45) << left << current->key.pd[2] << "|";
		out << setw(10) << left << current->key.pd[3] << "|";
		out << setw(15) << left << current->key.pd[4] << "|";
		out << current->key.pd[5] << endl;
		save(out, current->right);
	}

	bool isRedBlackTree() {
		if (root == nullptr)
			return true;
		if (root->color == red)
			return false;
		return isRedBlackTree(root) != -1;
	}

	int isRedBlackTree(node* x) {
		if (x == nullptr)
			return 1;
		if (x->color == red && (x->left != nullptr && x->left->color == red || x->right != nullptr && x->right->color == red))
			return -1;
		int result1 = isRedBlackTree(x->left);
		if (result1 == -1)
			return -1;
		int result2 = isRedBlackTree(x->right);
		if (result2 == -1 || result1 != result2)
			return -1;
		return result1 + (x->color == black ? 1 : 0);
	}

	node* LCA(node* root, node* x, node *y) {
		if (root == nullptr) return nullptr;

		if (root->key.pd[0] > x->key.pd[0] && root->key.pd[0] > y->key.pd[0]) LCA(root->left, x, y);

		if (root->key.pd[0] < x->key.pd[0] && root->key.pd[0] < y->key.pd[0]) LCA(root->right, x, y);
		return root;
	}

	bool isBST(node* root, node* max, node* min) {
		if (root != nullptr) {
			if (root->key.pd[0] > max->key.pd[0] || root->key.pd[0] < min->key.pd[0]) return false;
			return isBST(root->left, min, root) && isBST(root->right, root, max);
		}
		else return true;
	}

	int getDiameter(node* root) {

	}
};

void MakeTreefromFile(BinaryTree* tmp, string filename);

int main() {
	ios_base::sync_with_stdio(false);
	BinaryTree tmp;
	string operand;
	istringstream store;
	do {
		string first_word; // read < file name >
		cout << "$ ";
		//표준 입출력
		getline(cin, operand);

		istringstream store(operand);
		getline(store, first_word, ' ');

		if (first_word == "read") {
			string filename;
			getline(store, filename, ' ');
			MakeTreefromFile(&tmp, filename);
		}
		else if (operand == "list") tmp.inorder(tmp.root);
		else if (first_word == "trace") {
			string target;
			getline(store, target, ' ');
			tmp.trace(target);
		}
		else if (first_word == "find") {
			string target;
			getline(store, target, ' ');
			tmp.find(target);
		}
		else if (first_word == "delete") {
			string target;
			getline(store, target, ' ');
			tmp.DELETE(target);
		}
		else if (first_word == "save") {
			string target;
			getline(store, target, ' ');
			ofstream out(target);
			tmp.save(out, tmp.root);
		}
		else if (operand == "is red-black tree") {
			printf("%s \n", (tmp.isRedBlackTree()) ? "true" : "false");
		}
	} while (operand != "exit");
}

void MakeTreefromFile(BinaryTree* tmp, string filename) {
	ifstream file(filename);
	string line, stn, word;
	//한 줄 읽어오기
	/*
	string의 getline 함수
	getline(stream,string)
	*/
	while (getline(file, line))
	{
		People newpeople;
		istringstream lstream(line);
		// | 로 나누고
		int pindex = name;
		while (getline(lstream, stn, '|')) {
			istringstream sstream(stn);
			string inputstring("");
			// 공백으로 나눴다가 타이트하게 다시붙임
			while (getline(sstream, word, ' ')) {
				if (!word.empty())
					inputstring += word;
			}
			// 구조체에 넣구요
			newpeople.pd[pindex++] = inputstring;
		}
		tmp->INSERT(newpeople);
	}
}