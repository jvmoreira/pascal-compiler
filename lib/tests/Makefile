TESTS = stack

.PHONY: all $(TESTS)

all: $(TESTS)

$(TESTS):
	@make -C $@
	@make clean -C $@
	@echo "\nRunning \`$@\` tests"
	@./$@/execute-tests
