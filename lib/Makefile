CFLAGS = -Wall -Wextra -Werror -I include

LIB = libmepa.a

MEPA_FILES = mepa/utils	\
		mepa/pilhas		\
		mepa/rotulos	\
		mepa/while

STACK_FILES = stack/helpers	\
		stack/symbol	\
		stack/value		\
		stack/item		\
		stack/stack

FILES = $(MEPA_FILES) $(STACK_FILES)

OBJECTS = $(addsuffix .o, $(FILES))

.PHONY: all clean

all: lib

lib: $(LIB)( $(OBJECTS) )
	@echo Static Library compiled!

clean:
	@echo Removing static library
	@rm -f $(LIB)
