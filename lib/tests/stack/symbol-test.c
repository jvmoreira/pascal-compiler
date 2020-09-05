#include "stack-models.h"
#include "symbol.h"
#include "testCase.h"

#include "symbol-test.h"

void executeSymbolTests() {
  newSymbolTest();
  newSymbolWithInvalidNamesTest();
}

void newSymbolTest() {
  char name[5] = "John";
  Symbol symbol = newSymbol(name);

  assert(symbol != NULL, "#newSymbol returns pointer to a Symbol");
  assert(!strcmp(symbol->name, name), "#newSymbol returns symbol with correct name");

  destroySymbol(symbol);
}

void newSymbolWithInvalidNamesTest() {
  assert(newSymbol(NULL) == NULL, "#newSymbol returns NULL when name is NULL");
  assert(newSymbol("") == NULL, "#newSymbol returns NULL when name is empty");

  char invalidName[22] = { [0 ... 20] = 'a', '\0' };
  assert(newSymbol(invalidName) == NULL, "#newSymbol returns NULL when name is bigger than MAX_STR_LENGTH");
}
