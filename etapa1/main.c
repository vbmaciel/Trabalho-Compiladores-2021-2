//Vítor Badlez Maciel - 00264312
int main(int argc, char** argv)
{
  int p = 0, token = 0;
    
     if (argc > 1)
    {
      FILE *file;
      file = fopen(argv[1], "r");      
      if (!file)
      {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        exit(1);
      }
      yyin = file;
    }
    initMe();
    while(isRunning() != 0)
    {
        token = yylex();
        if(isRunning())
        {
            switch(token)
            {
                case KW_CHAR:       printf("KW_CHAR\n"); break;
                case KW_INT:        printf("KW_INT\n"); break;
                case KW_FLOAT:      printf("KW_FLOAT\n"); break;
                case KW_IF:         printf("KW_IF\n"); break;
                case KW_THEN:       printf("KW_THEN\n"); break;
                case KW_ELSE:       printf("KW_ELSE\n"); break;
                case KW_WHILE:      printf("KW_WHILE\n"); break;
                case KW_GOTO:       printf("KW_GOTO\n"); break;
                case KW_READ:       printf("KW_READ\n"); break;
                case KW_PRINT:      printf("KW_PRINT\n"); break;
                case KW_RETURN:     printf("KW_RETURN\n"); break;
                case OPERATOR_LE:   printf("OPERATOR_LE\n"); break;
                case OPERATOR_GE:   printf("OPERATOR_GE\n"); break;
                case OPERATOR_EQ:   printf("OPERATOR_EQ\n"); break;
                case OPERATOR_DIF:  printf("OPERATOR_DIF\n"); break;
                case LIT_CHAR:      printf("LIT_CHAR\n"); break;
                case LIT_STRING:    printf("LIT_STRING\n"); break;
                case LIT_INTEGER:   printf("LIT_INTEGER\n"); break;
                case TK_IDENTIFIER: printf("TK_IDENTIFIER\n"); break;
                case TOKEN_ERROR:   printf("TOKEN_ERROR\n"); break;
                default:            printf("Caracter Especial  %s\n", yytext); break;
            }
        }
    }
    p = getLineNumber();
    printf("Numero de linhas %d\n", p);
    hashPrint();

}