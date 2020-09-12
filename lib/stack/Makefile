CFLAGS = -Wall -Wextra -Werror -I include

FILES =	helpers				\
				symbol				\
				value					\
				item					\
				stack

OBJECTS = $(addsuffix .o, $(FILES))

.PHONY: all clean

all: $(OBJECTS)

clean:
	@echo Cleaning object files...
	@rm -f $(OBJECTS)
