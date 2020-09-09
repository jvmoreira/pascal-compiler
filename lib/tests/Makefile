TESTS = stack			\
				mepa

CLEAN = $(addprefix clean_, $(TESTS))

.PHONY: all $(TESTS)

all: $(TESTS)

$(TESTS):
	@make -C $@
	@echo "\nRunning \`$@\` tests"
	@./$@/execute-tests

clean: $(CLEAN)

$(CLEAN):
	@make clean -C $(subst clean_, , $@)
