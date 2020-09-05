#include "stack-models.h"
#include "stack-item.h"
#include "testCase.h"

#include "stack-item-test.h"

void executeStackItemTests() {
  newStackItemTest();
}

void newStackItemTest() {
  StackItem item = newStackItem();

  assert(item != NULL, "#newStackItem returns pointer to a StackItem");
  assert(item->content.defaultItem == NULL, "#newStackItem creates item with NULL content");
  assert(item->previous == NULL, "#newStackItem creates item with NULL previous pointer");

  destroyStackItem(item);
}
