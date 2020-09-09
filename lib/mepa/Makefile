CFLAGS = -Wall -Wextra -Werror -I headers

LIB_PATH = ../libmepa.a

FILES =	setup

OBJECTS = $(addsuffix .o, $(FILES))

.PHONY: all clean

all: $(OBJECTS) $(LIB_PATH)( $(OBJECTS) )

clean:
	@echo Cleaning object files...
	@rm -f $(OBJECTS)

purge: clean
	@echo Deleting static library...
	@rm -f $(LIB_PATH)
