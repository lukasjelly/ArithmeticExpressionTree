//Lukas Jehle #20009320

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <fstream>
#include <stack>

using namespace std;

/* implement the Tree class here, you can copy the one from week 4 slides */
/* the contents of the Tree nodes can be of type char, so they can store operators (+, *, / and -) as well as digits (0,1,2...9) */
/* all the RPN*.txt test files contain numbers with single digits */
class Tree {
private:
	char data;
	Tree* leftPtr;
	Tree* rightPtr;
public:
	Tree(char newdata, Tree* L, Tree* R);
	~Tree() {}
	char RootData() { return data; }
	Tree* Left() { return leftPtr; }
	Tree* Right() { return rightPtr; }
};

Tree::Tree(char newdata, Tree* L, Tree* R) {
	data = newdata;
	leftPtr = L;
	rightPtr = R;
}

/* implement your stack here*/
/* remember that the content of the stack is of type Tree */
//Stack S; //Declare your stack of Tree* here
stack<Tree*> S;
Tree* T1, * T2, * T;

/* implement your recursive funtions for traversals */
void PreOrder(Tree* T) {
	if (T == NULL) { return; }
	printf("%c ", T->RootData());
	PreOrder(T->Left());
	PreOrder(T->Right());
}

void InOrder(Tree* T) {
	if (T != NULL) {
		if (T->Left() == NULL && T->Right() == NULL) {
			printf("%c", T->RootData());
		}
		else {
			printf("(");
			InOrder(T->Left());
			printf("%c", T->RootData());
			InOrder(T->Right());
			printf(")");
		}
	}
}

void PostOrder(Tree* T) {
	if (T == NULL) { return; }
	PostOrder(T->Left());
	PostOrder(T->Right());
	printf("%c ", T->RootData());
}

int main(int argc, char** argv) {//get filename from arguments
	char digit;
	char oper;
	char expression[100];
	ifstream input_file;
	if (argc == 2) input_file.open(argv[1]);
	else { printf("The program needs a filename as argument \n"); exit(0); }
	/* both operator and digits are of type char */
	while (input_file >> expression) {
		if (isdigit(expression[0])) {
			sscanf(expression, "%c", &digit);
			//printf("reading a number: %c \n", digit);
			//modify here to deal with the Stack
			S.push(new Tree(digit, NULL, NULL));
		}
		else {
			sscanf(expression, "%c", &oper);
			//printf("reading an operator: %c \n", oper);
			//modify here to deal with the Stack
			T1 = S.top();
			S.pop();
			T2 = S.top();
			S.pop();
			S.push(new Tree(oper, T2, T1));
		}
	}
	T = S.top();
	//Now we can traverse the tree in a certain way and print the expression
	//in-order with parenthesis
	printf("In-fix:\n");
	InOrder(T);
	//post-order
	printf("\nPost-fix:\n");
	PostOrder(T);

}

