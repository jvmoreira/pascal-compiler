#include "stack-models.h"
#include "helpers.h"
#include "testCase.h"

#include "helpers-test.h"

void executeHelpersTests() {
  invalidNameTest();
  isValueStackTest();
  isSybmolStackTest();
  emptyStackTest();
}

void invalidNameTest() {
  assert(invalidName(NULL), "#invalidName returns true when name is NULL");
  assert(invalidName(""), "#invalidName returns true when name is NULL");
  assert(invalidName("abcdefghijklmnopqrstu"), "#invalidName returns true when name is bigger than MAX_STR_LEN");
  assert(!invalidName("John"), "#invalidName returns false when name is smaller than MAX_STR_LEN");
}

void isValueStackTest() {
  assert(!isValueStack(NULL), "#isValueStack returns false when stack is NULL");

  _Stack stack;
  stack.type = SYMBOL;
  assert(!isValueStack(&stack), "#isValueStack returns false when stack has type SYMBOL");

  stack.type = VALUE;
  assert(isValueStack(&stack), "#isValueStack returns true when stack has type VALUE");
}

void isSybmolStackTest() {
  assert(!isSymbolStack(NULL), "#isSymbolStack returns false when stack is NULL");

  _Stack stack;
  stack.type = VALUE;
  assert(!isSymbolStack(&stack), "#isSymbolStack returns false when stack has type VALUE");

  stack.type = SYMBOL;
  assert(isSymbolStack(&stack), "#isSymbolStack returns true when stack has type SYMBOL");
}

void emptyStackTest() {
  _Stack _stack;
  Stack stack = &_stack;
  stack->length = 0;
  stack->top = NULL;

  assert(emptyStack(NULL), "#emptyStack is true when stack is NULL");
  assert(emptyStack(stack), "#emptyStack is true when stack is empty");

  _StackItem item;
  stack->length = 1;
  stack->top = &item;
  assert(!emptyStack(stack), "#emptyStack is false when stack is not empty");
}
