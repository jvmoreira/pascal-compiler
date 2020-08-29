#ifndef __TEST_CASE__
#define __TEST_CASE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void context(const char *context);

void assert(int expression, const char* message);

void printTestCaseResults();

#endif
