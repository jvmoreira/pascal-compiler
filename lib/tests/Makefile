TESTS = stack

.PHONY: all $(TESTS)

all: $(TESTS)

$(TESTS):
	@make -C $@
	@echo "\nRunning \`$@\` tests"
	@./$@/execute-tests
