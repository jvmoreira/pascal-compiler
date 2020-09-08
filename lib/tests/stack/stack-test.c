#include "stack-models.h"
#include "stack.h"
#include "item.h"
#include "value.h"
#include "symbol.h"
#include "helpers.h"
#include "testCase.h"

#include "stack-test.h"

void executeStackTests() {
  newStackWithTypeTest();
  stackInsertValueTest();
  stackInsertSymbolTest();
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

void stackInsertValueTest() {
  _StackValue value;
  Stack stack = newStackWithType(SYMBOL);

  stackInsertValue(stack, &value);
  assert(emptyStack(stack), "#stackInsertValue does nothing when stack has type SYMBOL");
  destroyStack(stack);

  stack = newStackWithType(VALUE);
  for(int i = 0; i < 2; ++i) {
    StackItem previousTop = stack->top;
    int previousLength = stack->length;
    StackValue value = newStackValue("value", i);

    stackInsertValue(stack, value);
    int valueWasInserted = (stack->top != NULL) && (stack->top->type == VALUE) && (extractStackValue(stack->top) == value);

    assert(valueWasInserted, "#stackInsertValue inserts item with correct StackValue on stack->top");
    assert(stack->top->previous == previousTop, "#stackInsertValue sets stack->top->previous correctly");
    assert(stack->length == previousLength + 1, "#stackInsertValue increments stack->length correctly");
  }
  destroyStack(stack);
}

void stackInsertSymbolTest() {
  _Symbol symbol;
  Stack stack = newStackWithType(VALUE);

  stackInsertSymbol(stack, &symbol);
  assert(emptyStack(stack), "#stackInsertSymbol does nothing when stack has type VALUE");
  destroyStack(stack);

  stack = newStackWithType(SYMBOL);
  for(int i = 0; i < 2; ++i) {
    StackItem previousTop = stack->top;
    int previousLength = stack->length;
    Symbol symbol = newSymbol("symbol");

    stackInsertSymbol(stack, symbol);
    int symbolWasInserted = (stack->top != NULL) && (stack->top->type == SYMBOL) && (extractSymbol(stack->top) == symbol);

    assert(symbolWasInserted, "#stackInsertSymbol inserts item with correct Symbol on stack->top");
    assert(stack->top->previous == previousTop, "#stackInsertSymbol sets stack->top->previous correctly");
    assert(stack->length == previousLength + 1, "#stackInsertSymbol increments stack->length correctly");
  }
  destroyStack(stack);
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
