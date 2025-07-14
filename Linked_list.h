#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class linked_list {
	int x;
	linked_list* next;
public:
	linked_list() {
		x = -2;
		next = NULL;
	};

	linked_list(int b) {
		x = b;
		next = NULL;
	};

	int get_x() {
		return x;
	};

	linked_list* get_next() {
		return next;
	};

	void set_x(int a) {
		x = a;
	};

	linked_list* pridej(int x) {
		linked_list* temp = new linked_list();
		temp->x = x;
		temp->next = NULL;

		if (this == NULL) return temp;
		else {
			linked_list* temp1 = this;
			while (temp1->next != NULL) {
				temp1 = temp1->next;
			}
			temp1->next = temp;
		}
		return this;
	};
};