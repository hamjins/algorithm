#include <iostream>
#include <algorithm>
using namespace std;

class node {
public:
	int key;
	node* left;
	node* right;
	node* parent;

	node(int key) :key(key), left(NULL), right(NULL), parent(NULL) {}
};

class BST {
public:
	node* root = NULL;
	node* current;

	node* SEARCH(int key) {
		current = root;
		while (current != NULL&&current->key != key) {
			if (current->key < key) current = current->right;
			else current = current->left;
		}
		return current;
	}

	node* minimum(node* root) {
		current = root;
		while (current->left != NULL) current = current->left;
		return current;
	}
	node* maximum(node* root) {
		current = root;
		while (current->right != NULL) current = current->right;
		return current;
	}
	node* succesor(node* tmp) {
		current = tmp;
		if (current->right != NULL) return minimum(current->right);
		node* y = current->parent;
		while (y != NULL&&current == y->right) {
			current = y;
			y = y->parent;
		}
		return y;
	}
	node* predecsessor(node *tmp) {
		current = tmp;
		if (current->left != NULL) return maximum(current->left);
		node* y = current->parent;
		while (y != NULL&&current == y->left) {
			current = y;
			y = y->parent;
		}
		return y;
	}

	node* INSERT(int key) {
		node* y = NULL;
		current = root;
		node* NewNode = new node(key);
		while (current != NULL) {
			y = current;
			if (current->key < key) current = current->right;
			else current = current->left;
		}
		NewNode->parent = y;
		if (y == NULL) root = NewNode;
		else if (y->key < key) y->right = NewNode;
		else y->left = NewNode;
		return NewNode;
	}
	void DELETE(int key) {
		node* z = SEARCH(key);
		node* x;
		node* y;
		if (z->left == NULL || z->right == NULL) y = z;
		else y = succesor(z);
		//왼쪽자식이 NULL이 아니라면, X는 y의 왼쪽자식
		if (y->left != NULL) x = y->left;
		else x = y->right;

		if (x != NULL) x->parent = y->parent;
		if (y->parent == NULL) root = x;
		else if (y == y->parent->left) y->parent->left = x;
		else y->parent->right = x;

		if (y != z) z->key = y->key;
		delete y;
	}

	void inorder(node* root) {
		if (root == NULL) return;
		inorder(root->left);
		print(root);
		inorder(root->right);
	}

	void print(node* current) {
		cout << current->key << endl;
	}

	int getDiameter(node* root, int &ans) {
		int lHeight = 0, rHeight = 0;
		if (root == NULL) {
			ans = 0; return 0;
		}
		int lDia = getDiameter(root->left, lHeight);
		int rDia = getDiameter(root->right, rHeight);
		
		//find height
		ans = max(lHeight, rHeight) + 1;
		printf("%d %d \n", lHeight, rHeight);
		//passing the root or not
		return max(ans, max(lDia, rDia));
	}

	node* lowestCommonAncestor(node* x, node *y) {
		if (x== NULL || y == NULL) return NULL;
		if (x == y) return x;
		node* xParent = lowestCommonAncestor(x->parent, y);
		node* yParent = lowestCommonAncestor(x, y->parent);
		if (xParent == NULL&&yParent == NULL) return NULL;
		if (xParent != NULL&&yParent != NULL) return xParent;
		return ((xParent != NULL) ? xParent : yParent);
	}
};

int main() {
	BST test;
	int h = -90000;
	test.INSERT(10);
	test.INSERT(20);
	test.INSERT(5);
	test.INSERT(2);
	test.INSERT(1);
	test.INSERT(6);
	test.INSERT(8);
	test.INSERT(7);
	test.INSERT(0);
	node* x = test.SEARCH(4);
	node* y = test.SEARCH(2);
	printf("%d \n",test.getDiameter(test.root,h));
	test.print(test.lowestCommonAncestor(x, y));
}