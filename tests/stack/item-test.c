#include "stack-models.h"
#include "symbol.h"
#include "value.h"
#include "item.h"
#include "testCase.h"

#include "item-test.h"

void executeStackItemTests() {
  newStackItemTest();
  newSymbolStackItemTest();
}

void newStackItemTest() {
  StackValue stackValue = newStackValue("John", 16);

  StackItem item = newStackItem(stackValue);

  assert(item != NULL, "#newStackItem returns pointer to a StackItem");
  assert(item->type == VALUE, "#newStackItem creates item with correct type");
  assert(extractStackValue(item) == stackValue, "#newStackItem creates item with correct content");
  assert(item->previous == NULL, "#newStackItem creates item with NULL previous pointer");

  destroyStackItem(item);
}

void newSymbolStackItemTest() {
  Symbol symbol = newSymbol("John");

  StackItem item = newSymbolStackItem(symbol);

  assert(item != NULL, "#newStackItem returns pointer to a StackItem");
  assert(item->type == SYMBOL, "#newStackItem creates item with correct type");
  assert(extractSymbol(item) == symbol, "#newStackItem creates item with correct content");
  assert(item->previous == NULL, "#newStackItem creates item with NULL previous pointer");

  destroyStackItem(item);
}
