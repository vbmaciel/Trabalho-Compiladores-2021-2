//Implementada pelo professor Marcelo Johann

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HASH_SIZE 997

#define SYMBOL_IDENTIFIER       1
#define SYMBOL_LIT_INTEGER      2
#define SYMBOL_LIT_STRING       3
#define SYMBOL_TRUE 			4
#define SYMBOL_FALSE 			5
#define SYMBOL_VARIABLE 		6
#define SYMBOL_FUNCTION 		7
#define SYMBOL_VECTOR 			8
#define SYMBOL_LIT_CHAR         9
#define SYMBOL_LIT_FLOAT        10
#define SYMBOL_LABEL            11


#define DATATYPE_CHAR           1
#define DATATYPE_INT            2
#define DATATYPE_FLOAT          3
#define DATATYPE_STRING			4
#define ERROR_DATATYPE          5
#define DATATYPE_BOOL			6


typedef struct hash_node
{
	int type;
	int datatype;
	char *text;
	struct hash_node * next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
int hash_check_undeclared(void);

#endif

