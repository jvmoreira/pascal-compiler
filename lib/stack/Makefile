CFLAGS = -Wall -Wextra -Werror -I headers

FILES =	helpers				\
				symbol				\
				default-item	\
				stack-item

OBJECTS = $(addsuffix .o, $(FILES))

.PHONY: all

all: $(OBJECTS)

clean:
	@echo Cleaning object files...
	@-rm -f $(OBJECTS)
