CFLAGS = -Wall -Wextra -Werror -I include

LIB = libmepa.a

MEPA_FILES = mepa/escopo \
		mepa/subrotinas \
		mepa/desvios    \
		mepa/utils

STACK_FILES = stack/stack \
		stack/item       \
		stack/value      \
		stack/symbol     \
		stack/parameter  \
		stack/helpers

FILES = $(MEPA_FILES) $(STACK_FILES)

OBJECTS = $(addsuffix .o, $(FILES))

.PHONY: all clean

all: lib

lib: $(LIB)( $(OBJECTS) )
	@echo Static Library compiled!

clean:
	@echo Removing static library
	@rm -f $(LIB)
