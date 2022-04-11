//Vítor Badlez Maciel - 00264312
//AST - Abstrac Sintax Tree

#include<stdio.h>
#include<stdlib.h>
#include "ast.h"

FILE *yyout;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3)
{

    AST *newnode;
    newnode = (AST*) calloc(1, sizeof(AST));
    newnode->type = type;
    newnode->symbol = symbol;
    newnode->son[0] = s0;
    newnode->son[1] = s1;
    newnode->son[2] = s2;
    newnode->son[3] = s3;
    newnode->lineNumber = getLineNumber();
    //newnode->datatype = ERROR_DATATYPE;
    return newnode;
}

void astPrint(AST *node, int level)
{

    int i=0;
    if(node == 0)
        return;
    for(i=0; i<level; i++)
        fprintf(stderr, "  ");  
    fprintf(stderr, "ast(" );

    switch(node->type)
    {
        case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
        case AST_ADD: fprintf(stderr, "AST_ADD"); break;
        case AST_SUB: fprintf(stderr, "AST_SUB"); break; 
        case AST_MUL: fprintf(stderr, "AST_MUL"); break; 
        case AST_DIV: fprintf(stderr, "AST_DIV"); break; 
        case AST_LE: fprintf(stderr, "AST_LE"); break; 
        case AST_GE: fprintf(stderr, "AST_GE"); break; 
        case AST_EQ: fprintf(stderr, "AST_EQ"); break;
        case AST_DIF: fprintf(stderr, "AST_DIF"); break;
        case AST_GT: fprintf(stderr, "AST_GT"); break;
        case AST_LT: fprintf(stderr, "AST_LT"); break;
        case AST_READ: fprintf(stderr, "AST_READ"); break;
        case AST_ARRAY: fprintf(stderr, "AST_ARRAY"); break;
        case AST_FUNC: fprintf(stderr, "AST_FUNC"); break;
        case AST_REXPR: fprintf(stderr, "AST_REXPR"); break;
        case AST_LEXPR: fprintf(stderr, "AST_LEXPR"); break;
        case AST_PARENTESES: fprintf(stderr, "AST_PARENTESES"); break;
        case AST_LCMD: fprintf(stderr, " AST_LCMD"); break;
        case AST_LABEL: fprintf(stderr, "AST_LABEL"); break;
        case AST_BODY1: fprintf(stderr, "AST_BODY1"); break;
        case AST_BODY2: fprintf(stderr, "AST_BODY2"); break;
        case AST_CMD: fprintf(stderr, "AST_CMD"); break;
        case AST_ATRIBUTE: fprintf(stderr, "AST_ATRIBUTE"); break;
        case AST_PRINT: fprintf(stderr, "AST_PRINT"); break;
        case AST_LPRINT: fprintf(stderr, "AST_LPRINT"); break;
        case AST_RPRINT: fprintf(stderr, "AST_RPRINT"); break;
        case AST_RETURN: fprintf(stderr, "AST_RETURN"); break;
        case AST_GOTO: fprintf(stderr, "AST_GOTO"); break;
        case AST_WHILE: fprintf(stderr, "AST_WHILE"); break;
        case AST_IFTHEN: fprintf(stderr, "AST_IFTHEN"); break;
        case AST_IFTHENELSE: fprintf(stderr, "AST_IFTHENELSE"); break;
        case AST_PARAMETROS: fprintf(stderr, "AST_PARAMETROS"); break;
        case AST_RPARAMETROS: fprintf(stderr, "AST_RPARAMETROS"); break;
        case AST_FUNC_INT: fprintf(stderr, "AST_FUNC_INT"); break;
        case AST_FUNC_CHAR: fprintf(stderr, "AST_FUNC_CHAR"); break;
        case AST_FUNC_FLOAT: fprintf(stderr, "AST_FUNC_FLOAT"); break;
        case AST_DECL: fprintf(stderr, "AST_DECL"); break;
        case AST_ATR_CHAR: fprintf(stderr, "AST_ATR_CHAR"); break;
        case AST_ATR_INT: fprintf(stderr, "AST_ATR_INT"); break;
        case AST_ATR_FLOAT: fprintf(stderr, "AST_ATR_FLOAT"); break;
        case AST_LARRAY: fprintf(stderr, "AST_LARRAY"); break;
        case AST_ATR_VETOR_CHAR: fprintf(stderr, "AST_ATR_VETOR_CHAR"); break;
        case AST_ATR_VETOR_INT: fprintf(stderr, "AST_ATR_VETOR_INT"); break;
        case AST_ATR_VETOR_FLOAT: fprintf(stderr, "AST_ATR_VETOR_FLOAT"); break;
        case AST_SYMBOL_INT: fprintf(stderr, "AST_SYMBOL_INT"); break;
        case AST_SYMBOL_FLOAT: fprintf(stderr, "AST_SYMBOL_FLOAT"); break;
        case AST_SYMBOL_CHAR: fprintf(stderr, "AST_SYMBOL_CHAR"); break;
        case AST_REXPRP: fprintf(stderr, "AST_REXPRP"); break;
        default: fprintf(stderr, "AST_UNKNOWN"); break;
    }
    
    if(node->symbol != 0)
    {
        fprintf(stderr, ", %s\n", node->symbol->text);
    }
    else
    {
            fprintf(stderr,", 0\n");
    }

    for(i=0; i<MAX_SONS; ++i)
        astPrint(node->son[i], level+1);
}

void geraArquivoAST(AST *node, FILE *out)
{
	if (node == 0) return;

    switch (node->type)
    {
        case AST_DECL: 
                    geraArquivoAST(node->son[0], out);
			        geraArquivoAST(node->son[1], out);
		break;
        
        ///////DECLARAÇÃO CHAR
        case AST_ATR_CHAR:
                    fprintf(out," char ");
                    fprintf(out,"%s: ", node->symbol->text); 
			        geraArquivoAST(node->son[0], out);
			        fprintf(out, ";\n");
		break;

        case AST_ATR_VETOR_CHAR:
                    fprintf(out," char ");
                    fprintf(out,"%s", node->symbol->text); 
                    fprintf(out,"[");
                    geraArquivoAST(node->son[0], out);
                    fprintf(out,"]");
                    if(node->son[1]){
                        fprintf(out,":");
                        geraArquivoAST(node->son[1], out);
                    }
                    fprintf(out,";\n");
		break;

        case AST_FUNC_CHAR:
                    fprintf(out," char ");
                    fprintf(out,"%s", node->symbol->text); 
                    fprintf(out,"(");
                    geraArquivoAST(node->son[0], out);
                    fprintf(out,")");
                    if(node->son[1]){
                        geraArquivoAST(node->son[1], out);
                    }
                    fprintf(out,"\n");
		break;

        ///////DECLARAÇÃO INT
        case AST_ATR_INT:
                    fprintf(out," int ");
                    fprintf(out,"%s: ", node->symbol->text); 
			        geraArquivoAST(node->son[0], out);
			        fprintf(out, ";\n");
		break;

        case AST_ATR_VETOR_INT:
                    fprintf(out," int ");
                    fprintf(out,"%s", node->symbol->text); 
                    fprintf(out,"[");
                    geraArquivoAST(node->son[0], out);
                    fprintf(out,"]");
                    if(node->son[1]){
                        fprintf(out,":");
                        geraArquivoAST(node->son[1], out);
                    }
                    fprintf(out,";\n");
		break;

        case AST_FUNC_INT:
                    fprintf(out," int ");
                    fprintf(out,"%s", node->symbol->text); 
                    fprintf(out,"(");
                    geraArquivoAST(node->son[0], out);
                    fprintf(out,")");
                    if(node->son[1]){
                        geraArquivoAST(node->son[1], out);
                    }
                    fprintf(out,"\n");
		break;


        ///////DECLARAÇÃO FLOAT
        case AST_ATR_FLOAT:
                    fprintf(out," float ");
                    fprintf(out,"%s: ", node->symbol->text); 
			        geraArquivoAST(node->son[0], out);
                    fprintf(out,"/");
                    geraArquivoAST(node->son[1], out);
			        fprintf(out, ";\n");
		break;

        case AST_ATR_VETOR_FLOAT:
                    fprintf(out," float ");
                    fprintf(out,"%s", node->symbol->text); 
                    fprintf(out,"[");
                    geraArquivoAST(node->son[0], out);
                    fprintf(out,"]");
                    if(node->son[1]){
                        fprintf(out,":");
                        geraArquivoAST(node->son[1], out);
                    }
                    fprintf(out,";\n");
        break;

        case AST_FUNC_FLOAT:
                    fprintf(out," float ");
                    fprintf(out,"%s", node->symbol->text); 
                    fprintf(out,"(");
                    geraArquivoAST(node->son[0], out);
                    fprintf(out,")");
                    if(node->son[1]){
                        geraArquivoAST(node->son[1], out);
                    }
                    fprintf(out,"\n");
		break;

        ///////DECLARAÇÃO ARRAY
        case AST_LARRAY:
                    geraArquivoAST(node->son[0], out);
                    geraArquivoAST(node->son[1], out);
        break;

        ///////PARAMETROS
        case AST_PARAMETROS:
                    geraArquivoAST(node->son[0], out);
                    geraArquivoAST(node->son[1], out); 
		break;

        case AST_RPARAMETROS:
                    fprintf(out,", ");
                    geraArquivoAST(node->son[0], out);
                    geraArquivoAST(node->son[1], out); 
		break;

        case AST_SYMBOL_INT:
                     fprintf(out,"int ");
                     fprintf(out,"%s", node->symbol->text);
		break;

        case AST_SYMBOL_FLOAT:
                     fprintf(out,"float ");
                     fprintf(out,"%s", node->symbol->text);
		break;

        case AST_SYMBOL_CHAR:
                     fprintf(out,"char ");
                     fprintf(out,"%s", node->symbol->text);
                     geraArquivoAST(node->son[0], out);
		break;

        ///////COMANDOS
        case AST_ATRIBUTE:
                     fprintf(out,"  %s", node->symbol->text);
                     if(node->son[1]){
                        fprintf(out,"[");
                        geraArquivoAST(node->son[0], out);
                        fprintf(out,"]");
                        fprintf(out," = ");
                        geraArquivoAST(node->son[1], out);
                     }else
                     {
                        fprintf(out," = ");
                        geraArquivoAST(node->son[0], out);
                     }
        break;

        case AST_BODY1:
                     fprintf(out,"\n{\n");
                     geraArquivoAST(node->son[0], out);
                     fprintf(out,"}");
		break;

        case AST_BODY2:
                     geraArquivoAST(node->son[0], out);
		break;

        case AST_LCMD:
                     geraArquivoAST(node->son[0], out);
                     fprintf(out,";\n");
                     geraArquivoAST(node->son[1], out);
		break;


        case AST_PRINT:
                    fprintf(out, "  print ");
                    geraArquivoAST(node->son[0], out);
		break;

        case AST_LPRINT:
                     geraArquivoAST(node->son[0], out);
                     fprintf(out,",");
                     geraArquivoAST(node->son[1], out);
		break;

        case AST_RPRINT:
                     geraArquivoAST(node->son[0], out);
		break;

        case AST_REXPRP:
                     geraArquivoAST(node->son[0], out);
		break;

        case AST_RETURN:
                     fprintf(out, "  return ");
                     geraArquivoAST(node->son[0], out); 
		break;

        case AST_GOTO:
                     fprintf(out, "  goto "); 
                     fprintf(out,"%s", node->symbol->text);
		break;

        case AST_WHILE:
                     fprintf(out, "\n while "); 
                     geraArquivoAST(node->son[0], out);
                     geraArquivoAST(node->son[1], out);
		break;

        case AST_IFTHEN:
                     fprintf(out, "\n if "); 
                     geraArquivoAST(node->son[0], out);
                     fprintf(out, " then ");
                     geraArquivoAST(node->son[1], out);
		break;

        case AST_IFTHENELSE:
                     fprintf(out, "\n if "); 
                     geraArquivoAST(node->son[0], out);
                     fprintf(out, " then ");
                     geraArquivoAST(node->son[1], out);
                     fprintf(out, " else ");
                     geraArquivoAST(node->son[2], out);
        break;

        case AST_LABEL:
                     fprintf(out,"  %s", node->symbol->text); 
                     fprintf(out, ":\n");
                     geraArquivoAST(node->son[0], out);
		break;


        ///////EXPRESSÃO
        case AST_SYMBOL:
                    fprintf(out,"%s", node->symbol->text); 
		break;

        case AST_READ:
                    fprintf(out, "read"); 
		break;
        
        case AST_ADD:
                    geraArquivoAST(node->son[0], out); 
                    fprintf(out, " + ");
                    geraArquivoAST(node->son[1], out);
		break;

        case AST_SUB:
                    geraArquivoAST(node->son[0], out); 
                    fprintf(out, " - ");
                    geraArquivoAST(node->son[1], out); 
		break;   

        case AST_MUL:
                    geraArquivoAST(node->son[0], out); 
                    fprintf(out, " * ");
                    geraArquivoAST(node->son[1], out); 
		break;

        case AST_DIV:
                    geraArquivoAST(node->son[0], out); 
                    fprintf(out, " / ");
                    geraArquivoAST(node->son[1], out); 
		break;

        case AST_LE:
                    geraArquivoAST(node->son[0], out); 
                    fprintf(out, " <= ");
                    geraArquivoAST(node->son[1], out); 
		break; 

        case AST_GE:
                    geraArquivoAST(node->son[0], out); 
                    fprintf(out, " >= ");
                    geraArquivoAST(node->son[1], out); 
		break; 

        case AST_EQ:
                    geraArquivoAST(node->son[0], out); 
                    fprintf(out, " == ");
                    geraArquivoAST(node->son[1], out); 
		break; 

        case AST_DIF:
                    geraArquivoAST(node->son[0], out); 
                    fprintf(out, " != ");
                    geraArquivoAST(node->son[1], out); 
		break; 

        case AST_GT:
                    geraArquivoAST(node->son[0], out); 
                    fprintf(out, " > ");
                    geraArquivoAST(node->son[1], out); 
		break; 

        case AST_LT:
                    geraArquivoAST(node->son[0], out); 
                    fprintf(out, " < ");
                    geraArquivoAST(node->son[1], out); 
		break; 

        case AST_PARENTESES:
                    fprintf(out, "(");
                    geraArquivoAST(node->son[0], out);  
                    fprintf(out, ")");
		break;

        case AST_ARRAY:
                    fprintf(out,"%s", node->symbol->text);
                    fprintf(out, "[");
                    geraArquivoAST(node->son[0], out);  
                    fprintf(out, "]");
		break;

        case AST_FUNC:
                    fprintf(out,"%s", node->symbol->text);
                    fprintf(out, "(");
                    geraArquivoAST(node->son[0], out);  
                    fprintf(out, ")");
		break;


        ///////LISTA DE EXPRESSÃO
        case AST_LEXPR:
                    geraArquivoAST(node->son[0], out);  
                    geraArquivoAST(node->son[1], out);
		break;

        case AST_REXPR:
                    fprintf(out, ", ");
                    geraArquivoAST(node->son[0], out);  
                    geraArquivoAST(node->son[1], out);
		break;
    }
}