etapa2:	y.tab.c lex.yy.c
	gcc -o etapa2 lex.yy.c

y.tab.c: parser.y
	bison -dy parser.y		

lex.yy.c: scanner.l
	flex scanner.l

clean: 
	rm lex.yy.c y.tab.c etapa2
	