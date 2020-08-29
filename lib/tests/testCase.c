#include "testCase.h"

#define ERROR_COLOR "1;31m"
#define SUCCESS_COLOR "1;32m"

int errorCount = 0;

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
  printf("\n\n\t%s\n========================================\n", context);
}

void assert(int expression, const char* message) {
  if(expression == 0) {
    errorCount++;
    setErrorMode();
    printf("ERROR:\t");
  }

  printf("%s --> %i\n", message, expression);
  resetColorMode();
}

void printTestCaseResults() {
  if(errorCount > 0) {
    setErrorMode();
    printf("\n\nTest suite failed: %i error%c found.\n\n", errorCount, (errorCount > 1 ? 's' : '\0'));
    resetColorMode();
  } else {
		setSuccessMode();
		printf("\n\nTest suite succeeded.\n\n");
		resetColorMode();
	}
}
