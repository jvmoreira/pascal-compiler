CFLAGS = -Wall -Wextra -I ./ -I ../ -I ../../stack/headers
LDLIBS = -L $(LIBS_DIR) -l$(LIB)

LIB = stack
LIBS_DIR = ../../

TARGET = execute-tests

FILES = $(TARGET)						\
				../testCase					\
				helpers-test				\
				symbol-test   			\
				default-item-test

OBJECTS = $(addsuffix .o, $(FILES))

.PHONY: all clean purge

all: lib $(TARGET)

lib:
	@make $(LIB) -C $(LIBS_DIR) -s

$(TARGET): $(OBJECTS)

clean:
	@echo Cleaning object files...
	@rm -f $(OBJECTS)

purge: clean
	@rm -f $(TARGET)
