#include "stack-models.h"
#include "stack.h"
#include "item.h"
#include "helpers.h"
#include "testCase.h"

#include "stack-test.h"

void executeStackTests() {
  newStackWithTypeTest();
  stackPopTest();
}

void newStackWithTypeTest() {
  StackType cases[2] = { VALUE, SYMBOL };
  StackType type;

  for(int i = 0; (i < 2) && (type = cases[i]); ++i) {
    Stack stack = newStackWithType(type);

    assert(stack != NULL, "#newStackWithType returns pointer to a stack");
    assert(stack->type == type, "#newStackWithType creates stack with correct type");
    assert(stack->top == NULL, "#newStackWithType creates stack with NULL top");
    assert(stack->length == 0, "#newStackWithType creates stack with zero length");

    destroyStack(stack);
  }
}

void stackPopTest() {
  Stack stack = newStackWithType(SYMBOL);

  assert(stackPop(NULL) == NULL, "#stackPop returns NULL when stack is NULL");
  assert(stackPop(stack) == NULL, "#stackPop returns NULL when stack is empty");

  _StackItem item;
  item.previous = NULL;
  stack->top = &item;
  stack->length = 1;
  StackItem poppedItem = stackPop(stack);

  assert(poppedItem == &item, "#stackPop returns last item inserted");
  assert(emptyStack(stack), "#stackPop lefts stack empty after popping all items");

  destroyStack(stack);
}
