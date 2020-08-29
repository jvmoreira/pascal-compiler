#include "testCase.h"
#include "../stack.h"

void StackDestroyTest();
void StackItemDestroyTest();
void StackBuildTest();
void StackItemBuildTest();
void StackInsertTest();
void StackPopTest();
void StackSearchTest();

int main() {

  StackDestroyTest();
  StackItemDestroyTest();
  StackItemBuildTest();
  StackBuildTest();
  StackInsertTest();
  StackPopTest();
  StackSearchTest();

  printTestCaseResults();

  return 0;
}

void StackDestroyTest() {
  context("Destroying Stack");

  Stack *stack = (Stack*) malloc(sizeof(Stack));
  stack->top = stack->bottom = NULL;
  stack->length = 0;
  StackDestroy(&stack);

  assert((stack == NULL), "#StackDestroy destroys the stack" );
}

void StackItemDestroyTest() {
  context("Destroying StackItem");

  StackItem item = (StackItem) malloc(sizeof(Symbol));
  StackItemDestroy(&item);

  assert((item == NULL), "#StackItemDestroy destroys the item" );
}

void StackBuildTest() {
  context("Creating new Stack");

  Stack *stack = StackBuild();

  assert((stack != NULL), "#StackBuild returns a pointer to a Stack");
  assert((stack->length == 0), "New stack's length equals zero");
  assert((stack->top == NULL), "New stack's top item equals NULL");
  assert((stack->bottom == NULL), "New stack's bottom item equals NULL");
  assert((StackEmpty(stack) == 1), "#StackEmpty on new stack returns true");

  StackDestroy(&stack);
}

void StackItemBuildTest() {
  context("Creating new StackItem");
  char *itemName = "itemName";

  StackItem item = StackItemBuild(itemName);

  assert((item != NULL), "#StackItemBuild returns a pointer to a StackItem");
  assert((strcmp(item->name, itemName) == 0), "New item has the correct name");

  StackItemDestroy(&item);
}

void StackInsertTest() {
  context("Inserting first item");
  Stack *stack = StackBuild();
  int previousLength = stack->length;

  StackItem firstItem = StackItemBuild("name");
  StackInsert(stack, firstItem);

  assert((stack->top == firstItem), "#StackInsert inserts new item on the top of the stack");
  assert((stack->bottom == stack->top), "First insert makes bottom equals top");
  assert((stack->top->next == NULL), "Top's next is NULL");
  assert((stack->bottom->previous == NULL), "Bottom's previous is NULL");
  assert((stack->length == previousLength + 1), "StackInsert increments stack length");
  assert((StackEmpty(stack) == 0), "#StackEmpty returns false");

  context("Inserting second item");
  previousLength = stack->length;

  StackItem secondItem = StackItemBuild("age");
  StackInsert(stack, secondItem);

  assert((stack->top == secondItem), "#StackInsert inserts new item on the top of the stack");
  assert((stack->bottom == firstItem), "Second insert mantains the bottom item");
  assert((stack->bottom->next == stack->top), "Can reach top item from bottom's next");
  assert((stack->top->previous == stack->bottom), "Can reach bottom item from top's previous");
  assert((stack->length == previousLength + 1), "#StackInsert increments stack length");

  StackDestroy(&stack);
}

void StackPopTest() {
  context("Popping first and only item");
  Stack *stack = StackBuild();
  StackItem item = StackItemBuild("item");
  StackInsert(stack, item);

  StackItem previousItem = stack->top->previous;
  StackItem poppedItem = StackPop(stack);

  assert((poppedItem == item), "#StackPop pops the top of the Stack");
  assert((stack->top == previousItem), "Stack top becomes the previous item");
  assert((stack->bottom == NULL), "When popping stack with single item, bottom equals NULL");
  assert((StackEmpty(stack) == 1), "#StackEmpty returns true");

  StackDestroy(&stack);
}

void StackSearchTest() {
  context("Inserting multiple items");
  Stack *stack = StackBuild();

  assert((StackSearch(stack, NULL) == NULL), "#StackSearch returns NULL when targetName is NULL");
  assert((StackSearch(stack, "item") == NULL), "#StackSearch on an empty stack returns NULL");

  StackItem nameItem = StackItemBuild("name");
  StackItem addressItem = StackItemBuild("address");
  StackItem phoneItem = StackItemBuild("phone");
  StackItem newAddressItem = StackItemBuild("address");
  StackItem documentItem = StackItemBuild("document");

  StackInsert(stack, nameItem);
  StackInsert(stack, addressItem);
  StackInsert(stack, phoneItem);
  StackInsert(stack, newAddressItem);
  StackInsert(stack, documentItem);

  StackItem searchedItem = StackSearch(stack, "age");
  assert((searchedItem == NULL), "#StackSearch returns NULL when target does not exist");

  searchedItem = StackSearch(stack, "phone");
  assert((searchedItem == phoneItem), "#StackSearch finds the latest match inserted");

  searchedItem = StackSearch(stack, "address");
  assert((searchedItem == newAddressItem), "#StackSearch finds the latest match inserted");

  StackDestroy(&stack);
}
