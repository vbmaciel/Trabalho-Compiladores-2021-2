//Vítor Badlez Maciel - 00264312


#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER 

#include "hash.h"
#include "ast.h"

extern int SemanticErrors;

void check_and_set_declarations(AST *node);
void check_symbol(AST *node);
void check_undeclared();
void check_operands(AST *node);
void set_type_values(AST *node);
void set_type_params(AST *node);
int is_number(AST *son);
int get_type(int datatype0, int datatype1);
int is_int(int datatype);
int is_char(int datatype);
int is_float(int datatype);
int is_vector(int datatype);
int is_compatible(int var, int atrib);
int isDeclistBlockCMDListorReturn(int type);
AST* get_function(AST* rootNode, char* teste);
int check_function_parameters(AST* fun, AST* node);
int vector_count(AST* node);
void check_return_in_function(AST* node, int datatype);
void check_function_with_return(AST* node);
int get_semantic_errors();
void check_label(int type);
int is_compatibleAtri(int var, int atrib);

#endif

//END OF FILE