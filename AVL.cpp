//Implementace operací s AVL stromem: insert, delete, find, findmin, findmax, next
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "Linked_list.h"
using namespace std;

int depth = 0;

class AVL_node {
	int data;
	int height;
	AVL_node* left;
	AVL_node* right;

	void check_height() {
		/* Ohodnocuje výšky vrchlů AVL stromu */
		if (left != NULL) left->check_height();
		if (right != NULL) right->check_height();
		if (!right && !left) this->height = 1;
		else if (!right) this->height = left->height + 1;
		else if (!left) this->height = right->height + 1;
		else this->height = max(right->height, left->height) + 1;
	};

	void left_rotation() {
		/* Provádí levou rotaci AVL stromu */
		int temp = data;
		data = right->data;
		right->data = temp;
		AVL_node* temp_branch = left;
		left = right->right;
		right->right = right->left;
		right->left = temp_branch;
		temp_branch = left;
		left = right;
		right = temp_branch;
	};

	void right_rotation() {
		/* Provádí pravou rotaci AVL stromu */
		int temp = data;
		data = left->data;
		left->data = temp;
		AVL_node* temp_branch = right;
		right = left->left;
		left->left = left->right;
		left->right = temp_branch;
		temp_branch = right;
		right = left;
		left = temp_branch;
	};

	void b_left_rotation() {
		/* Provádí velkou levou rotaci AVL stromu */
		int temp = data;
		data = right->left->data;
		right->left->data = temp;
		AVL_node* temp_branch = right->left->right;
		right->left->right = right->left->left;
		right->left->left = left;
		left = right->left;
		right->left = temp_branch;
	};

	void b_right_rotation() {
		/* Provádí velkou pravou rotaci AVL stromu */
		int temp = data;
		data = left->right->data;
		left->right->data = temp;
		AVL_node* temp_branch = left->right->left;
		left->right->left = left->right->right;
		left->right->right = right;
		right = left->right;
		left->right = temp_branch;
	};

	void balance() {
		/* Provádí balancování AVL stromu */
		int lh, rh;
		if (!left) lh = 0;
		else lh = left->height;
		if (!right) rh = 0;
		else rh = right->height;

		if (abs(lh - rh) <= 1) 	return;
		else
		{
			int lrh, llh, rlh, rrh;

			if (lh > rh) {
				if (!left->right) lrh = 0;
				else lrh = left->right->height;
				if (!left->left) llh = 0;
				else llh = left->left->height;

				if (lrh <= llh) this->right_rotation();
				else this->b_right_rotation();
			}
			else {
				if (!right->left) rlh = 0;
				else rlh = right->left->height;
				if (!right->right) rrh = 0;
				else rrh = right->right->height;

				if (rlh <= rrh) this->left_rotation();
				else this->b_left_rotation();
			}
		}
	};

public:

	AVL_node(int d) {
		data = d;
		height = 1;
		left = NULL;
		right = NULL;
	};

	AVL_node() {
		data = 0;
		height = 1;
		left = NULL;
		right = NULL;
	};

	void insert(int a); 
	void del(int a);
	int find(int a);
	int findmin();
	int findmax();
	int next();

	void show(bool fromleft = 0, bool prev = 0, linked_list* prev_state = NULL) {
	/* Vypíše do konzole strukturu AVL stromu*/
		if (prev_state == NULL) {
			for (int i = 0; i < height; i++) {
				prev_state = prev_state->pridej(-1); //ukazuje jestli na určité pozici v předchozím stavu bylo něco nebo ne
			}
		}

		if (right != NULL) {
			depth++;
			prev = fromleft;
			right->show(fromleft = 0, prev, prev_state);
			fromleft = prev;
			depth--;
		}
		linked_list* pointer1 = prev_state;
		linked_list* pointer2 = prev_state;
		linked_list* pointer3 = prev_state;

		if (right != NULL) {
			for (int i = 0; i < depth; i++) {
				if (prev_state->get_x() == 1) {
					cout << "   |";
					prev_state->set_x(1);
					prev_state = prev_state->get_next();
				}
				else {
					cout << "    ";
					prev_state->set_x(-1);
					prev_state = prev_state->get_next();
				}
			}
			cout << "   |" << endl;

		}
		for (int i = 0; i < depth - 1; i++) {
			if (pointer1->get_x() == 1) {
				cout << "   |";
				pointer1->set_x(1);
				pointer1 = pointer1->get_next();
			}
			else {
				cout << "    ";
				pointer1->set_x(-1);
				pointer1 = pointer1->get_next();
			}
		}
		if (depth != 0) {
			if (!fromleft) {
				cout << "   ,--";
				pointer1->set_x(1);
			}
			else {
				cout << "   '--";
				pointer1->set_x(-1);
			}
		}
		cout << "(" << this->data << ")" << endl;

		if (left != NULL) {
			for (int i = 0; i < depth; i++) {
				if (pointer2->get_x() == 1) {
					cout << "   |";
					pointer2 = pointer2->get_next();
				}
				else {
					cout << "    ";
					pointer2 = pointer2->get_next();
				}
			}
			cout << "   |" << endl;
		}

		if (left != NULL) {
			depth++;
			left->show(fromleft = 1, prev, pointer3);
			depth--;
		}
	};

	int is_leaf() {
		/* Ověřování jestli je AVL strom listem */
		if (left || right) return 0;
		else return 1;
	};
};

void AVL_node::insert(int a) {
	/* Přidání vrcholu s hodnotou 'a' do AVL stromu */
	if (data > a) {
		if (left) {
			left->insert(a);
			this->balance();
		}
		else left = new AVL_node(a);
	}
	else {
		if (data == a) return;
		if (right) {
			right->insert(a);	
			this->balance();
		}
		else right = new AVL_node(a);
	}
	this->check_height();
}

int AVL_node::find(int a) {
	/* Hledání vrcholu s hodnotou 'a' v AVL stromu */
	if (this == NULL) {
		cout << "Hodnota " << a << " nebyla nalezena" << endl;
		return 0;
	}
	else if (data == a) {
		cout << "Hodnota " << a << " byla nalezena" << endl;
		return 1;
	}
	else if (data > a) left->find(a);
	else right->find(a);
}

int	AVL_node::findmax() {
	/* Hledání maximální hodnoty AVL stromu */
	if (right != NULL) right->findmax();
	else return this->data;
}

int	AVL_node::findmin() {
	/* Hledání minimální hodnoty AVL stromu*/
	if (left != NULL) left->findmin();
	else return this->data;
}

void AVL_node::del(int a) {
	/* Vypouštění vrcholu AVL stromu s hodnotou 'a' */
	if (this == NULL){ 
		cout << "Hodnota " << a << " nebyla nalezena" << endl;
		return;
	}
	else {
		if (data > a) {
			if (left->data == a) {
				if (left->is_leaf()) left = NULL;
				else {
					left->del(a);
					this->balance(); 
				}
			}
			else {
				left->del(a);
				this->balance();
			}
		}
		else if (data < a) {
			if (right->data == a) {
				if (right->is_leaf()) right = NULL;
				else {
					right->del(a);
					this->balance();
				}
			}
			else {
				right->del(a);
				this->balance();
			}
		}
		else { 
			if (right) { 
				data = right->findmin();
				if (right->height == 1) right = NULL;
				else {
					right->del(data);
					this->balance();
				}
			}
			else {
				data = left->findmax();
				if (left->height == 1) left = NULL;
				else {
					left->del(data);
					this->balance();
				}
			}
		}	
	}
	this->check_height();
}

int previous;
int i = 0;
int AVL_node::next() {
	/* Iterator přes hodnoty AVL stromu. Vrátí dalsí nejmensí císlo */
	if (!i) {
		i++;
		previous = findmin();
		return previous;
	}
	else {
		if (data > previous) {
			if (left->data == previous) {
				if (!left->right) {
					previous = data;
					return previous;
				}
				else {
					previous = left->right->findmin();
					return previous;
				}
			}
			else left->next();
		}
		else if (data < previous) {
			if(right->data == previous) {
				if (!right->right) {
					cout << "Dalsi hodnoty nejsou" << endl;
					return previous;
				}
				else {
					previous = right->right->findmin();
					return previous;
				}
			}
			else right->next(); 
		}
		else {
			if (!right) {
				cout << "Dalsi hodnoty nejsou" << endl;
				return previous;
			}
			else {
				previous = right->findmin();
				return previous;
			}
		}
	}
}

int main() {
	/*
	AVL_node vrchol(1);
	vrchol.insert(-11);
	vrchol.insert(-11);
	vrchol.insert(-11);
	vrchol.insert(0);
	vrchol.insert(-12);
	vrchol.insert(-1);
	vrchol.insert(10);
	vrchol.insert(2);
	vrchol.insert(-5);
	vrchol.del(2);

	vrchol.show();*/
}
