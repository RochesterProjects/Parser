#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "expr.h"
#define FAILED NULL

struct StackNode 
{ 
    char* data; 
    struct StackNode* next; 
}; 
  
struct StackNode* newNode(char* data) 
{ 
    struct StackNode* stackNode = 
              (struct StackNode*) malloc(sizeof(struct StackNode)); 
    stackNode->data = data; 
    stackNode->next = NULL; 
    return stackNode; 
} 
  
int isEmpty(struct StackNode *root) 
{ 
    return !root;
} 
  
void push(struct StackNode** root, char* data) 
{ 
    struct StackNode* stackNode = newNode(data); 
    stackNode->next = *root; 
    *root = stackNode; 
} 
  
char* pop(struct StackNode** root) 
{ 
    if (isEmpty(*root)) 
        return "$"; 

    struct StackNode* temp = *root; 
    *root = (*root)->next; 
    char* popped = temp->data; 
    free(temp);
    return popped; 
} 

char* peek(struct StackNode* root){
	if(isEmpty(root)){
		return NULL;
	}else{
		return root->data;
	}

}
  

  
typedef struct NODE *TREE;	

struct NODE{
	char* label;
	TREE leftmostChild, rightSibling;
};


TREE recParseTree; /* holds the result of the recursive parse */
TREE tabParseTree; /* holds the resuolt of the table-driven parse */
char *nextInputChar; /* current position in input string */
struct StackNode* stack = NULL; /** stack for table parsing*/

/** returns a tree with no children */
TREE makeNode0(char* x){
	TREE root;
	root = (TREE) malloc(sizeof(struct NODE));
	root->label = x;
	root->leftmostChild = NULL;
	root->rightSibling = NULL;
	return root;
}

/** returns a tree with one child */
TREE makeNode1(char* x, TREE t){
	TREE root;
	root = makeNode0(x);
	root->leftmostChild = t;
	return root;
}

/** returns a tree with two children */
TREE makeNode2(char* x, TREE t1, TREE t2){
	TREE root;
	t1-> rightSibling = t2;
	root = makeNode1(x, t1);
	return root;
}

/** returns a tree with 3 children */
TREE makeNode3(char* x, TREE t1, TREE t2, TREE t3){
	TREE root;
	root = makeNode1(x, t1);
	t1-> rightSibling = t2;
	t2->rightSibling = t3;
	return root;
}

/** make root have two children */
TREE combine2Children(TREE root, TREE child1, TREE child2){
	root->leftmostChild = child1;
	child1->rightSibling = child2;
	return root;
}

/** make root have 3 children */
TREE combine3Children(TREE root, TREE child1, TREE child2, TREE child3){
	root->leftmostChild = child1;
	root->leftmostChild->rightSibling = child2;
	root->leftmostChild->rightSibling->rightSibling = child3;
	return root;
}
/** returns a tree with  4 children */
TREE makeNode4(char* x, TREE t1, TREE t2, TREE t3, TREE t4){
	TREE root;
	root = makeNode1(x, t1);
	t1-> rightSibling = t2;
	t2-> rightSibling = t3;
	t3-> rightSibling = t4;
	return root;
}

/** returns the leaf in which you should add more nodes to- the leftmost leaf */
TREE getLeaf(TREE root){
	
	if(root->leftmostChild != NULL){
		TREE t1 = getLeaf(root->leftmostChild); //check child
		if(t1 != NULL){
		 return t1;}
	}else if(!(strcmp(root->label, "e") == 0) && !isTerminal(root->label)) return root; //check if root is not empty or a terminal
	if(root->rightSibling != NULL){//check siblings
		TREE t2 = getLeaf(root->rightSibling);
		if(t2 != NULL) return t2;
	}

	return NULL;
}

/** prints TREE as specified by specs, with correct indent */

void treePrinter(TREE root, int indent){
	if(root == NULL){
		return;
	}else{
		for(int i = 1; i<=indent; i++){
			printf("\t");
		}
		printf("%s\n", root->label);
	}
	treePrinter(root->leftmostChild, indent+1);
	treePrinter(root->rightSibling, indent);
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

/** Returns a tree if matches <D> syntactic category. Else return null*/
TREE D(){
	char c = *nextInputChar;
	switch(c){
		case '0':
			if(matchTerminal('0')){
				TREE t = makeNode0("0");
				return makeNode1("D", t);
			}
			break;
		case '1':
			if(matchTerminal('1')){
				TREE t = makeNode0("1");
				return makeNode1("D", t);
			}
			break;
		case '2':
			if(matchTerminal('2')){
				TREE t = makeNode0("2");
				return makeNode1("D", t);
			}
			break;
		case '3':
			if(matchTerminal('3')){
				TREE t = makeNode0("3");
				return makeNode1("D", t);
			}
			break;
		case '4':
			if(matchTerminal('4')){
				TREE t = makeNode0("4");
				return makeNode1("D", t);
			}
			break;
		case '5':
			if(matchTerminal('5')){
				TREE t = makeNode0("5");
				return makeNode1("D", t);
			}
			break;
		case '6':
			if(matchTerminal('6')){
				TREE t = makeNode0("6");
				return makeNode1("D", t);
			}
			break;
		case '7':
			if(matchTerminal('7')){
				TREE t = makeNode0("7");
				return makeNode1("D", t);
			}
			break;
		case '8':
			if(matchTerminal('8')){
				TREE t = makeNode0("8");
				return makeNode1("D", t);
			}
			break;
		case '9':
			if(matchTerminal('9')){
				TREE t = makeNode0("9");
				return makeNode1("D", t);
			}
			break;
		default:
			return FAILED;
			break;

	}
	return FAILED;
}

/** Returns a tree if matches <NT> syntactic category. Else return null*/
TREE NT(){
	if(!(lookahead('0') || lookahead('1') || lookahead('2') || lookahead('3') || lookahead('4') || lookahead('5') || lookahead('6') || lookahead('7') || lookahead('8') || lookahead('9'))){
		TREE t = makeNode0("e");
		return makeNode1("NT", t);
	}else{
		 TREE y = N();
		 if(y == NULL) return FAILED;
		 else return makeNode1("NT", y);
		}
	return 0;
}
	


		


/** Returns tree if matches <N> Syntactic category. Else return null*/
TREE N(){
	TREE y1 = D();
	if(y1 == NULL) return FAILED;
	TREE y2 = NT(); 
	if(y2 == NULL) return FAILED;
	return makeNode2("N",y1,y2);
}

/** Returns a tree if matches <F> syntactic category. Else return null*/
TREE F(){
	if(lookahead('(')){
		if(!matchTerminal('(')) return NULL;
		TREE y1 = E();
		if(y1 == NULL) return NULL;
		if(!matchTerminal(')')) return NULL;
		return makeNode3("F", makeNode0("("), y1, makeNode0(")"));
	} else{
		 TREE y2 = N();
		 if(y2 != NULL) return makeNode1("F",y2);}
   return NULL;
}

/** Returns a tree if matches <FT> syntactic category. Else return null*/
TREE FT(){
	if(!(lookahead('*') || lookahead('/'))){
		return makeNode1("FT", makeNode0("e"));
	} else{
		char* operator;
		if(lookahead('*')) operator = "*";
		if(lookahead('/')) operator = "/";
		if(!(matchTerminal('*') || matchTerminal('/'))) return NULL;
		TREE y1 = F();
		if(y1 == NULL) return NULL;
		TREE y2 = FT();
		if(y2 == NULL) return NULL;
		return makeNode3("FT",makeNode0(operator),y1,y2); // fix times or divide
	}
}

/** Returns a tree if matches <T> syntactic category. Else return null*/
TREE T(){
	TREE y1 = F();
	if(y1 == NULL) return NULL;
	TREE y2 = FT();
	if(y2== NULL) return NULL;
	return makeNode2("T", y1,y2);
}

/** Returns a tree if matches <TT> syntactic category. Else return null*/
TREE TT(){
	if(!(lookahead('+') || lookahead('-'))){
		return makeNode1("TT", makeNode0("e"));
	} else{
		char* operator;
		if(lookahead('+')) operator = "+";
		if(lookahead('-')) operator = "-";
		if(!(matchTerminal('+') || matchTerminal('-'))) return NULL;
		TREE y1 = T();
		if(y1 == NULL) return NULL;
		TREE y2 = TT();
		if(y2 == NULL) return NULL;
		return makeNode3("TT",makeNode0(operator),y1,y2); // fix times or divide
		free(y1);
		free(y2);
	}
}

/** Returns a tree if matches <E> syntactic category. Else return null*/
TREE E(){
	TREE y1 = T();
	if(y1 == NULL) return NULL;
	TREE y2 = TT();
	if(y2== NULL) return NULL;
	return makeNode2("E", y1, y2);
}


/** driver to run a recrusiveParse */
TREE recursiveParse(){
	return E();
}

/** returns 1 if char is a digit*/
int isDigit(char x){
	return (x=='0'|| x=='1'|| x=='2'|| x=='3'||x=='4'|| x=='5'|| x=='6'|| x=='7'|| x=='8'|| x=='9');
}

int isOperator(char* x){
	 if((strcmp(x, "+") == 0) || (strcmp(x, "-") == 0) || (strcmp(x, "*") == 0) || (strcmp(x, "/") == 0)) return 1;
	 else return 0;
}
/** PART THREE: CALCULATIONS. done with recursive tree */

/** handles subcalculations of a arithmetic tree recursively. */
int subcal(TREE tree){ 
	int result = 0;
	char val[255]; //to store string of number
	if(strcmp(tree->label, "N") == 0){return subcal(tree->leftmostChild);}
	else if(strcmp(tree->label, "NT") == 0){return subcal(tree->leftmostChild);} //check child
	else if(strcmp(tree->label, "FT") == 0){return subcal(tree->leftmostChild->rightSibling);} 
	else if(strcmp(tree->label, "TT") == 0){return subcal(tree->leftmostChild->rightSibling);}
	else if(strcmp(tree->label, "E") == 0){return subcal(tree->leftmostChild);}
	/** return terminal values accordingly */
	else if(strcmp(tree->label, "e") == 0){return 0;}
	else if(strcmp(tree->label, "0") == 0){return 0;}
	else if(strcmp(tree->label, "1") == 0){return 1;}
	else if(strcmp(tree->label, "2") == 0){return 2;}
	else if(strcmp(tree->label, "3") == 0){return 3;}
	else if(strcmp(tree->label, "4") == 0){return 4;}
	else if(strcmp(tree->label, "5") == 0){return 5;}
	else if(strcmp(tree->label, "6") == 0){return 6;}
	else if(strcmp(tree->label, "7") == 0){return 7;}
	else if(strcmp(tree->label, "8") == 0){return 8;}
	else if(strcmp(tree->label, "9") == 0){return 9;}
	else if(strcmp(tree->label, "T") == 0){//check if correct grandchild is an operator + or -
			if(strcmp(tree->rightSibling->leftmostChild->label, "e") == 0){
				 return subcal(tree->leftmostChild);} //empty addition subtraction
			if(strcmp(tree->rightSibling->leftmostChild->label, "+") == 0){
				 return (subcal(tree->leftmostChild) + subcal(tree->rightSibling->leftmostChild->rightSibling));}
			if(strcmp(tree->rightSibling->leftmostChild->label, "-") == 0){
				 return (subcal(tree->leftmostChild) - subcal(tree->rightSibling->leftmostChild->rightSibling));}
	}
	else if(strcmp(tree->label, "F") == 0){//check if correct grandchild is an operator */ or a ( terminal
			if(strcmp(tree->leftmostChild->label, "(") == 0){
				if(strcmp(tree->rightSibling->leftmostChild->label, "e") == 0) return subcal(tree->leftmostChild->rightSibling);
				if(strcmp(tree->rightSibling->leftmostChild->label, "*") == 0)
					return (subcal(tree->leftmostChild->rightSibling) * subcal(tree->rightSibling->leftmostChild->rightSibling));
				if(strcmp(tree->rightSibling->leftmostChild->label, "/") == 0)
					return (subcal(tree->leftmostChild->rightSibling) / subcal(tree->rightSibling->leftmostChild->rightSibling));
			}
			if(strcmp(tree->rightSibling->leftmostChild->label, "e") == 0){
				 return subcal(tree->leftmostChild);} //empty addition subtraction
			if(strcmp(tree->rightSibling->leftmostChild->label, "*") == 0){
				 return (subcal(tree->leftmostChild) * subcal(tree->rightSibling));}
			if(strcmp(tree->rightSibling->leftmostChild->label, "/") == 0){
				 return (subcal(tree->leftmostChild) / subcal(tree->rightSibling));}
	}
	else if(strcmp(tree->label, "D") == 0){
			if(strcmp(tree->rightSibling->leftmostChild->label, "e") == 0){return subcal(tree->leftmostChild);}
			sprintf(val, "%d%d", subcal(tree->leftmostChild), subcal(tree->rightSibling)); //concatenates digits 
			return atoi(val); //return the conctenated string as an int
	}

	return result;
			
}

/** driver to run the calculation of arithmetic expression through a recursive parse */
int calculate(TREE tree){
	return subcal(tree);
}


/** PART TWO: TABLE PARSING FUNCTIONS BELOW */

int tableGrammar[8][17] = {  /*E*/{1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0}, 
							/*TT*/{0,4,2,3,4,4,4,0,0,0,0,0,0,0,0,0,4}, 
							/*T*/{5,0,0,0,0,0,5,5,5,5,5,5,5,5,5,5,0},
							/*FT*/{8,8,8,8,6,7,8,8,8,8,8,8,8,8,8,8,8}, 
							/*F*/{10,0,0,0,0,0,9,9,9,9,9,9,9,9,9,9,0}, 
							/*N*/{0,0,0,0,0,0,11,11,11,11,11,11,11,11,11,11,0},
							/*D*/{13,13,13,13,13,13,14,15,16,17,18,19,20,21,22,23,0},
							/*NT*/{13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,12,13} 
							}; 
		//rows are syntactic categories corresponding to E,TT,T,FT,F,N,D,NT
			// columns are terminals corresponding (,), +, -, *,/, A DIGIT, NUL
			//assign a 0 for an empty space


/** now, create methods that match strings of syntactic categories with their correspoonding number, and for matching terminals with their corresponding terminal*/

int syncatMatcher(char* c){
	if(strcmp(c, "E") == 0) return 0;
	else if(strcmp(c, "TT") == 0) return 1;
	else if(strcmp(c, "T") == 0) return 2;
	else if(strcmp(c, "FT") == 0) return 3;
	else if(strcmp(c, "F") == 0) return 4;
	else if(strcmp(c, "N") == 0) return 5;
	else if(strcmp(c, "D") == 0) return 6;
	else if(strcmp(c, "NT") == 0) return 7;
	else return -1; //not a syntactic category
}

int terminalMatcher(char c){
	switch(c){
		case '(':
			return 0;
			break;
		case ')':
			return 1;
			break;
		case '+':
			return 2;		
			break;
		case '-':
			return 3;
			break;
		case '*':
			return 4;
			break;
		case '/':
			return 5;
			break;
		case '0':
		 return 6;
	     break;
		case '1':
			return 7;
			break;
		case '2': 
			return 8;
			break;
		case '3':
			return 9;
			break;
		case '4':
			return 10;
			break;
		case '5':
		 return 11;
	     break;
		case '6':
			return 12;
			break;
		case '7': 
			return 13;
			break;
		case '8':
			return 14;
			break;
		case '9':
			return 15;
			break;
		default:
			return -1;
			break;
		}
}
/** return 1 if string is a character matched by a terminal specified in the grammar */
int isTerminal(char* c){
	char x = *c;
	return (x=='0'|| x=='1'|| x=='2'|| x=='3'||x=='4'|| x=='5'|| x=='6'|| x=='7'|| x=='8'|| x=='9' || x == '(' || x == ')' || x == '+' || x == '-' || x == '*' || x == '/');
}

/**pushes correct production onto the stack, adds leaves to tree */

void stackPusher(int i){
	TREE t;
	t = getLeaf(tabParseTree);
	switch(i){
			case 1:
				push(&stack, "TT");
				push(&stack, "T");
				combine2Children(t,makeNode0("T"), makeNode0("TT"));
				break;
			case 2: 
				push(&stack, "TT");
				push(&stack, "T");
				push(&stack, "+");
				combine3Children(t,makeNode0("+"), makeNode0("T"), makeNode0("TT"));
				break;
			case 3:
				push(&stack, "TT");
				push(&stack, "T");
				push(&stack, "-");
				combine3Children(t,makeNode0("-"), makeNode0("T"), makeNode0("TT"));
				break;
			case 4:
				push(&stack, "e");
				t->leftmostChild = makeNode0("e");
				break;
			case 5: 
				push(&stack, "FT");
				push(&stack, "F");
				combine2Children(t,makeNode0("F"), makeNode0("FT"));
				break;
			case 6:
				push(&stack, "FT");
				push(&stack, "F");
				push(&stack, "*");
				combine3Children(t,makeNode0("*"), makeNode0("F"), makeNode0("FT"));
				break;
			case 7:
				push(&stack, "FT");
				push(&stack, "F");
				push(&stack, "/");
				combine3Children(t,makeNode0("/"), makeNode0("F"), makeNode0("FT"));
				break;
			case 8:
				push(&stack, "e");
				t->leftmostChild = makeNode0("e");
				break;
			case 9:
				push(&stack, "N");
				t->leftmostChild = makeNode0("N");
				break;
			case 10:
				push(&stack, ")");
				push(&stack, "E");
				push(&stack, "(");
				combine3Children(t,makeNode0("("), makeNode0("E"), makeNode0(")"));
				break;
			case 11:
				push(&stack, "NT");
				push(&stack, "D");
				combine2Children(t,makeNode0("D"), makeNode0("NT"));
				break;
			case 12:
				push(&stack, "N");
				t->leftmostChild = makeNode0("N");
				break;
			case 13:
				push(&stack, "e");
				t->leftmostChild = makeNode0("e");
				break;
			case 14:
				push(&stack, "0");
				t->leftmostChild = makeNode0("0");
				break;
			case 15:
				push(&stack, "1");
				t->leftmostChild = makeNode0("1");
				break;
			case 16:
				push(&stack, "2");
				t->leftmostChild = makeNode0("2");
				break;
			case 17:
				push(&stack, "3");
				t->leftmostChild = makeNode0("3");
				break;
			case 18:
				push(&stack, "4");
				t->leftmostChild = makeNode0("4");
				break;
			case 19:
				push(&stack, "5");
				t->leftmostChild = makeNode0("5");
				break;
			case 20:
				push(&stack, "6");
				t->leftmostChild = makeNode0("6");
				break;
			case 21:
				push(&stack, "7");
				t->leftmostChild = makeNode0("7");
				break;
			case 22:
				push(&stack, "8");
				t->leftmostChild = makeNode0("8");
				break;
			case 23:
				push(&stack, "9");
				t->leftmostChild = makeNode0("9");
				break;
			default:
				break;
			}

			
}

/** decides which production to push onto the stack */
void productionDecider(char* nextCat){
	int production;
	 production = tableGrammar[syncatMatcher(nextCat)][terminalMatcher(*nextInputChar)];
	stackPusher(production);
}
	
/** run a table-driven parse on the given grammar */
TREE tableParse(){
	tabParseTree = makeNode0("E");
	push(&stack, "E"); //push start symbol
	while(!(isEmpty(stack))){
		char* y = pop(&stack);
		if(isTerminal(y) == 1){//match and consume, else fail
			char c = *y;
			matchTerminal(c);
		}
		else{
			productionDecider(y); //decide production to push onto stack
		}
	}
	return tabParseTree;
}

	
		
			
		
	
/** runner function */
void test(){
	char* input = (char*)malloc(3);
	fgets(input,255,stdin);
	printf("input = %s\n", input);
	nextInputChar = input;
	recParseTree = recursiveParse();
	if(recParseTree != NULL && lookahead('\n')){
		printf("Valid input! This is the parsing tree: \n");
		treePrinter(recParseTree,0);
		printf("\n");

		printf("Now will complete  table-driven parsing...\n");
		nextInputChar = input;
		tableParse();
		if(tabParseTree != NULL && lookahead('\n')){
		printf("printing result of table parse...\n");
		treePrinter(tabParseTree,0);
		printf("\n");
		}

		printf("Calculating expression...\nThe value of this expression is...%d\n ", calculate(recParseTree));
	
	}else{printf("Invalid expression. No tree could be generated.");}
	
	
	free(input);
	free(recParseTree);
	free(tabParseTree);
	free(stack);
}

int main(){
	test();
	

}
