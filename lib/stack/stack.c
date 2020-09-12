#include <stdlib.h>

#include "libstack.h"

Stack newStackWithType(StackType type) {
  Stack stack = (Stack) malloc(sizeof(_Stack));

  stack->type = type;
  stack->length = 0;
  stack->top = NULL;

  return stack;
}

void stackInsert(Stack stack, StackItem item) {
  item->previous = stack->top;
  stack->top = item;
  stack->length++;
}

void stackInsertValue(Stack stack, StackValue stackValue) {
  if(!isValueStack(stack) || !stackValue)
    return;

  StackItem item = newStackItem(stackValue);

  stackInsert(stack, item);
}

void stackInsertSymbol(Stack stack, Symbol symbol) {
  if(!isSymbolStack(stack) || !symbol)
    return;

  StackItem item = newSymbolStackItem(symbol);

  stackInsert(stack, item);
}

StackItem stackPop(Stack stack) {
  if(emptyStack(stack))
    return NULL;

  StackItem item = stack->top;
  stack->top = item->previous;
  stack->length--;

  return item;
}

void destroyStack(Stack stack) {
  StackItem item;

  for(; (item = stackPop(stack)) ;)
    destroyStackItem(item);

  free(stack);
}
