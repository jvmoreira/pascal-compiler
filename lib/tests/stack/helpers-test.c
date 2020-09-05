#include "stack-models.h"
#include "helpers.h"
#include "testCase.h"

#include "helpers-test.h"

void executeHelpersTests() {
  invalidNameTest();
}

void invalidNameTest() {
  assert(invalidName(NULL), "#invalidName returns true when name is NULL");
  assert(invalidName(""), "#invalidName returns true when name is NULL");
  assert(invalidName("abcdefghijklmnopqrstu"), "#invalidName returns true when name is bigger than MAX_STR_LEN");
  assert(!invalidName("John"), "#invalidName returns false when name is smaller than MAX_STR_LEN");
}
