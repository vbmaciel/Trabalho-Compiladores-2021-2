#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL         1
#define TAC_ADD            2
#define TAC_SUB            3
#define TAC_MOVE           4             
#define TAC_MUL            5
#define TAC_DIV            6
#define TAC_GE             7
#define TAC_LE             8
#define TAC_EQ             9
#define TAC_DIF            10
#define TAC_GT             11
#define TAC_LT             12
#define TAC_JFALSE         13
#define TAC_LABEL          14
#define TAC_JUMP           15
#define TAC_READ           16
#define TAC_GOTO           17
#define TAC_DECL           18
#define TAC_MOVE_VETOR     19
#define TAC_LARRAY         20
#define TAC_PRINT          21
#define TAC_ARRAY_MOVE     22
#define TAC_PARENTESES     23
#define TAC_DEC_FUNC       24
#define TAC_PARAMETROS     25
#define TAC_FUNC_BEGUN     26
#define TAC_FUNC_END       27
#define TAC_CALL_FUNC      28
#define TAC_RETURN         29
#define TAC_ARGUMENTS_FUNC 30
 
typedef struct tc_node
{
    int type;
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;
    struct tc_node* prev;
    struct tc_node* next;
}TAC;

TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);
void tacPrint(TAC* tac);
void tacPrintBackwards(TAC *tac);
TAC* tacJoin(TAC* l1, TAC *l2);
void makeBinOperation(int i);
TAC* makeIfThen(TAC* code0, TAC* code1);
TAC *makeIfThenElse(TAC *code0, TAC *code1, TAC *code2);
TAC* makeWhile(TAC *code0, TAC* code1);
TAC* makeRead();
TAC* makePrint(AST* node);
TAC* makeFunc(AST *node, TAC* code0, TAC* code1);
TAC* makeFuncWithoutParam(AST *node, TAC* code1);
TAC* makeCallFunc(AST *node, TAC* code0);
TAC* makeOperation(int type, AST *node, TAC* code0, TAC* code1);
TAC* generateCode(AST *node);


#endif