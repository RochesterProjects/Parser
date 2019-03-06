
struct NODE;

typedef struct NODE *TREE;



extern TREE makeNode0(char* x);

extern TREE makeNode1(char* x, TREE t);

extern TREE makeNode4(char* x, TREE t1, TREE t2, TREE t3, TREE t4);

extern int matchTerminal(char c);

extern int lookahead(char c);

extern TREE D();

extern TREE N();

extern TREE NT();

extern TREE T();

extern TREE FT();

extern TREE TT();

extern TREE E();

extern TREE F();

extern int isTerminal(char* x);

extern TREE parseE();

extern void stackPusher(int i);

extern void productionDecider(char* nextCat);

extern TREE tableParse();

extern void test();

