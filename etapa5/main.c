//Vítor Badlez Maciel - 00264312
#include<stdio.h>
#include "hash.h"

extern FILE *yyin;
extern FILE *out;
int yyparse();
void initMe();
int get_semantic_errors();


int main(int argc, char** argv)
{
  int p = 0, token = 0;
    
    initMe();

    if (argc > 2)
    {
      FILE *file;
      file = fopen(argv[1], "r");      
      if (!file)
      {
        fprintf(stderr, "Could not open input file in%s\n", argv[1]);
        exit(2);
      }
      yyin = file;
      
      out = fopen(argv[2], "w+");      
      if (!out)
      {
        fprintf(stderr, "Could not create output file %s\n", argv[2]);
        exit(2);
      }

    }else {
        fprintf(stderr, "Call Etapa2 fileName\n");
        exit(1);
    }

      yyparse();

    int erro = 0;
    if ((erro=get_semantic_errors()) != 0) {
        fprintf(stderr,"%d Semantic errors", erro);
        exit(4);
    } else {
        hashPrint();
        printf("Super! Compilation successful\n");
    }

    
    //fprintf(stderr, "Super! Compilation successful\n");

    //hashPrint();

    fclose(out);
    exit(0); //Zero is code for success
}