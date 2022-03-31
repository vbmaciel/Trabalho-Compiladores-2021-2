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
        exit(2);
      }
      yyin = file;
    }else {
        fprintf(stderr, "Call Etapa2 fileName\n");
        exit(1);
    }

    initMe();
    
    yyparse();
    fprintf(stderr, "Super! Compilation successful\n");

    hashPrint();
    exit(0); //Zero is code for success
}