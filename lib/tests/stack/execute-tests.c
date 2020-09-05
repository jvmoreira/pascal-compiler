#include "testCase.h"
#include "helpers-test.h"
#include "symbol-test.h"
#include "default-item-test.h"
#include "stack-item-test.h"

int main() {

  executeHelpersTests();
  executeSymbolTests();
  executeDefaultItemTests();
  executeStackItemTests();

  printTestCaseResults();

  return 0;
}
