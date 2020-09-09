#ifndef __TEST_CASE__
#define __TEST_CASE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int mallocCount;
#define malloc(size) malloc(size); mallocCount++
#define free(size) free(size); mallocCount--

void context(const char *context);

void assert(int expression, const char* message);

void printTestCaseResults();

#endif
