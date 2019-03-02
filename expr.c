#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "expr.h"
#define FAILED NULL

typedef struct NODE *TREE;	

struct NODE{
	char label;
	TREE leftmostChild, rightSibling;
};

TREE parseTree; /* holds the result of the parse */
char *nextInputChar; /* current position in input string */

/** returns a tree with no children */
TREE makeNode0(char x){
	TREE root;
	root = (TREE) malloc(sizeof(struct NODE));
	root->label = x;
	root->leftmostChild = NULL;
	root->rightSibling = NULL;
	return root;
}

/** returns a tree with one child */
TREE makeNode1(char x, TREE t){
	TREE root;
	root = makeNode0(x);
	root->leftmostChild = t;
	return root;
}

/** returns a tree with  4 children */
TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4){
	TREE root;
	root = makeNode1(x, t1);
	t1-> rightSibling = t2;
	t2-> rightSibling = t3;
	t3-> rightSibling = t4;
	return root;
}

/** Attempts to match the given char against the current input symbol. 
* If succeeds, return 1 and consume input symbol. Else, return 0. */
int matchTerminal(char c){
	if(*nextInputChar == c){
		nextInputChar++;
		return 1;
	}else{
		return 0;
	}
}

/** Returns 1 if the next input character matches the given character, else 0.
* Does not consume any input. */
int lookahead(char c){
	return *nextInputChar == c;
}

/** Returns 1 if matches <D> syntactic category. Else return 0*/
int D(){
	char c = *nextInputChar;
	switch(c){
		case '0':
			return matchTerminal('0');
			break;
		case '1':
			return matchTerminal('1');
			break;
		case '2':
			return matchTerminal('2');
			break;
		case '3':
			matchTerminal('3');
			break;
		case '4':
			return matchTerminal('4');
			break;
		case '5':
			return matchTerminal('5');
			break;
		case '6':
			return matchTerminal('6');
			break;
			return matchTerminal('7');
			break;
		case '8':
			return matchTerminal('8');
			break;
		case '9':

			return matchTerminal('9');
			break;
		default:
			printf("got to deafult");
			return 0;
			break;

	}
}

int NT(){
	if(!(lookahead('0') || lookahead('1') || lookahead('2') || lookahead('3') || lookahead('4') || lookahead('5') || lookahead('6') || lookahead('7') || lookahead('8') || lookahead('9'))){
		return 1;
	}else if(N()){return 1;}
	return 0;
}
	


		


/** Returns 1 if matches <N> Syntactic category. Else return 0*/
int N(){
	if(!D()) return 0;
	if(!NT()) return 0;
	return 1;
}

int F(){
	if(lookahead('(')){
		if(!matchTerminal('(')) return 0;
		if(!E()) return 0;
		if(!matchTerminal(')')) return 0;
		return 1;
	} else if(N()){ return 1;}
	else return 0;
}

int FT(){
	if(!(lookahead('*') || lookahead('/'))){
		return 1;
	} else{
		if(!(matchTerminal('*') || matchTerminal('/'))) return 0;
		if(!F()) return 0;
		if(!FT()) return 0;
		return 1;
	}
}

int T(){
	if(!F()) return 0;
	if(!FT()) return 0;
	return 1;
}

int TT(){
	if(!(lookahead('+') || lookahead('-'))){
		return 1;
	} else{
		if(!(matchTerminal('+') || matchTerminal('-'))) return 0;
		if(!T()) return 0;
		if(!TT()) return 0;
		return 1;
	}
	return 0;
}

int E(){
	if(!T()) return 0;
	if(!TT()) return 0;
	return 1;
}









int parseE(){
	if(!E()) return 0;
	return lookahead('\0');
}

void test(){
	//char* input[256];
	//fgets(input,255, stdin);
	char* input = "(7+6)";
	printf("input = %s\n", input);
	nextInputChar = input;
	printf("result = %d\n", parseE());
}

int main(){
	test();
	//nextInputChar = "4";

}
