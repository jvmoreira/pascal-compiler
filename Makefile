$DEPURA=1

compilador: lex.yy.c y.tab.c helpers.o helpers.h
	gcc lex.yy.c compilador.tab.c helpers.o -o compilador -ll -ly -lc

lex.yy.c: compilador.l helpers.h
	flex compilador.l

y.tab.c: compilador.y helpers.h
	bison compilador.y -d -v

compilador.o : helpers.h compiladorF.c
	gcc -c helpers.c -o helpers.o

helpers: helpers.c helpers.h
	gcc -Wall helpers.c -o helpers && ./helpers

clean :
	rm -f compilador.tab.* lex.yy.c compilador.o compilador.output
