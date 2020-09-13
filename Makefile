LDFLAGS = -L lib
CFLAGS = -Wall -I lib/include
LDLIBS = -ll -ly -lc -lmepa

$DEPURA=1

TARGET = compilador

.PHONY: all lib clean

all: $(TARGET)

$(TARGET): lib lex.yy.c y.tab.c
	gcc $(CFLAGS) $(LDFLAGS) lex.yy.c compilador.tab.c -o $(TARGET) $(LDLIBS)

lib:
	@make -C lib -s

lex.yy.c: compilador.l
	flex compilador.l

y.tab.c: compilador.y
	bison compilador.y -d -v

clean:
	@echo Cleaning files...
	@rm -f compilador.tab.* lex.yy.c compilador.output

purge: clean
	@rm -f $(TARGET)
