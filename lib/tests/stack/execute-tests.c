#include "testCase.h"
#include "helpers-test.h"
#include "symbol-test.h"
#include "default-item-test.h"

int main() {

  executeHelpersTests();
  executeSymbolTests();
  executeDefaultItemTests();

  printTestCaseResults();

  return 0;
}
