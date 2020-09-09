LIBS =  stack			\
				mepa

CLEAN = $(addprefix clean_, $(LIBS))

.PHONY: all $(LIBS)

all: $(LIBS)

$(LIBS):
	@make -C $@

clean: $(CLEAN)
	@echo Cleaning static libraries...
	@rm -f *.a

$(CLEAN):
	@make clean -C $(subst clean_, , $@)
