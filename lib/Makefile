LIBS = stack

LIB_OBJS= $@/*.o

.PHONY: all stack

all: $(LIBS)

$(LIBS):
	@make -C $@
	@ar rcs lib$@.a $(LIB_OBJS)
	@make clean -C $@

clean:
	@echo Cleaning static libraries...
	@rm -f *.a
	@make clean -C $(LIBS)
