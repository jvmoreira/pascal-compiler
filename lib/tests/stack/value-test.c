#include "stack-models.h"
#include "value.h"
#include "symbol.h"
#include "stack.h"
#include "helpers.h"
#include "testCase.h"

#include "value-test.h"

void executeStackValueTests() {
  newStackValueWithInvalidNamesTest();
  newStackValueTest();
  extractStackValueTest();
  stackPopValueTest();
}

void newStackValueTest() {
  char name[5] = "John";
  int value = 16;
  StackValue stackValue = newStackValue(name, value);

  assert(stackValue != NULL, "#newStackValue returns pointer to a StackValue");
  assert(!strcmp(stackValue->name, name), "#newStackValue returns stackValue with correct name");
  assert(stackValue->value == value, "#newStackValue returns stackValue with correct value");

  destroyStackValue(stackValue);
}

void newStackValueWithInvalidNamesTest() {
  assert(newStackValue(NULL, 16) == NULL, "#newStackValue returns NULL when name is NULL");
  assert(newStackValue("", 16) == NULL, "#newStackValue returns NULL when name is empty");

  char invalidName[22] = { [0 ... 20] = 'a', '\0' };
  assert(newStackValue(invalidName, 16) == NULL, "#newStackValue returns NULL when name is bigger than MAX_STR_LENGTH");
}

void extractStackValueTest() {
  _StackItem item;
  _Symbol symbol;
  item.type = SYMBOL;
  item.symbol = &symbol;

  assert(extractStackValue(NULL) == NULL, "#extractStackValue returns NULL when item is NULL");
  assert(extractStackValue(&item) == NULL, "#extractStackValue returns NULL when item has SYMBOL type");

  _StackValue stackValue;
  item.type = VALUE;
  item.value = &stackValue;
  assert(extractStackValue(&item) == &stackValue, "#extractStackValue returns pointer to StackValue when item has VALUE type");
}

void stackPopValueTest() {
  Stack stack = newStackWithType(SYMBOL);
  stackInsertSymbol(stack, newSymbol("symbol"));

  assert(stackPopValue(NULL) == NULL, "#stackPopValue returns NULL when stack is NULL");
  assert(!emptyStack(stack) && stackPopValue(stack) == NULL, "#stackPopValue returns NULL when stack has SYMBOL type");
  destroyStack(stack);

  stack = newStackWithType(VALUE);
  assert(stackPopValue(stack) == NULL, "#stackPopValue returns NULL when stack is empty");

  int stackSize = 2;
  StackValue values[2];
  for(int i = 0; i < stackSize; ++i) {
    values[i] = newStackValue("value", i);
    stackInsertValue(stack, values[i]);
  }

  for(int i = stackSize - 1; i >= 0; --i) {
    int previousLength = stack->length;
    StackItem topPrevious = stack->top->previous;

    StackValue poppedValue = stackPopValue(stack);

    assert(poppedValue == values[i], "#stackPopValue returns last StackValue inserted");
    assert(stack->top == topPrevious, "#stackPopValue sets stack->top correctly");
    assert(stack->length == previousLength - 1, "#stackPopValue decrements stack->length correctly");

    destroyStackValue(poppedValue);
  }
  assert(emptyStack(stack), "#stackPopValue lefts stack empty after popping all items");
  destroyStack(stack);
}
