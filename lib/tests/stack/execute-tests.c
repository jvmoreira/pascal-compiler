#include "testCase.h"
#include "helpers-test.h"
#include "symbol-test.h"
#include "value-test.h"
#include "item-test.h"

int main() {

  executeHelpersTests();
  executeSymbolTests();
  executeStackValueTests();
  executeStackItemTests();

  printTestCaseResults();

  return 0;
}
