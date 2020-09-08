LIBS = stack

.PHONY: all stack

all: $(LIBS)

$(LIBS):
	@make -C $@

clean:
	@echo Cleaning static libraries...
	@rm -f *.a
	@make clean -C $(LIBS)
