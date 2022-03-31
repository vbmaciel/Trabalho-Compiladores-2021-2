//Vítor Badlez Maciel - 00264312

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

%token TK_IDENTIFIER     

%token LIT_INTEGER     
%token LIT_CHAR        
%token LIT_STRING  
%token TOKEN_ERROR      



%%

programa: decl

decl: dec resto
    |
    ;

resto: dec resto
     |
     ;
    
dec:  KW_CHAR TK_IDENTIFIER ':' LIT_CHAR ';'
    | KW_CHAR TK_IDENTIFIER ':' LIT_INTEGER ';'
    | KW_CHAR TK_IDENTIFIER'[' LIT_INTEGER ']' ':' larray ';'
    | KW_CHAR TK_IDENTIFIER'[' LIT_INTEGER ']' ';'
    | KW_CHAR TK_IDENTIFIER '(' lparameters ')' 
    | KW_CHAR TK_IDENTIFIER '(' lparameters ')' cmd
    | KW_INT TK_IDENTIFIER ':' LIT_CHAR ';'
    | KW_INT TK_IDENTIFIER ':' LIT_INTEGER ';'
    | KW_INT TK_IDENTIFIER'[' LIT_INTEGER ']' ':' larray ';'
    | KW_INT TK_IDENTIFIER'[' LIT_INTEGER ']' ';'
    | KW_INT TK_IDENTIFIER '(' lparameters ')' 
    | KW_INT TK_IDENTIFIER '(' lparameters ')' cmd
    | KW_FLOAT TK_IDENTIFIER ':' LIT_INTEGER '/' LIT_INTEGER ';'
    | KW_FLOAT TK_IDENTIFIER'[' LIT_INTEGER ']' ':' larray ';'
    | KW_FLOAT TK_IDENTIFIER'[' LIT_INTEGER ']' ';'
    | KW_FLOAT TK_IDENTIFIER '(' lparameters ')' 
    | KW_FLOAT TK_IDENTIFIER '(' lparameters ')' cmd
    ;

larray: array larray
      |
      ;

array: LIT_CHAR
     | LIT_INTEGER
     ;

lparameters: parameters rparameters
           |
           ;

rparameters: ',' parameters rparameters
    |
    ;

parameters: KW_INT TK_IDENTIFIER
          | KW_FLOAT TK_IDENTIFIER 
          | KW_CHAR TK_IDENTIFIER
          ;

body: '{' lcmd '}'
    ;

lcmd: cmd ';' lcmd
    | label
    |
    ;

 cmd:
    | TK_IDENTIFIER '=' expr
    | TK_IDENTIFIER'[' expr ']' '=' expr 
    | KW_PRINT TK_IDENTIFIER 
    | KW_PRINT lpprint
    | KW_PRINT TK_IDENTIFIER'[' LIT_INTEGER ']' 
    | KW_RETURN expr 
    | KW_GOTO expr 
    | TK_IDENTIFIER '=' KW_READ 
    | KW_GOTO expr       {printf("ACHOUGOTO");}
    | KW_WHILE expr cmd
    | KW_IF expr KW_THEN cmd
    | KW_IF expr KW_THEN cmd KW_ELSE cmd 
    | body
    | 
    ;

label: TK_IDENTIFIER ':' lcmd
    ;

lpprint: pprint ',' lpprint
       | pprint
       ;

pprint: LIT_STRING
       | expr
       ; 

lexpr: expr rexpr
    | 
    ;

rexpr: ',' expr rexpr
    |
    ;

expr: LIT_INTEGER
    | TK_IDENTIFIER
    | LIT_CHAR				
    | KW_READ				{printf("ACHOU");}
    | expr '+' expr 
    | expr '-' expr
    | expr '*' expr 
    | expr '/' expr 
    | expr OPERATOR_LE expr 
    | expr OPERATOR_GE expr 
    | expr OPERATOR_EQ expr 
    | expr OPERATOR_DIF expr 
    | expr '>' expr
    | expr '<' expr
    | '(' expr ')'
    | TK_IDENTIFIER '[' expr ']'
    | TK_IDENTIFIER '(' lexpr ')' 
    ;


%%

int yyerror()
{
    fprintf(stderr, "Sintax error at line %d.\n", getLineNumber());
    exit(3);
}