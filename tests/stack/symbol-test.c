#include "stack-models.h"
#include "symbol.h"
#include "value.h"
#include "stack.h"
#include "helpers.h"
#include "testCase.h"

#include "symbol-test.h"

void executeSymbolTests() {
  newSymbolTest();
  newSymbolWithInvalidNamesTest();
  extractSymbolTest();
  stackSearchSymbolTest();
  stackPopSymbolTest();
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

void extractSymbolTest() {
  _StackItem item;
  _StackValue stackValue;
  item.type = VALUE;
  item.value = &stackValue;

  assert(extractSymbol(NULL) == NULL, "#extractSymbol returns NULL when item is NULL");
  assert(extractSymbol(&item) == NULL, "#extractSymbol returns NULL when item has VALUE type");

  _Symbol symbol;
  item.type = SYMBOL;
  item.symbol = &symbol;
  assert(extractSymbol(&item) == &symbol, "#extractSymbol returns pointer to Symbol when item has SYMBOL type");
}

void stackSearchSymbolTest() {
  Stack stack = newStackWithType(SYMBOL);
  assert(stackSearchSymbol(NULL, "target") == NULL, "#stackSearchSymbol returns NULL when stack is NULL");
  assert(stackSearchSymbol(stack, "target") == NULL, "#stackSearchSymbol returns NULL when stack is empty");

  String names[5] = { "name", "address", "age", "address", "phone" };
  Symbol symbols[5];
  for(int i = 0; i < 5; ++i) {
    symbols[i] = newSymbol(names[i]);
    stackInsertSymbol(stack, symbols[i]);
  }

  assert(stackSearchSymbol(stack, NULL) == NULL, "#stackSearchSymbol returns NULL when targetName is NULL");
  assert(stackSearchSymbol(stack, "height") == NULL, "#stackSearchSymbol returns NULL when target does not exist");
  assert(stackSearchSymbol(stack, "name") == symbols[0], "#stackSearchSymbol returns the matched `name` item");
  assert(stackSearchSymbol(stack, "address") == symbols[3], "#stackSearchSymbol finds the latest `address` inserted");

  destroyStack(stack);
}

void stackPopSymbolTest() {
  Stack stack = newStackWithType(VALUE);
  stackInsertValue(stack, newStackValue("value", 16));

  assert(stackPopSymbol(NULL) == NULL, "#stackPopSymbol returns NULL when stack is NULL");
  assert(!emptyStack(stack) && stackPopSymbol(stack) == NULL, "#stackPopSymbol returns NULL when stack has VALUE type");
  destroyStack(stack);

  stack = newStackWithType(SYMBOL);
  assert(stackPopSymbol(stack) == NULL, "#stackPopSymbol returns NULL when stack is empty");

  int stackSize = 2;
  Symbol symbols[2];
  for(int i = 0; i < stackSize; ++i) {
    symbols[i] = newSymbol("symbol");
    stackInsertSymbol(stack, symbols[i]);
  }

  for(int i = stackSize - 1; i >= 0; --i) {
    int previousLength = stack->length;
    StackItem topPrevious = stack->top->previous;

    Symbol poppedSymbol = stackPopSymbol(stack);

    assert(poppedSymbol == symbols[i], "#stackPopSymbol returns last Symbol inserted");
    assert(stack->top == topPrevious, "#stackPopSymbol sets stack->top correctly");
    assert(stack->length == previousLength - 1, "#stackPopSymbol decrements stack->length correctly");

    destroySymbol(poppedSymbol);
  }
  assert(emptyStack(stack), "#stackPopSymbol lefts stack empty after popping all items");
  destroyStack(stack);
}
