#include "tacs.h"
#include "ast.h"

//IMPLEMENTATION
TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2)
{
    TAC* newtac = 0;
    newtac = (TAC*) calloc(1, sizeof(TAC));
    newtac->type = type;
    newtac->res = res;
    newtac->op1 = op1;
    newtac->op2 = op2;
    newtac->prev = 0;
    newtac->next = 0;
    return newtac;
}


void tacPrint(TAC* tac)
{                
    if(!tac) return;
    if(tac->type == TAC_SYMBOL) return;
    
    fprintf(stderr, "TAC(");
    switch(tac->type)
    {
        case TAC_SYMBOL: fprintf(stderr,"TAC_SYMBOL");
            break;
        case TAC_ADD: fprintf(stderr,"TAC_ADD");
            break;
        case TAC_SUB: fprintf(stderr,"TAC_SUB");
            break;
        case TAC_MOVE: fprintf(stderr,"TAC_MOVE");
            break;
        case TAC_MUL: fprintf(stderr,"TAC_MUL");
            break;
        case TAC_DIV: fprintf(stderr,"TAC_DIV");
            break;
        case TAC_GE: fprintf(stderr,"TAC_GE");
            break;
        case TAC_LE: fprintf(stderr,"TAC_LE");
            break;
        case TAC_EQ: fprintf(stderr,"TAC_EQ");
            break;
        case TAC_DIF: fprintf(stderr,"TAC_DIF");
            break;
        case TAC_GT: fprintf(stderr,"TAC_GT");
            break;
        case TAC_LT: fprintf(stderr,"TAC_LT");
            break;
        case TAC_JFALSE: fprintf(stderr,"TAC_JFALSE");
            break;
        case TAC_JUMP: fprintf(stderr,"TAC_JUMP");
            break;
        case TAC_LABEL: fprintf(stderr,"TAC_LABEL");
            break;   
        case TAC_READ: fprintf(stderr,"TAC_READ");
            break; 
        case TAC_DECL: fprintf(stderr,"TAC_DECL");
            break;    
        case TAC_MOVE_VETOR: fprintf(stderr,"TAC_MOVE_VETOR");
            break;
        case TAC_LARRAY: fprintf(stderr,"TAC_LARRAY");
            break;
        case TAC_PRINT: fprintf(stderr,"TAC_PRINT");
            break;   
        case TAC_ARRAY_MOVE: fprintf(stderr,"TAC_ARRAY_MOVE");
            break;  
        case TAC_PARENTESES: fprintf(stderr,"TAC_PARENTESES");
            break;
        case TAC_FUNC_BEGUN: fprintf(stderr,"TAC_FUNC_BEGUN");
            break;
        case TAC_FUNC_END: fprintf(stderr,"TAC_FUNC_END");
            break;
        case TAC_CALL_FUNC: fprintf(stderr,"TAC_CALL_FUNC");
            break;
        case TAC_PARAMETROS: fprintf(stderr, "TAC_PARAMETROS");
            break;
        case TAC_RETURN: fprintf(stderr, "TAC_RETURN");
            break;
        case TAC_ARGUMENTS_FUNC: fprintf(stderr, "TAC_ARGUMENTS_FUNC");
            break;
        default: fprintf(stderr,"TAC_UNKNOWN");
    }
    fprintf(stderr, ",%s", (tac->res)?tac->res->text:"0");
    fprintf(stderr, ",%s", (tac->op1)?tac->op1->text:"0");
    fprintf(stderr, ",%s", (tac->op2)?tac->op2->text:"0");

    fprintf(stderr, ");\n");
}
void tacPrintBackwards(TAC *tac)
{
    if(!tac) return;
    else {
        tacPrintBackwards(tac->prev);
        tacPrint(tac);
    }
}

//CODE GENERATION

TAC* tacJoin(TAC* l1, TAC *l2)
{
    TAC* point;
    if(!l1) return l2;
    if(!l2) return l1;

    for(point = l2; point->prev != 0; point = point->prev)
        ;
        point->prev = l1;
        return l2;
}

TAC* generateCode(AST *node)
{
    int i;
    TAC *result = 0;
    TAC *code[MAX_SONS];

    if(!node) return 0;

    //PROCESS CHILDREN
    for (i=0; i<MAX_SONS; ++i)
        code[i] = generateCode(node->son[i]);

    //PROCESS THIS NODE
    switch (node->type)
    {
    case AST_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
        break;
    case AST_FUNC_CHAR:
    case AST_FUNC_INT:
    case AST_FUNC_FLOAT: 
        if(code[0])
            result = makeFunc(node, code[0]?code[0]:0, code[1]?code[1]:0);
        else{
            result = makeFuncWithoutParam(node, code[1]?code[1]:0);
        }
        break;
    case AST_PARAMETROS:
    case AST_RPARAMETROS: 
        if(node->son[0])
            result = tacJoin(tacCreate(TAC_PARAMETROS, node->son[0]->symbol, 0, 0), code[1]);
        break;
    case AST_FUNC:
            result = makeCallFunc(node, code[0]?code[0]:0);
        break;
    case AST_LEXPR:
    case AST_REXPR:
        result = tacJoin(tacCreate(TAC_ARGUMENTS_FUNC, node->son[0]->symbol, 0, 0), code[1]);
        break;
    case AST_ADD: 
        result = makeOperation(TAC_ADD, node, code[0], code[1]);
        break;
    case AST_SUB: 
        result = makeOperation(TAC_SUB, node, code[0], code[1]);
        break;
    case AST_MUL: 
        result = makeOperation(TAC_MUL, node, code[0], code[1]);
        break;
    case AST_DIV: 
        result = makeOperation(TAC_DIV, node, code[0], code[1]);
        break;
    case AST_GE: 
        result = makeOperation(TAC_GE, node, code[0], code[1]);
        break;
    case AST_LE: 
        result = makeOperation(TAC_LE, node, code[0], code[1]);
        break;
    case AST_GT: 
        result = makeOperation(TAC_GT, node, code[0], code[1]);
        break;
    case AST_LT: 
        result = makeOperation(TAC_LT, node, code[0], code[1]);
        break;
    case AST_EQ: 
        result = makeOperation(TAC_EQ, node, code[0], code[1]);
        break;
    case AST_DIF: 
        result = makeOperation(TAC_DIF, node, code[0], code[1]);
        break; 
    case AST_PARENTESES:
                        result = tacJoin(code[0], 
                        tacCreate(TAC_PARENTESES, code[0]?code[0]->res:0, 0, 0));
        break;        
    case AST_ARRAY: result = tacJoin(tacJoin(code[0], code[1]), 
                           tacCreate(TAC_ARRAY_MOVE, makeTemp(), node->symbol, code[0]?code[0]->res:0));
        break;                                   
    case AST_ATR_CHAR:
    case AST_ATR_INT:
                    result = tacJoin(code[0], 
                    tacCreate(TAC_MOVE, node->symbol, code[0]?code[0]->res:0, 0));
        break;
    case AST_ATRIBUTE:
                    if(node->son[1] != 0){
                        result = tacJoin(tacJoin(code[0], code[1]), 
                           tacCreate(TAC_MOVE_VETOR, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0));
                    }else if(node->son[0]->type == AST_FUNC){
                        result = tacJoin(code[0], 
                        tacCreate(TAC_MOVE, node->symbol, node->son[0]->symbol, 0));
                    }else{
                        result = tacJoin(code[0], 
                        tacCreate(TAC_MOVE, node->symbol, code[0]?code[0]->res:0, 0));
                    }
        break; 
    case AST_ATR_FLOAT:
                    result = tacJoin(code[0], 
                    tacCreate(TAC_MOVE, node->symbol, code[0]?code[0]->res:0, code[1]?code[1]->res:0));
        break;
    case AST_ATR_VETOR_CHAR:
    case AST_ATR_VETOR_INT:
    case AST_ATR_VETOR_FLOAT:
        if(!code[1])
            result = tacJoin(code[0], tacCreate(TAC_MOVE_VETOR, node->symbol, code[0]?code[0]->res:0, 0));
        else{
            result = tacJoin(code[0], tacJoin(tacCreate(TAC_MOVE_VETOR, node->symbol, code[0]?code[0]->res:0, 0), code[1]));
        } 
        break;
    case AST_LPRINT:
    case AST_RPRINT:
        if(node->son[0]->type == AST_SYMBOL)
            result = tacJoin(tacCreate(TAC_PRINT, node->son[0]->symbol, 0, 0), code[1]);
        else{
            result = tacJoin(code[0], tacJoin(tacCreate(TAC_PRINT, code[0]->res, 0, 0), code[1]));
        }
        break;
    case AST_RETURN:
            result = tacJoin(code[0], tacCreate(TAC_RETURN, code[0]->res, 0, 0));
        break;    
    case AST_LARRAY:
            result = tacJoin(tacCreate(TAC_LARRAY, code[0]?code[0]->res:0, 0, 0), code[1]);
        break; 
    case AST_IFTHEN: result =  makeIfThen(code[0], code[1]);
        break;
    case AST_IFTHENELSE: result =  makeIfThenElse(code[0], code[1], code[2]);
        break;
    case AST_WHILE: result =  makeWhile(code[0], code[1]);
        break;
    case AST_READ: 
        result = makeRead();
        break; 
    case AST_LABEL: result = tacJoin(tacCreate(TAC_LABEL, node->symbol, 0, 0), code[0]);
        break;
    case AST_GOTO: result = tacCreate(TAC_JUMP, node->symbol, 0, 0);
        break;   
    default: result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
        break;
    }
    return result;
}

TAC* makeOperation(int type, AST* node, TAC* code0, TAC* code1){
    if(node->son[0]->type == AST_FUNC){
        return tacJoin(tacJoin(code0, code1), 
        tacCreate(type, makeTemp(), node->son[0]->symbol, code1?code1->res:0));
    }else if(node->son[1]->type == AST_FUNC){
        return tacJoin(tacJoin(code0, code1), 
        tacCreate(type, makeTemp(), code0?code0->res:0, node->son[1]->symbol));
    }else if(node->son[0]->type == AST_READ){
        return tacJoin(tacJoin(code0, code1), 
        tacCreate(type, makeTemp(), node->son[0]->symbol, code1?code1->res:0));
    }else if(node->son[1]->type == AST_READ){
        return tacJoin(tacJoin(code0, code1), 
        tacCreate(type, makeTemp(), code0?code0->res:0, node->son[1]->symbol));
    }else{
        return tacJoin(tacJoin(code0, code1), 
        tacCreate(type, makeTemp(), code0?code0->res:0, code1?code1->res:0));
    }
}


TAC* makeFuncWithoutParam(AST* node,TAC* code1){
     return tacJoin(tacCreate(TAC_FUNC_BEGUN, node->symbol, 0 , 0), tacJoin(code1, tacCreate(TAC_FUNC_END, node->symbol, 0 , 0)));
}

TAC* makeCallFunc(AST *node, TAC* code0){
    return tacJoin(code0, tacCreate(TAC_CALL_FUNC, node->symbol, 0 , 0));
}

TAC* makeFunc(AST *node, TAC* code0, TAC* code1)
{
    return tacJoin(code0, tacJoin(tacCreate(TAC_FUNC_BEGUN, node->symbol, 0 , 0), tacJoin(code1, tacCreate(TAC_FUNC_END, node->symbol, 0 , 0))));
};

TAC* makePrint(AST* node)
{
    return tacCreate(TAC_PRINT, node->son[0]->symbol, 0, 0);
}

TAC* makeRead()
{
    HASH_NODE * labelRead = 0;
    labelRead = makeLabel();
    return tacCreate(TAC_READ,labelRead,0,0);
}

TAC* makeIfThen(TAC* code0, TAC* code1)
{
    TAC * jumptac = 0;
    TAC * labeltac = 0;
    HASH_NODE * newlabel = 0;
    newlabel = makeLabel();

    jumptac = tacCreate(TAC_JFALSE, newlabel, code0?code0->res:0, 0);
    labeltac = tacCreate(TAC_LABEL, newlabel, 0, 0);
    return tacJoin(tacJoin(code0, jumptac), tacJoin(code1, labeltac));
}

TAC *makeIfThenElse(TAC *code0, TAC *code1, TAC *code2) 
{
    TAC *tacElse = 0;
    TAC *tacFim = 0;
    TAC *labelTacElse = 0;
    TAC *labelTacFim = 0;
    HASH_NODE *labelElse = 0;
    HASH_NODE *labelFim = 0;

    labelElse = makeLabel();
    labelFim = makeLabel();
    tacElse = tacCreate(TAC_JFALSE,labelElse,code0?code0->res:0,0);
    tacFim = tacCreate(TAC_JUMP,labelFim,0,0);
    labelTacElse = tacCreate(TAC_LABEL,labelElse,0,0);
    labelTacFim = tacCreate(TAC_LABEL,labelFim,0,0);

    return tacJoin(code0, tacJoin(tacElse, tacJoin(code1, tacJoin(tacFim, tacJoin(labelTacElse, tacJoin(code2, labelTacFim))))));
}

TAC* makeWhile(TAC *code0, TAC *code1){
    TAC *tacJumpInicio = 0;
    TAC *tacJumpFim = 0;
    TAC *labelTacInicio = 0;
    TAC *labelTacFim = 0;
    HASH_NODE *labelInicio = 0;
    HASH_NODE *labelFim = 0;

    labelInicio = makeLabel();
    labelFim = makeLabel();

    tacJumpFim = tacCreate(TAC_JFALSE,labelFim,code0?code0->res:0,0);
    tacJumpInicio = tacCreate(TAC_JUMP,labelInicio,0,0);
    labelTacInicio = tacCreate(TAC_LABEL, labelInicio,0,0);
    labelTacFim = tacCreate(TAC_LABEL, labelFim,0,0);

    return tacJoin(labelTacInicio, tacJoin(code0, tacJoin(tacJumpFim, tacJoin(code1, tacJoin(tacJumpInicio, labelTacFim)))));
}



