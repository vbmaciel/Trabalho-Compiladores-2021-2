//Vítor Badlez Maciel - 00264312

#include "semantic.h"

int SemanticErrors = 0;
int auxiliarConta = 0;
AST* root = 0;


void check_and_set_declarations(AST *node)
{
    int i;
    if(node==0)
        return;

    if(root == 0)
        root = node;    

    switch(node->type)
    {
        case AST_PARAMETROS:
        case AST_RPARAMETROS:
            set_type_params(node->son[0]);
            break;
        case AST_SYMBOL:
            set_type_values(node);
            check_symbol(node);
            break;
        case AST_ATR_CHAR:
            if(node->symbol) 
                if(node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                    ++SemanticErrors;
                }
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = DATATYPE_CHAR;
            node->datatype = DATATYPE_CHAR;
            break;
        case AST_FUNC_CHAR:
            if(node->symbol) 
                if(node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                    ++SemanticErrors;
                    if(node->symbol->type == SYMBOL_VARIABLE || node->symbol->type == SYMBOL_VECTOR)
                    {
                        fprintf(stderr, "Semantic ERROR: symbol %s couldn't be a function\n", node->symbol->text);
                        ++SemanticErrors;
                    }
                }else{
                    node->symbol->type = SYMBOL_FUNCTION;
                    node->symbol->datatype = DATATYPE_CHAR;
                    node->datatype = DATATYPE_CHAR;
                }
            break;
        case AST_ATR_VETOR_CHAR:
            if(node->symbol) 
                if(node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                    ++SemanticErrors;
                }
            node->symbol->type = SYMBOL_VECTOR;
            node->symbol->datatype = DATATYPE_CHAR;
            node->datatype = DATATYPE_CHAR;
            break;  
        case AST_ATR_INT:
            if(node->symbol) 
                if(node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                    ++SemanticErrors;
                }
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = DATATYPE_INT;
            node->datatype = DATATYPE_INT;
            break;
        case AST_FUNC_INT:
            if(node->symbol) 
                if(node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                    ++SemanticErrors;
                    if(node->symbol->type == SYMBOL_VARIABLE || node->symbol->type == SYMBOL_VECTOR)
                    {
                        fprintf(stderr, "Semantic ERROR: symbol %s couldn't be a function\n", node->symbol->text);
                        ++SemanticErrors;
                    }
                }else{    
                    node->symbol->type = SYMBOL_FUNCTION;
                    node->symbol->datatype = DATATYPE_INT;
                    node->datatype = DATATYPE_INT;
                }
            break;
        case AST_ATR_VETOR_INT:
            if(node->symbol) 
                if(node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                    ++SemanticErrors;
                }
            node->symbol->type = SYMBOL_VECTOR;
            node->symbol->datatype = DATATYPE_INT;
            node->datatype = DATATYPE_INT;
            break;
        case AST_ATR_FLOAT:
            if(node->symbol) 
                if(node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                    ++SemanticErrors;
                }
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = DATATYPE_FLOAT;
            node->datatype = DATATYPE_FLOAT;
            break;
        case AST_FUNC_FLOAT:
            if(node->symbol) 
                if(node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                    ++SemanticErrors;
                    if(node->symbol->type == SYMBOL_VARIABLE || node->symbol->type == SYMBOL_VECTOR)
                    {
                        fprintf(stderr, "Semantic ERROR: symbol %s couldn't be a function\n", node->symbol->text);
                        ++SemanticErrors;
                    }
                }else{
                    node->symbol->type = SYMBOL_FUNCTION;
                    node->symbol->datatype = DATATYPE_FLOAT;
                    node->datatype = DATATYPE_FLOAT;
                }
            break;
        case AST_ATR_VETOR_FLOAT:
            if(node->symbol) 
                if(node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                    ++SemanticErrors;
                }
            node->symbol->type = SYMBOL_VECTOR;
            node->symbol->datatype = DATATYPE_FLOAT;
            node->datatype = DATATYPE_FLOAT;
            break; 
        case AST_LABEL:
            if(node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }else{
                node->symbol->type = SYMBOL_LABEL;
            }
        break;
        case AST_GOTO:
            check_label(node->symbol->type);
        break;
        default: break;             
    }

    for (i=0; i<MAX_SONS; ++i)
        check_and_set_declarations(node->son[i]);
    
}

void check_label(int type){
    if(type != SYMBOL_LABEL){
        fprintf(stderr, "Semantic ERROR - goto needs match only with a label\n");
        ++SemanticErrors;
    }
}

void check_symbol(AST *node) {
    if (node->symbol->type){
        if (node->symbol->type == SYMBOL_FUNCTION){
            fprintf(stderr,"Semantic ERROR - Line %d function needs parentheses.\n", node->lineNumber);
            ++SemanticErrors;
        } else if (node->symbol->type == SYMBOL_VECTOR){
            fprintf(stderr,"Semantic ERROR - Line %d unindexed vector.\n", node->lineNumber);
            ++SemanticErrors;
        } else if (node->symbol->type == SYMBOL_LABEL){
            fprintf(stderr,"Semantic ERROR - Line %d label declared incorrectly.\n", node->lineNumber);
            ++SemanticErrors;
        }
    }
}


void set_type_params(AST *node)
{
    switch(node->type)
    {
        case AST_SYMBOL_INT:
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = DATATYPE_INT;
            node->datatype = DATATYPE_INT;
            break;
        case AST_SYMBOL_CHAR:
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = DATATYPE_CHAR;
            node->datatype = DATATYPE_CHAR;
            break;
        case AST_SYMBOL_FLOAT:
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = DATATYPE_FLOAT;
            node->datatype = DATATYPE_FLOAT;
            break;

        default: break;
    } 
}

void set_type_values(AST *node)
{
    switch(node->symbol->type)
    {
        case SYMBOL_FUNCTION:
        case SYMBOL_VECTOR:
        case SYMBOL_VARIABLE:
            if(node->symbol->datatype == DATATYPE_INT){
                node->datatype = DATATYPE_INT;
            }else if(node->symbol->datatype == DATATYPE_CHAR){
                node->datatype = DATATYPE_CHAR;
            }else if(node->symbol->datatype == DATATYPE_FLOAT){
                node->datatype = DATATYPE_FLOAT;
            }
            break;
        case SYMBOL_LIT_INTEGER:
            node->symbol->datatype = DATATYPE_INT;
            node->datatype = DATATYPE_INT;
            break;
        case SYMBOL_LIT_CHAR:
            node->symbol->datatype = DATATYPE_CHAR;
            node->datatype = DATATYPE_CHAR;
            break;
        case SYMBOL_LIT_FLOAT:
            node->symbol->datatype = DATATYPE_FLOAT;
            node->datatype = DATATYPE_FLOAT;
            break;
        default: break;
    } 
}


void check_undeclared()
{
    SemanticErrors += hash_check_undeclared();
}

void check_operands(AST *node)
{
    int i;
    if(node==0) return;

    for (i=0; i<MAX_SONS; ++i)
        check_operands(node->son[i]);    

    //fprintf(stderr, "TYPE: %d\n", node->type);
    switch(node->type)
    { 
        case AST_DECL:    
        break;
        case AST_RETURN:
            node->datatype = node->son[0]->datatype;
        break;
        case AST_ARRAY:
            if(node->symbol == 0){
                fprintf(stderr, "Semantic ERROR - Line %i: No symbol.\n", node->lineNumber);
                ++SemanticErrors;
            }
            if(node->symbol->type != SYMBOL_VECTOR){
                fprintf(stderr, "Semantic ERROR - Line %i: Not is a vector\n", node->lineNumber);
                ++SemanticErrors;
            }

            if(!is_int(node->son[0]->datatype) && !is_char(node->son[0]->datatype)){
                fprintf(stderr, "Semantic ERROR - Line %i: index must be an integer.\n", node->son[0]->lineNumber);
                ++SemanticErrors;
            }
            node->datatype = node->symbol->datatype;
            break;
        case AST_ADD:
        case AST_SUB:
        case AST_MUL:
        case AST_DIV:
                node->datatype = get_type(node->son[0]->datatype, node->son[1]->datatype);
                if(node->datatype == ERROR_DATATYPE){
                    fprintf(stderr, "Semantic ERROR - Line %i: operands not compatible.\n", node->lineNumber);
                    ++SemanticErrors;
                }
            break;
        case AST_LT:
        case AST_GT:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_DIF:
            node->datatype = DATATYPE_BOOL;
            break;
        case AST_PARENTESES:
            node->datatype = node->son[0]->datatype;
        break;
        case AST_ATR_CHAR:
        case AST_ATR_INT:
        case AST_ATRIBUTE:
            if(node->symbol == 0){
                    fprintf(stderr, "Semantic ERROR - Line %i: No symbol.\n", node->lineNumber);
                    ++SemanticErrors;
                    break;
                }
            //fprintf(stderr, "TEXT: %s TYPE: %d\n", node->symbol->text, node->symbol->type);
            if(node->symbol->type == SYMBOL_FUNCTION){
                    fprintf(stderr, "Semantic ERROR - Line %i: Function couldn't be a scalar\n", node->lineNumber);
                    ++SemanticErrors; 
                }
            if(node->son[1]==0){
                if(node->symbol->type != SYMBOL_VARIABLE){
                    fprintf(stderr, "Semantic ERROR - Line %i: doesn't match it's type.\n", node->lineNumber);
                    ++SemanticErrors;
                }
                //if(node->symbol->datatype, node->son[0]->datatype) READDD
                if(node->symbol->datatype && node->son[0]->datatype){
                    //fprintf(stderr, "ENTROU AQUI %d, %d", node->symbol->datatype, node->son[0]->datatype);
                    if(!is_compatibleAtri(node->symbol->datatype, node->son[0]->datatype)){
                        fprintf(stderr, "Semantic ERROR - Line %i: Has not compatible datatypes.\n", node->lineNumber);
                        ++SemanticErrors;
                    }
                }
            }else{
                if(node->symbol->type != SYMBOL_VECTOR){
                    fprintf(stderr, "Semantic ERROR - Line %i: Not is a vectorasa\n", node->lineNumber);
                    ++SemanticErrors;
                }
                if(node->symbol->datatype && node->son[0]->datatype){
                    if(!is_compatibleAtri(node->symbol->datatype, node->son[1]->datatype)){
                        fprintf(stderr, "Semantic ERROR - Line %i: Has not compatible datatypes.\n", node->lineNumber);
                        ++SemanticErrors;
                    }
                }
                if(!is_int(node->son[0]->datatype) && !is_char(node->son[0]->datatype)){
                    fprintf(stderr, "Semantic ERROR - Line %i: index must be an integer.\n", node->son[1]->lineNumber);
                    ++SemanticErrors;   
                }
            }       
            node->datatype = node->symbol->datatype;
        break;
        case AST_ATR_FLOAT:
            if(node->symbol == 0){
                    fprintf(stderr, "Semantic ERROR - Line %i: No symbol.\n", node->lineNumber);
                    ++SemanticErrors;
                }
            if(node->symbol->type != SYMBOL_VARIABLE){
                    fprintf(stderr, "Semantic ERROR - Line %i: doesn't match it's type.\n", node->lineNumber);
                    ++SemanticErrors;
                }
            if(!is_int(node->son[0]->datatype)||!is_int(node->son[1]->datatype)){
                    fprintf(stderr, "Semantic ERROR - Line %i: Has not compatible datatypes.\n", node->son[1]->lineNumber);
                    ++SemanticErrors;   
                }
            node->datatype = node->symbol->datatype;
        break;
        case AST_ATR_VETOR_CHAR:
        case AST_ATR_VETOR_INT:
        case AST_ATR_VETOR_FLOAT:
            if(node->symbol == 0){
                fprintf(stderr, "Semantic ERROR - Line %i: No symbol.\n", node->lineNumber);
                ++SemanticErrors;
            }
            if(node->symbol->type != SYMBOL_VECTOR){
                fprintf(stderr, "Semantic ERROR - Line %i: doesn't match it's type.\n", node->lineNumber);
                ++SemanticErrors;
            }
            if(node->symbol->datatype != DATATYPE_INT && node->symbol->datatype != DATATYPE_FLOAT && node->symbol->datatype != DATATYPE_CHAR){
                fprintf(stderr, "Semantic ERROR - Line %i: Has not compatible datatypes.\n", node->lineNumber);
                ++SemanticErrors;
            }
            if(node->son[0]->datatype != DATATYPE_INT){
                fprintf(stderr, "Semantic ERROR - Line %i: Has not compatible datatypes.\n", node->son[0]->lineNumber);
                ++SemanticErrors;    
            }
            if(node->son[1] != 0){
                if(!is_compatible(node->symbol->datatype, node->son[1]->datatype)){
                    fprintf(stderr, "Semantic ERROR - Line %i: the elements of a vector must be compatible.\n", node->son[1]->lineNumber);
                    ++SemanticErrors;
                }
                auxiliarConta = 0;
                int tamanho = strtol(node->son[0]->symbol->text,NULL, 10);
                //fprintf(stderr, "TAMANHO: %d\n", tamanho);
                int vetor = vector_count(node->son[1]);
                if(tamanho != auxiliarConta){
                    fprintf(stderr, "Semantic ERROR - Line %i: vector range must be compatible.\n", node->son[1]->lineNumber);
                    ++SemanticErrors;
                }
            }
            node->datatype = node->symbol->datatype;
        break;
        case AST_LARRAY:
            if(node->son[0] == 0){
                node->datatype = ERROR_DATATYPE;
            }
            else if(node->son[1] == 0){
                node->datatype = node->son[0]->datatype;
            }
            else{
                node->datatype = get_type(node->son[0]->datatype, node->son[1]->datatype);
            }
            break;
        break;
        case AST_FUNC:
            if(node->symbol == 0){
                fprintf(stderr, "Semantic ERROR - Line %i: No symbol.\n", node->lineNumber);
                ++SemanticErrors;
                break;
            }
            if(node->symbol->type != SYMBOL_FUNCTION){
                fprintf(stderr, "Semantic ERROR - Line %i: %s doesn't match it's type.\n", node->lineNumber, node->symbol->text);
                ++SemanticErrors;
            }
            //fprintf(stderr, "ROOT %s    SYMBOL: %s doesn't match it's type.\n", root->son[0]->symbol->text, node->symbol->text);
            AST* aux = get_function(root, node->symbol->text);
            if(!check_function_parameters(aux->son[0], node->son[0])){
                fprintf(stderr, "Semantic ERROR - Line %i: function parameters wrong.\n", node->lineNumber);
                ++SemanticErrors;
            }
            node->datatype = node->symbol->datatype; 
        break;
        case AST_PRINT:
            node->datatype = node->son[0]->datatype;
        break;
        default: break;
    }   
}

void check_return_in_function(AST* node, int datatype){
    int i;

    if(node == 0) return;

    if(node->type){
        //fprintf(stderr, "TYPE: %i.\n", node->type);
        if(node->type == AST_RETURN){
            //fprintf(stderr, "ENTROU TESTE RETURN: %i, %i\n", node->type, node->son[0]->datatype);
            if(!is_compatibleAtri(datatype, node->son[0]->datatype)){
                fprintf(stderr, "Semantic ERROR - Line %i: function with incompatible return.\n", node->lineNumber);
                ++SemanticErrors;
            }
        }
    }
    for (i=0; i<MAX_SONS; ++i)
        check_return_in_function(node->son[i], datatype);
}

void check_function_with_return(AST* node){
    int i;

    if(node == 0) return;

    if(node->type){
        if(node->type == AST_FUNC_CHAR || node->type == AST_FUNC_FLOAT || node->type == AST_FUNC_INT){
            //fprintf(stderr, "%s, %i\n", node->symbol->text, node->symbol->datatype);
            check_return_in_function(node, node->symbol->datatype);
        }
    }
    
    for (i=0; i<MAX_SONS; ++i)
        check_function_with_return(node->son[i]);
}

int vector_count(AST* node){
    if(node != NULL){
        auxiliarConta++;
        if(node->son[1] != NULL){
            vector_count(node->son[1]);
        }
    }
}

AST* get_function(AST* rootNode, char* text){
    if(rootNode == 0 || rootNode->son[0] == 0)
        return 0;
    if( strcmp(rootNode->son[0]->symbol->text, text) == 0 ){ 
        //fprintf(stderr, "CHEGOU AQUI 3: %s, %s\n", rootNode->son[0]->symbol->text, text);
        return rootNode->son[0];
    }
    //fprintf(stderr, "CHEGOU AQUI 3: %s, %s\n", rootNode->son[0]->symbol->text, text);
    return get_function(rootNode->son[1], text);
}

int check_function_parameters(AST* fun, AST* node){
    //fprintf(stderr, "CHEGOU AQUI CHECK PARAMS\n");
    if(fun == 0){
        if(node == 0)
            return 1;
        else
            return 0;
    }
    else if(node == 0){
        return 0;
    }
    if(!is_compatibleAtri(fun->son[0]->datatype, node->son[0]->datatype)){
        return 0;
    }
    else{
        return check_function_parameters(fun->son[1], node->son[1]);
    }
    
}

int get_type(int datatype0, int datatype1)
{
    if((!is_int(datatype0)&&!is_char(datatype0)&&!is_float(datatype0))||(!is_int(datatype1)&&!is_char(datatype1)&&!is_float(datatype1)))
    {
        return ERROR_DATATYPE;
    }
    else if(is_float(datatype0)||is_float(datatype1))
    {
        return DATATYPE_FLOAT;
    }
    return DATATYPE_INT;
}

int is_int(int datatype)
{
    switch (datatype)
    {
        case DATATYPE_INT:
            return 1;
            break;
        
        default:
            return 0;
            break;
    }
}

int is_char(int datatype)
{
    switch (datatype)
    {
        case DATATYPE_CHAR:
            return 1;
            break;
        
        default:
            return 0;
            break;
    }
}

int is_float(int datatype)
{
    switch (datatype)
    {
        case DATATYPE_FLOAT:
            return 1;
            break;
        
        default:
            return 0;
            break;
    }
}

int is_compatible(int var, int atrib){
    if(is_float(var)){
        if(is_float(atrib)||is_int(atrib)||is_char(atrib))
            return 1;
        else
            return 0;
    }
    else if (is_int(var)){
        if(is_int(atrib)||is_char(atrib))
            return 1;
        else
            return 0;
    }
    else if(is_char(var)){
        if(is_char(atrib)||is_int(atrib))
            return 1;
        else 
            return 0;
    }
    return 0;
}

int is_compatibleAtri(int var, int atrib){
    if(is_float(var)||is_int(var)||is_char(var)){
        if(is_float(atrib)||is_int(atrib)||is_char(atrib))
            return 1;
        else
            return 0;
    }
}

int get_semantic_errors(){
    return SemanticErrors;
}

//END OF FILE