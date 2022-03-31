//Vítor Badlez Maciel - 00264312

#ifndef AST_HEADER
#define AST_HEADER

#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

#define MAX_SONS 4

#define AST_SYMBOL          1
#define AST_ADD             2
#define AST_SUB             3
#define AST_MUL             4
#define AST_DIV             5
#define AST_LE              6
#define AST_GE              7
#define AST_EQ              8
#define AST_DIF             9
#define AST_GT              10           
#define AST_LT              11
#define AST_READ            12
#define AST_ARRAY           13
#define AST_FUNC            14
#define AST_REXPR           15
#define AST_LEXPR           16
#define AST_PARENTESES      17
#define AST_LCMD            18
#define AST_LABEL           19
#define AST_BODY1           20
#define AST_CMD             21
#define AST_ATRIBUTE        22
#define AST_PRINT           23
#define AST_RPRINT          24
#define AST_LPRINT          25
#define AST_RETURN          26
#define AST_GOTO            27
#define AST_WHILE           28
#define AST_IFTHEN          29
#define AST_IFTHENELSE      30
#define AST_BODY2           31
#define AST_PARAMETROS      32
#define AST_RPARAMETROS     33
#define AST_FUNC_INT        34
#define AST_FUNC_CHAR       35
#define AST_FUNC_FLOAT      36
#define AST_DECL            37
#define AST_ATR_CHAR        38
#define AST_ATR_INT         39
#define AST_ATR_FLOAT       40
#define AST_LARRAY          41
#define AST_ATR_VETOR_CHAR  42
#define AST_ATR_VETOR_INT   43
#define AST_ATR_VETOR_FLOAT 44
#define AST_SYMBOL_INT      45
#define AST_SYMBOL_FLOAT    46
#define AST_SYMBOL_CHAR     47
#define AST_REXPRP          48

typedef struct astnode{
    int type;
    int datatype;
    HASH_NODE *symbol;
    struct astnode *son[MAX_SONS];
    int lineNumber;
} AST;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST *node, int level);
void astPrintFile(AST *node, int);
void writeOutputFile(AST *node, char *filename);
int getLineNumber();


#endif

//END OF FILE