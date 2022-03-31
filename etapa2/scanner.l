%{

//Vítor Badlez Maciel - 00264312

int getLineNumber();
int isRunning();
void initMe(void);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
#include "hash.h"

int contalinhas = 1;
int running = 1;

%}

%x TEXTO

%%

char                                    return KW_CHAR;
int                                     return KW_INT;
float                                   return KW_FLOAT; 
if   	                                  return KW_IF;
then   	                                return KW_THEN;
else  	                                return KW_ELSE;
while                                   return KW_WHILE;
goto                                    return KW_GOTO;
read                                    return KW_READ;
print                                   return KW_PRINT;
return                                  return KW_RETURN;
[\,\;\:\(\)\[\]\{\}\+\-\*\/\<\>\=]      return yytext[0];
"<="                                    return OPERATOR_LE;  
">="                                    return OPERATOR_GE; 
"=="                                    return OPERATOR_EQ; 
"!="                                    return OPERATOR_DIF; 
\'.\'                                   {hashInsert(yytext, LIT_CHAR);return LIT_CHAR;}
\"(\\\"|[^\"\n])*\"                     {hashInsert(yytext, LIT_STRING); return LIT_STRING;}
[0-9]+                                  {hashInsert(yytext, LIT_INTEGER); return LIT_INTEGER;} 
[a-z\-\_]+                              {hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER;} 
"\n"                                    contalinhas++;
"\\*"						                        BEGIN(TEXTO);
"\\""\\".*					                    
[ \t] 
.                                       return TOKEN_ERROR; 

<TEXTO>.                                
<TEXTO>"\n"                             contalinhas++;
<TEXTO>"*\\"                            BEGIN(INITIAL);

%%

#include "y.tab.c"
#include "hash.c"
#include "main.c"

void initMe(void){
  hashInit();
}

int yywrap()
{
  running = 0;
  return 1;
}

int getLineNumber()
{
  return contalinhas;
}

int isRunning()
{
    return running;
}