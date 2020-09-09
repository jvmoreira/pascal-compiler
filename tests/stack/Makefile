LIB = stack
LIBS_DIR = ../../
CFLAGS = -Wall -Wextra -I ./headers -I ../ -I ../../$(LIB)/headers
LDFLAGS = -L $(LIBS_DIR)
LDLIBS = -l$(LIB)


TARGET = execute-tests

FILES = $(TARGET)						\
				../testCase					\
				helpers-test				\
				symbol-test   			\
				value-test					\
				item-test						\
				stack-test

OBJECTS = $(addsuffix .o, $(FILES))

.PHONY: all clean purge

all: lib $(TARGET)

run: all
	./$(TARGET)

lib:
	@make $(LIB) -C $(LIBS_DIR)

$(TARGET): $(OBJECTS)

clean:
	@echo Cleaning object files...
	@rm -f $(OBJECTS)

purge: clean
	@rm -f $(TARGET)
