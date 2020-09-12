LDFLAGS = -L lib
CFLAGS = -Wall -I lib/include
LDLIBS = -ll -ly -lc -lmepa -lstack

$DEPURA=1

TARGET = compilador

.PHONY: all libs clean

all: $(TARGET)

$(TARGET): libs lex.yy.c y.tab.c
	gcc $(CFLAGS) $(LDFLAGS) lex.yy.c compilador.tab.c -o compilador $(LDLIBS)

libs:
	@make -C lib

lex.yy.c: compilador.l
	flex compilador.l

y.tab.c: compilador.y
	bison compilador.y -d -v

clean:
	@echo Cleaning files...
	@rm -f compilador.tab.* lex.yy.c compilador.output

purge: clean
	@rm -f $(TARGET)
