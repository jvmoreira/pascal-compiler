#include "stack-models.h"
#include "symbol.h"
#include "default-item.h"
#include "stack-item.h"
#include "testCase.h"

#include "stack-item-test.h"

void executeStackItemTests() {
  newStackItemTest();
  newSymbolStackItemTest();
}

void newStackItemTest() {
  DefaultItem item = newDefaultItem("John", 16);

  StackItem stackItem = newStackItem(item);

  assert(stackItem != NULL, "#newStackItem returns pointer to a StackItem");
  assert(stackItem->type == DEFAULT, "#newStackItem creates item with correct type");
  assert(extractDefaultItem(stackItem) == item, "#newStackItem creates item with correct content");
  assert(stackItem->previous == NULL, "#newStackItem creates item with NULL previous pointer");

  destroyStackItem(stackItem);
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
