#include "testCase.h"
#include "helpers-test.h"
#include "symbol-test.h"
#include "value-test.h"
#include "item-test.h"
#include "stack-test.h"

int main() {

  executeHelpersTests();
  executeSymbolTests();
  executeStackValueTests();
  executeStackItemTests();
  executeStackTests();

  printTestCaseResults();

  return 0;
}
