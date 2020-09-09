#include "testCase.h"

#define ERROR_COLOR "1;31m"
#define SUCCESS_COLOR "1;32m"

int errorCount = 0;
int mallocCount = 0;

void setErrorMode() {
	printf("\x1b[%s", ERROR_COLOR);
}

void setSuccessMode() {
	printf("\x1b[%s", SUCCESS_COLOR);
}

void resetColorMode() {
	printf("\x1b[0m");
}

void context(const char *context) {
  printf("\n\t%s\n", context);
}

void assert(int expression, const char* message) {
  if(expression != 0)
    return;

  errorCount++;
  setErrorMode();
  printf("ERROR:\t%s\n", message);
  resetColorMode();
}

void printTestCaseResults() {
  assert(!mallocCount, "The number of calls for malloc should be equal to the number of calls of free");

  if(errorCount > 0) {
    setErrorMode();
    char plural = (errorCount > 1 ? 's' : '\0');
    printf("\nTest suite failed: %i error%c found.\n\n", errorCount, plural);
  }
  else {
		setSuccessMode();
		printf("Test suite succeeded.\n\n");
	}

		resetColorMode();
}
