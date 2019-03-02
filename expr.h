
struct NODE;

typedef struct NODE *TREE;



extern TREE makeNode0(char x);

extern TREE makeNode1(char x, TREE t);

extern TREE makeNode4(char x, TREE t1, TREE t2, TREE t3, TREE t4);

extern int matchTerminal(char c);

extern int lookahead(char c);

extern int D();

extern int N();

extern int NT();

extern int T();

extern int FT();

extern int TT();

extern int E();

extern int F();


extern int parseE();

extern void test();

