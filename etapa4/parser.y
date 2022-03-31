//Vítor Badlez Maciel - 00264312
%{
    #include "hash.h" 
    #include "ast.h"
    #include "ast.c"
    #include "semantic.h"
    int yyerror(); 
    int getLineNumber();
    int yylex(); 

    FILE *out = NULL;
%}

%union
{    
    HASH_NODE *symbol;
    AST* ast;
}

%token KW_CHAR        
%token KW_INT          
%token KW_FLOAT       

%token KW_IF           
%token KW_THEN         
%token KW_ELSE          
%token KW_WHILE        
%token KW_GOTO         
%token KW_READ       
%token KW_PRINT      
%token KW_RETURN      

%token OPERATOR_LE      
%token OPERATOR_GE      
%token OPERATOR_EQ       
%token OPERATOR_DIF      

%token<symbol> TK_IDENTIFIER     
%token<symbol> LIT_INTEGER  
%token<symbol> LIT_CHAR 
%token<symbol> LIT_STRING   
       
%token TOKEN_ERROR      

%type<ast> programa
%type<ast> expr
%type<ast> rexpr
%type<ast> lexpr
%type<ast> body 
%type<ast> lcmd 
%type<ast> cmd
%type<ast> label
%type<ast> parameters 
%type<ast> rparameters
%type<ast> lparameters
%type<ast> array
%type<ast> larray
%type<ast> dec
%type<ast> decl
%type<ast> lprint
%type<ast> rprint

%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF '<' '>' 
%left '+' '-'
%left '*' '/'

%%

programa: decl                                                      {   $$ = $1; 
                                                                        astPrint($1, 0); 
                                                                        geraArquivoAST($1, out); 
                                                                        check_and_set_declarations($1);
                                                                        check_undeclared();
                                                                        check_operands($1);
                                                                        check_function_with_return($1);
                                                                    }
        ;
        
decl: dec decl                                                      { $$ = astCreate(AST_DECL, 0, $1, $2, 0, 0); }
    |                                                               { $$ = 0; }
    ;
    
dec:  KW_CHAR TK_IDENTIFIER ':' LIT_CHAR ';'                        { $$ = astCreate(AST_ATR_CHAR, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0, 0); }
    | KW_CHAR TK_IDENTIFIER ':' LIT_INTEGER ';'                     { $$ = astCreate(AST_ATR_CHAR, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0, 0); }
    | KW_CHAR TK_IDENTIFIER'[' LIT_INTEGER ']' ':' larray ';'       { $$ = astCreate(AST_ATR_VETOR_CHAR, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), $7, 0, 0); }
    | KW_CHAR TK_IDENTIFIER'[' LIT_INTEGER ']' ';'                  { $$ = astCreate(AST_ATR_VETOR_CHAR, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0, 0); }
    | KW_CHAR TK_IDENTIFIER '(' lparameters ')' cmd                 { $$ = astCreate(AST_FUNC_CHAR, $2, $4, $6, 0, 0); } 
    | KW_INT TK_IDENTIFIER ':' LIT_CHAR ';'                         { $$ = astCreate(AST_ATR_INT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0, 0); }
    | KW_INT TK_IDENTIFIER ':' LIT_INTEGER ';'                      { $$ = astCreate(AST_ATR_INT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0, 0); }
    | KW_INT TK_IDENTIFIER'[' LIT_INTEGER ']' ':' larray ';'        { $$ = astCreate(AST_ATR_VETOR_INT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), $7, 0, 0); }
    | KW_INT TK_IDENTIFIER'[' LIT_INTEGER ']' ';'                   { $$ = astCreate(AST_ATR_VETOR_INT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0, 0); } 
    | KW_INT TK_IDENTIFIER '(' lparameters ')' cmd                  { $$ = astCreate(AST_FUNC_INT, $2, $4, $6, 0, 0); }        
    | KW_FLOAT TK_IDENTIFIER ':' LIT_INTEGER '/' LIT_INTEGER ';'    { $$ = astCreate(AST_ATR_FLOAT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), astCreate(AST_SYMBOL, $6, 0, 0, 0, 0), 0, 0); }
    | KW_FLOAT TK_IDENTIFIER'[' LIT_INTEGER ']' ':' larray ';'      { $$ = astCreate(AST_ATR_VETOR_FLOAT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), $7, 0, 0); }
    | KW_FLOAT TK_IDENTIFIER'[' LIT_INTEGER ']' ';'                 { $$ = astCreate(AST_ATR_VETOR_FLOAT, $2, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0, 0); }
    | KW_FLOAT TK_IDENTIFIER '(' lparameters ')' cmd                { $$ = astCreate(AST_FUNC_FLOAT, $2, $4, $6, 0, 0); } 
    ;

larray: array larray                                                { $$ = astCreate(AST_LARRAY, 0, $1, $2, 0, 0); }
      |                                                             { $$ = 0; }
      ;

array: LIT_CHAR                                                     { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }        
     | LIT_INTEGER                                                  { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
     ;

lparameters: parameters rparameters                 { $$ = astCreate(AST_PARAMETROS, 0, $1, $2, 0, 0); }
           |                                        { $$ = 0; }
           ;

rparameters: ',' parameters rparameters             { $$ = astCreate(AST_RPARAMETROS, 0, $2, $3, 0, 0); }    
    |                                               { $$ = 0; }
    ;

parameters: KW_INT TK_IDENTIFIER                    { $$ = astCreate(AST_SYMBOL_INT, $2, 0, 0, 0, 0); }         
          | KW_FLOAT TK_IDENTIFIER                  { $$ = astCreate(AST_SYMBOL_FLOAT, $2, 0, 0, 0, 0); }
          | KW_CHAR TK_IDENTIFIER                   { $$ = astCreate(AST_SYMBOL_CHAR, $2, 0, 0, 0, 0); }
          ;

body: '{' lcmd '}'                                  { $$ = astCreate(AST_BODY1, 0, $2, 0, 0, 0); }                       
    ;

lcmd: cmd ';' lcmd                                  { $$ = astCreate(AST_LCMD, 0, $1, $3, 0, 0); }
    | label                                         { $$ = $1; }
    |                                               { $$ = 0; }
    ;

 cmd: TK_IDENTIFIER '=' expr                        { $$ = astCreate(AST_ATRIBUTE, $1, $3, 0, 0, 0); }      
    | TK_IDENTIFIER'[' expr ']' '=' expr            { $$ = astCreate(AST_ATRIBUTE, $1, $3, $6, 0, 0); }
    | KW_PRINT lprint                               { $$ = astCreate(AST_PRINT, 0, $2, 0, 0, 0); }
    | KW_RETURN expr                                { $$ = astCreate(AST_RETURN, 0, $2, 0, 0, 0); }
    | KW_GOTO TK_IDENTIFIER                         { $$ = astCreate(AST_GOTO, $2, 0, 0, 0, 0); } 
    | KW_WHILE expr cmd                             { $$ = astCreate(AST_WHILE, 0, $2, $3, 0, 0); }
    | KW_IF expr KW_THEN cmd                        { $$ = astCreate(AST_IFTHEN, 0, $2, $4, 0, 0); }
    | KW_IF expr KW_THEN cmd KW_ELSE cmd            { $$ = astCreate(AST_IFTHENELSE, 0, $2, $4, $6, 0); }
    | body                                          { $$ = astCreate(AST_BODY2, 0, $1, 0, 0, 0); }
    |                                               { $$ = 0; }
    ;
                          

label: TK_IDENTIFIER ':' lcmd                       { $$ = astCreate(AST_LABEL, $1, $3, 0, 0, 0); }                
    ;

lprint: rprint ',' lprint                           { $$ = astCreate(AST_LPRINT, 0, $1, $3, 0, 0); }
       | rprint                                     { $$ = astCreate(AST_RPRINT, 0, $1, 0, 0, 0); }
       ;    

rprint: LIT_STRING                                  { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
       | expr                                       { $$ = astCreate(AST_REXPRP, 0, $1, 0, 0, 0); }
       ; 

lexpr: expr rexpr                                   { $$ = astCreate(AST_LEXPR, 0, $1, $2, 0, 0); }
    |                                               { $$ = 0; }
    ;

rexpr: ',' expr rexpr                               { $$ = astCreate(AST_REXPR, 0, $2, $3, 0, 0); }
    |                                               { $$ = 0; }
    ;

expr: LIT_INTEGER                                   { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | TK_IDENTIFIER                                 { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | LIT_CHAR                                      { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | KW_READ                                       { $$ = astCreate(AST_READ, 0, 0, 0, 0, 0); }
    | expr '+' expr                                 { $$ = astCreate(AST_ADD, 0, $1, $3, 0, 0); }
    | expr '-' expr                                 { $$ = astCreate(AST_SUB, 0, $1, $3, 0, 0); }
    | expr '*' expr                                 { $$ = astCreate(AST_MUL, 0, $1, $3, 0, 0); }
    | expr '/' expr                                 { $$ = astCreate(AST_DIV, 0, $1, $3, 0, 0); }
    | expr OPERATOR_LE expr                         { $$ = astCreate(AST_LE, 0, $1, $3, 0, 0); }
    | expr OPERATOR_GE expr                         { $$ = astCreate(AST_GE, 0, $1, $3, 0, 0); }
    | expr OPERATOR_EQ expr                         { $$ = astCreate(AST_EQ, 0, $1, $3, 0, 0); }
    | expr OPERATOR_DIF expr                        { $$ = astCreate(AST_DIF, 0, $1, $3, 0, 0); }
    | expr '>' expr                                 { $$ = astCreate(AST_GT, 0, $1, $3, 0, 0); }
    | expr '<' expr                                 { $$ = astCreate(AST_LT, 0, $1, $3, 0, 0); }
    | '(' expr ')'                                  { $$ = astCreate(AST_PARENTESES, 0, $2, 0, 0, 0); }
    | TK_IDENTIFIER '[' expr ']'                    { $$ = astCreate(AST_ARRAY, $1, $3, 0, 0, 0); }
    | TK_IDENTIFIER '(' lexpr ')'                   { $$ = astCreate(AST_FUNC, $1, $3, 0, 0, 0); }
    ;


%%

int yyerror()
{
    fprintf(stderr, "Sintax error at line %d.\n", getLineNumber());
    exit(3);
}